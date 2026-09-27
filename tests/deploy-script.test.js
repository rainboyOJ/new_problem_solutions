import test from 'node:test';
import assert from 'node:assert/strict';
import { existsSync, readFileSync, statSync } from 'node:fs';
import path from 'node:path';

const repoRoot = path.resolve('.');

function read(relativePath) {
  return readFileSync(path.join(repoRoot, relativePath), 'utf8');
}

test('local deployment builds and verifies before pushing', () => {
  const scriptPath = path.join(repoRoot, 'deploy.sh');
  const script = read('deploy.sh');

  assert.ok(statSync(scriptPath).mode & 0o111);
  assert.match(script, /BRANCH="master"/);
  assert.match(script, /git fetch --quiet origin "\$BRANCH"/);
  assert.match(script, /merge-base --is-ancestor/);
  assert.match(script, /--dry-run/);
  assert.match(script, /npm run verify:push/);
  assert.match(script, /scripts\/build-native-release\.sh/);
  assert.match(script, /git push --no-verify origin/);
  assert.ok(script.indexOf('npm run verify:push') < script.indexOf('git push --no-verify'));
  assert.ok(script.indexOf('scripts/build-native-release.sh') < script.indexOf('git push --no-verify'));
  assert.doesNotMatch(script, /gh run|gh workflow|docker build|docker pull/);
});

test('release is exported from the committed tree and checked as production', () => {
  const scriptPath = path.join(repoRoot, 'scripts/build-native-release.sh');
  const script = read('scripts/build-native-release.sh');

  assert.ok(statSync(scriptPath).mode & 0o111);
  assert.match(script, /git -C "\$ROOT_DIR" archive --format=tar "\$RELEASE_SHA"/);
  assert.match(script, /app\.js package\.json package-lock\.json bin lib routes views public problems problem-sets/);
  assert.doesNotMatch(script, /rsync.*ROOT_DIR/);
  assert.match(script, /npm ci --omit=dev/);
  assert.match(script, /process\.platform, process\.arch/);
  assert.match(script, /activeRevision !== process\.env\.RELEASE_SHA/);
  assert.match(script, /errorCount !== 0/);
});

test('VPS activation is serialized, health checked, and rollback capable', () => {
  const scriptPath = path.join(repoRoot, 'scripts/deploy-native.sh');
  const script = read('scripts/deploy-native.sh');

  assert.ok(statSync(scriptPath).mode & 0o111);
  assert.match(script, /flock -x -w 1800/);
  assert.match(script, /start_candidate/);
  assert.match(script, /point_current_at "\$RELEASE_DIR"/);
  assert.match(script, /systemctl restart "\$SERVICE_NAME"/);
  assert.match(script, /rolling back/);
  assert.match(script, /rolled-back-to-/);
  assert.ok(script.indexOf('start_candidate\n') < script.indexOf('docker stop -t 20'));
  assert.ok(script.indexOf('point_current_at "$RELEASE_DIR"') < script.lastIndexOf('systemctl restart "$SERVICE_NAME"'));
});

test('systemd service runs the release as an unprivileged user', () => {
  const unit = read('deploy/problems-solution.service');

  assert.match(unit, /User=problems-solution/);
  assert.match(unit, /Group=problems-solution/);
  assert.match(unit, /WorkingDirectory=\/opt\/problems-solution\/current/);
  assert.match(unit, /Environment=HOST=127\.0\.0\.1/);
  assert.match(unit, /Environment=PORT=3300/);
  assert.match(unit, /ExecStart=\/usr\/bin\/node \/opt\/problems-solution\/current\/bin\/www/);
  assert.match(unit, /NoNewPrivileges=true/);
});

test('active Docker and GitHub deployment entrypoints are removed', () => {
  for (const relativePath of [
    '.github/workflows/deploy.yml',
    'scripts/deploy-vps.sh',
    'Dockerfile',
    'docker-compose.yml',
    '.dockerignore',
  ]) {
    assert.equal(existsSync(path.join(repoRoot, relativePath)), false, relativePath);
  }
});
