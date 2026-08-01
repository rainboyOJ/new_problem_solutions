import test from 'node:test';
import assert from 'node:assert/strict';
import {
  chmodSync,
  mkdtempSync,
  mkdirSync,
  readFileSync,
  rmSync,
  writeFileSync,
} from 'node:fs';
import { tmpdir } from 'node:os';
import path from 'node:path';
import { execFileSync, spawnSync } from 'node:child_process';

const deployScript = path.resolve('scripts/deploy-vps.sh');

function git(...args) {
  return execFileSync('git', args, { encoding: 'utf8' }).trim();
}

function createDeployFixture() {
  const root = mkdtempSync(path.join(tmpdir(), 'rbook-deploy-'));
  const origin = path.join(root, 'origin.git');
  const source = path.join(root, 'source');
  const app = path.join(root, 'app');
  const fakeBin = path.join(root, 'bin');
  const stateFile = path.join(root, 'docker-state');
  const logFile = path.join(root, 'docker.log');
  mkdirSync(source);
  mkdirSync(fakeBin);

  git('init', '--bare', origin);
  git('-C', source, 'init', '-b', 'master');
  git('-C', source, 'config', 'user.email', 'test@example.com');
  git('-C', source, 'config', 'user.name', 'RBook Test');
  writeFileSync(path.join(source, 'content.txt'), 'revision one\n');
  git('-C', source, 'add', 'content.txt');
  git('-C', source, 'commit', '-m', 'initial');
  git('-C', source, 'remote', 'add', 'origin', origin);
  git('-C', source, 'push', '-u', 'origin', 'master');
  git('clone', '--branch', 'master', origin, app);

  writeFileSync(path.join(source, 'content.txt'), 'revision two\n');
  git('-C', source, 'commit', '-am', 'content update');
  git('-C', source, 'push', 'origin', 'master');
  const targetRevision = git('-C', source, 'rev-parse', 'HEAD');

  writeFileSync(stateFile, 'running');
  writeFileSync(logFile, '');
  const dockerPath = path.join(fakeBin, 'docker');
  writeFileSync(dockerPath, `#!/usr/bin/env bash
set -euo pipefail
printf '%s\\n' "$*" >> "$FAKE_DOCKER_LOG"
if [[ "$1" == "compose" ]]; then
  if [[ "\${2:-}" == "up" ]]; then printf 'recreated' > "$FAKE_DOCKER_STATE"; fi
  exit 0
fi
if [[ "$1 $2" == "container inspect" ]]; then
  format="\${4:-}"
  case "$format" in
    *State.Running*) printf 'true\\n' ;;
    *'.Image'*) printf 'fake-image-id\\n' ;;
    *compose.project*) printf 'problems-solution\\n' ;;
    *compose.service*) printf 'problems-solution\\n' ;;
    *) printf 'fake-container-id\\n' ;;
  esac
  exit 0
fi
if [[ "$1 $2" == "image inspect" ]]; then exit 0; fi
if [[ "$1" == "kill" ]]; then
  case "$2" in
    --signal=SIGUSR2)
      if [[ "$FAKE_BUSY" == "true" ]]; then
        printf 'busy' > "$FAKE_DOCKER_STATE"
      else
        printf 'switching' > "$FAKE_DOCKER_STATE"
      fi
      ;;
    --signal=SIGHUP)
      if [[ "$FAKE_BUSY" == "true" ]]; then
        printf 'restored' > "$FAKE_DOCKER_STATE"
      else
        printf 'reloaded' > "$FAKE_DOCKER_STATE"
      fi
      ;;
  esac
  exit 0
fi
if [[ "$1" == "pull" || "$1" == "tag" || "$1 $2" == "container rm" ]]; then exit 0; fi
exit 0
`);
  chmodSync(dockerPath, 0o755);

  const curlPath = path.join(fakeBin, 'curl');
  writeFileSync(curlPath, `#!/usr/bin/env bash
set -euo pipefail
state="$(cat "$FAKE_DOCKER_STATE")"
if [[ "$state" == "switching" ]]; then
  printf '{"state":"switching","targetRevision":"old","activeRevision":"old","inFlightRequests":0}\\n'
elif [[ "$state" == "busy" ]]; then
  printf '{"state":"switching","targetRevision":"old","activeRevision":"old","inFlightRequests":1}\\n'
elif [[ "$state" == "restored" ]]; then
  printf '{"state":"healthy","targetRevision":"old","activeRevision":"old","inFlightRequests":0}\\n'
elif [[ "$state" == "reloaded" || "$state" == "recreated" ]]; then
  printf '{"state":"healthy","targetRevision":"%s","activeRevision":"%s","inFlightRequests":0}\\n' "$TARGET_REVISION" "$TARGET_REVISION"
else
  printf '{"state":"healthy","targetRevision":"old","activeRevision":"old","inFlightRequests":0}\\n'
fi
`);
  chmodSync(curlPath, 0o755);

  return { root, app, fakeBin, stateFile, logFile, targetRevision };
}

function runDeploy(fixture, skipImagePull, busy = false) {
  return spawnSync('bash', [deployScript], {
    encoding: 'utf8',
    env: {
      ...process.env,
      PATH: `${fixture.fakeBin}:${process.env.PATH}`,
      APP_DIR: fixture.app,
      SERVICE_NAME: 'problems-solution',
      BRANCH: 'master',
      TARGET_REVISION: fixture.targetRevision,
      SKIP_IMAGE_PULL: skipImagePull ? 'true' : 'false',
      CONTENT_DRAIN_TIMEOUT: '1',
      CONTENT_REFRESH_TIMEOUT: '1',
      FAKE_DOCKER_LOG: fixture.logFile,
      FAKE_DOCKER_STATE: fixture.stateFile,
      FAKE_BUSY: busy ? 'true' : 'false',
    },
  });
}

test('content-only deployment updates revision without pulling or recreating', () => {
  const fixture = createDeployFixture();
  try {
    const result = runDeploy(fixture, true);
    assert.equal(result.status, 0, result.stderr || result.stdout);
    const log = readFileSync(fixture.logFile, 'utf8');
    assert.match(log, /kill --signal=SIGUSR2 fake-container-id/);
    assert.match(log, /kill --signal=SIGHUP fake-container-id/);
    assert.doesNotMatch(log, /^pull /m);
    assert.doesNotMatch(log, /^compose up /m);
    assert.equal(git('-C', fixture.app, 'rev-parse', 'HEAD'), fixture.targetRevision);
    const handoff = JSON.parse(readFileSync(
      path.join(fixture.app, '.runtime', 'content-revision.json'),
      'utf8',
    ));
    assert.equal(handoff.targetRevision, fixture.targetRevision);
  } finally {
    rmSync(fixture.root, { recursive: true, force: true });
  }
});

test('drain timeout restores the previous revision without changing Git', () => {
  const fixture = createDeployFixture();
  try {
    const previousRevision = git('-C', fixture.app, 'rev-parse', 'HEAD');
    const result = runDeploy(fixture, true, true);
    assert.equal(result.status, 1, result.stderr || result.stdout);
    assert.match(result.stderr, /Git was not modified/);
    assert.equal(git('-C', fixture.app, 'rev-parse', 'HEAD'), previousRevision);
    const log = readFileSync(fixture.logFile, 'utf8');
    assert.match(log, /kill --signal=SIGHUP fake-container-id/);
    assert.doesNotMatch(log, /^compose up /m);
  } finally {
    rmSync(fixture.root, { recursive: true, force: true });
  }
});

test('application deployment still pulls an image and force recreates Compose', () => {
  const fixture = createDeployFixture();
  try {
    const result = runDeploy(fixture, false);
    assert.equal(result.status, 0, result.stderr || result.stdout);
    const log = readFileSync(fixture.logFile, 'utf8');
    assert.match(log, /^pull /m);
    assert.match(log, /compose up -d --force-recreate --remove-orphans/);
  } finally {
    rmSync(fixture.root, { recursive: true, force: true });
  }
});
