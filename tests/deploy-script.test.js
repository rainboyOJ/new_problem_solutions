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
  assert.match(script, /^REQUIRED_PLATFORM="linux-x64"$/m);
  assert.match(script, /if \[\[ "\$DRY_RUN" != true \]\]/);
  assert.match(script, /\[\[ "\$deploy_platform" == "\$REQUIRED_PLATFORM" \]\]/);
  assert.match(script, /deploy from a \$REQUIRED_PLATFORM host/);
  assert.ok(script.indexOf('deploy_platform=') < script.indexOf('npm run verify:push'));
  assert.ok(script.indexOf('deploy_platform=') < script.indexOf('git push --no-verify'));
  assert.match(script, /npm run verify:push/);
  assert.match(script, /scripts\/build-native-release\.sh/);
  assert.match(script, /upload content index/);
  assert.match(script, /UPLOAD_CONTENT_INDEX/);
  assert.match(script, /git push --no-verify origin/);
  assert.ok(script.indexOf('npm run verify:push') < script.indexOf('git push --no-verify'));
  assert.ok(script.indexOf('scripts/build-native-release.sh') < script.indexOf('git push --no-verify'));
  assert.match(script, /content_sync_mode=delta/);
  assert.match(script, /git diff --no-renames --name-only -z --diff-filter=ACMRTUXB/);
  assert.match(script, /upload content delta/);
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
  assert.match(script, /scripts\/build-content-index\.js/);
  assert.match(script, /CONTENT_INDEX_PATH="\$CONTENT_INDEX"/);
});

test('VPS activation is serialized, health checked, and rollback capable', () => {
  const scriptPath = path.join(repoRoot, 'scripts/deploy-native.sh');
  const script = read('scripts/deploy-native.sh');

  assert.ok(statSync(scriptPath).mode & 0o111);
  assert.match(script, /flock -x -w 1800/);
  assert.match(script, /start_candidate/);
  assert.match(script, /assemble_app/);
  assert.match(script, /assemble_content/);
  assert.match(script, /content-index-v1\.json/);
  assert.match(script, /PROBLEMS_SOLUTION_CONTENT_SHA="\$CONTENT_SHA"/);
  assert.match(script, /assemble_deployment/);
  assert.match(script, /-name '\*\.node'/);
  assert.match(script, /native dependency ABI mismatch/);
  assert.match(script, /point_current_at "\$DEPLOYMENT_DIR"/);
  assert.match(script, /systemctl restart "\$SERVICE_NAME"/);
  assert.match(script, /rolling back/);
  assert.match(script, /rolled-back-to-/);
  assert.match(script, /docker container inspect problems-solution/);
  assert.doesNotMatch(script, /docker inspect problems-solution/);
  assert.match(script, /deployment_references content \| grep -Fx -- "\$name" >\/dev\/null/);
  assert.doesNotMatch(script, /deployment_references (?:app|content) \| grep -q/);
  assert.ok(script.indexOf('start_candidate\n') < script.indexOf('docker stop -t 20'));
  assert.ok(script.indexOf('point_current_at "$DEPLOYMENT_DIR"') < script.lastIndexOf('systemctl restart "$SERVICE_NAME"'));
});

test('content delta clones unchanged files and applies additions, changes, and deletions', () => {
  const root = mkdtempSync(path.join(tmpdir(), 'rbook-content-rsync-'));
  const previous = path.join(root, 'previous');
  const source = path.join(root, 'delta-source');
  const target = path.join(root, 'target');
  const archiveTar = path.join(root, 'delta.tar');
  const archive = path.join(root, 'delta.tar.zst');
  const changedList = path.join(root, 'changed.nul');
  const deletedList = path.join(root, 'deleted.nul');
  const contentSha = 'a'.repeat(40);
  try {
    for (const directory of [
      path.join(previous, 'problems'),
      path.join(previous, 'problem-sets'),
      path.join(source, 'problems'),
    ]) mkdirSync(directory, { recursive: true });
    writeFileSync(path.join(previous, 'content.env'), 'PROBLEMS_SOLUTION_CONTENT_SHA=before\n');
    writeFileSync(path.join(previous, 'problems/same.md'), 'same\n');
    writeFileSync(path.join(previous, 'problems/changed.md'), 'before\n');
    writeFileSync(path.join(previous, 'problems/removed.md'), 'removed\n');
    writeFileSync(path.join(previous, 'problem-sets/base.md'), 'base\n');
    writeFileSync(path.join(source, 'content.env'), `PROBLEMS_SOLUTION_CONTENT_SHA=${contentSha}\n`);
    writeFileSync(path.join(source, 'problems/changed.md'), 'after\n');
    writeFileSync(path.join(source, 'problems/added.md'), 'added\n');
    writeFileSync(changedList, Buffer.from('content.env\0problems/changed.md\0problems/added.md\0'));
    writeFileSync(deletedList, Buffer.from('problems/removed.md\0'));

    execFileSync('tar', [
      '-C', source, '-cf', archiveTar,
      'content.env', 'problems/changed.md', 'problems/added.md',
    ]);
    execFileSync('zstd', ['-q', '-f', archiveTar, '-o', archive]);
    execFileSync('bash', [
      path.join(repoRoot, 'scripts/apply-content-delta.sh'),
      previous, target, archive, changedList, deletedList, contentSha,
    ]);

    assert.equal(readFileSync(path.join(target, 'problems/changed.md'), 'utf8'), 'after\n');
    assert.equal(readFileSync(path.join(previous, 'problems/changed.md'), 'utf8'), 'before\n');
    assert.equal(readFileSync(path.join(target, 'problems/added.md'), 'utf8'), 'added\n');
    assert.equal(existsSync(path.join(target, 'problems/removed.md')), false);
    assert.equal(
      statSync(path.join(target, 'problems/same.md')).ino,
      statSync(path.join(previous, 'problems/same.md')).ino,
    );
    assert.equal(
      readFileSync(path.join(target, 'content.env'), 'utf8'),
      `PROBLEMS_SOLUTION_CONTENT_SHA=${contentSha}\n`,
    );
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
  assert.match(unit, /EnvironmentFile=\/opt\/problems-solution\/current\/deployment\.env/);
  assert.match(unit, /Environment=CONTENT_INDEX_PATH=\/opt\/problems-solution\/current\/content-index-v1\.json/);
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
