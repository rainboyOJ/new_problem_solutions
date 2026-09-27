import test from 'node:test';
import assert from 'node:assert/strict';
import {
  existsSync,
  mkdtempSync,
  mkdirSync,
  readFileSync,
  rmSync,
  statSync,
  writeFileSync,
} from 'node:fs';
import { execFileSync } from 'node:child_process';
import { tmpdir } from 'node:os';
import path from 'node:path';

const repoRoot = path.resolve('.');

function read(relativePath) {
  return readFileSync(path.join(repoRoot, relativePath), 'utf8');
}

test('local deployment builds and verifies before pushing', () => {
  const scriptPath = path.join(repoRoot, 'deploy.sh');
  const script = read('deploy.sh');

  assert.ok(statSync(scriptPath).mode & 0o111);
  assert.match(script, /https:\/\/pcs2\.roj\.ac\.cn\/api\/health\/content/);
  assert.match(script, /BRANCH="master"/);
  assert.match(script, /git fetch --quiet origin "\$BRANCH"/);
  assert.match(script, /merge-base --is-ancestor/);
  assert.match(script, /--dry-run/);
  assert.match(script, /npm run verify:push/);
  assert.match(script, /scripts\/build-native-release\.sh/);
  assert.match(script, /git push --no-verify origin/);
  assert.ok(script.indexOf('npm run verify:push') < script.indexOf('git push --no-verify'));
  assert.ok(script.indexOf('scripts/build-native-release.sh') < script.indexOf('git push --no-verify'));
  assert.match(script, /--link-dest=\$BASE_DIR\/contents\/\$remote_content_sha/);
  assert.match(script, /--copy-dest=\$BASE_DIR\/current/);
  assert.match(script, /--copy-dest=\/srv\/rbook/);
  assert.match(script, /if \[\[ "\$application_changed" == true \]\]/);
  assert.match(script, /if \[\[ "\$content_changed" == true \]\]/);
  assert.doesNotMatch(script, /gh run|gh workflow|docker build|docker pull/);
});

test('build separates the app release from incrementally synced content', () => {
  const scriptPath = path.join(repoRoot, 'scripts/build-native-release.sh');
  const script = read('scripts/build-native-release.sh');

  assert.ok(statSync(scriptPath).mode & 0o111);
  assert.match(script, /git -C "\$ROOT_DIR" archive --format=tar "\$RELEASE_SHA"/);
  assert.match(script, /app\.js package\.json package-lock\.json config\.yml bin lib routes views public/);
  assert.match(script, /for source in problems problem-sets/);
  assert.match(script, /tar -C "\$APP_DIR"/);
  assert.doesNotMatch(script, /tar -C "\$CONTENT_DIR"/);
  assert.doesNotMatch(script, /rsync.*ROOT_DIR/);
  assert.match(script, /npm ci --omit=dev/);
  assert.match(script, /process\.platform, process\.arch/);
  assert.match(script, /NODE_ABI="\$\(node -p/);
  assert.match(script, /activeRevision !== process\.env\.RELEASE_SHA/);
  assert.match(script, /errorCount !== 0/);
});

test('VPS activation is serialized, health checked, and rollback capable', () => {
  const scriptPath = path.join(repoRoot, 'scripts/deploy-native.sh');
  const script = read('scripts/deploy-native.sh');

  assert.ok(statSync(scriptPath).mode & 0o111);
  assert.match(script, /flock -x -w 1800/);
  assert.match(script, /start_candidate/);
  assert.match(script, /assemble_app/);
  assert.match(script, /assemble_content/);
  assert.match(script, /assemble_deployment/);
  assert.match(script, /-name '\*\.node'/);
  assert.match(script, /native dependency ABI mismatch/);
  assert.match(script, /point_current_at "\$DEPLOYMENT_DIR"/);
  assert.match(script, /systemctl restart "\$SERVICE_NAME"/);
  assert.match(script, /rolling back/);
  assert.match(script, /rolled-back-to-/);
  assert.match(script, /docker container inspect problems-solution/);
  assert.doesNotMatch(script, /docker inspect problems-solution/);
  assert.ok(script.indexOf('start_candidate\n') < script.indexOf('docker stop -t 20'));
  assert.ok(script.indexOf('point_current_at "$DEPLOYMENT_DIR"') < script.lastIndexOf('systemctl restart "$SERVICE_NAME"'));
});

test('rsync content snapshots transfer changes and hard-link unchanged files', () => {
  const root = mkdtempSync(path.join(tmpdir(), 'rbook-content-rsync-'));
  const previous = path.join(root, 'previous');
  const source = path.join(root, 'source');
  const target = path.join(root, 'target');
  try {
    for (const directory of [previous, source, target]) mkdirSync(directory);
    writeFileSync(path.join(previous, 'same.md'), 'same\n');
    writeFileSync(path.join(previous, 'changed.md'), 'before\n');
    writeFileSync(path.join(previous, 'removed.md'), 'removed\n');
    writeFileSync(path.join(source, 'same.md'), 'same\n');
    writeFileSync(path.join(source, 'changed.md'), 'after\n');
    writeFileSync(path.join(source, 'added.md'), 'added\n');

    execFileSync('rsync', [
      '-rlp', '--delete', '--checksum', `--link-dest=${previous}`, `${source}/`, `${target}/`,
    ]);

    assert.equal(readFileSync(path.join(target, 'changed.md'), 'utf8'), 'after\n');
    assert.equal(readFileSync(path.join(target, 'added.md'), 'utf8'), 'added\n');
    assert.equal(existsSync(path.join(target, 'removed.md')), false);
    assert.equal(statSync(path.join(target, 'same.md')).ino, statSync(path.join(previous, 'same.md')).ino);
  } finally {
    rmSync(root, { recursive: true, force: true });
  }
});

test('systemd service runs the release as an unprivileged user', () => {
  const unit = read('deploy/problems-solution.service');

  assert.match(unit, /User=problems-solution/);
  assert.match(unit, /Group=problems-solution/);
  assert.match(unit, /WorkingDirectory=\/opt\/problems-solution\/current/);
  assert.match(unit, /Environment=HOST=127\.0\.0\.1/);
  assert.match(unit, /Environment=PORT=3300/);
  assert.match(unit, /ExecStart=\/usr\/bin\/node \/opt\/problems-solution\/current\/app\/bin\/www/);
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
