import test from 'node:test';
import assert from 'node:assert/strict';
import {
  chmodSync,
  mkdirSync,
  mkdtempSync,
  readFileSync,
  rmSync,
  statSync,
  writeFileSync,
} from 'node:fs';
import os from 'node:os';
import path from 'node:path';
import { execFileSync, spawnSync } from 'node:child_process';
import yaml from 'js-yaml';
import {
  findNonHeadRefs,
  parsePushRefs,
} from '../scripts/check-pre-push.js';
import {
  compareDirectoryTrees,
  runVerification,
  VerificationFailure,
} from '../scripts/verify-push.js';
import {
  validateContentHealth,
  validateLiveHealth,
} from '../scripts/smoke-test.js';

const repoRoot = path.resolve();
const prePushCheck = path.join(repoRoot, 'scripts', 'check-pre-push.js');
const hookInstaller = path.join(repoRoot, 'scripts', 'install-git-hooks.js');

function git(cwd, ...args) {
  return execFileSync('git', args, { cwd, encoding: 'utf8' }).trim();
}

function createGitFixture() {
  const root = mkdtempSync(path.join(os.tmpdir(), 'rbook-pre-push-'));
  git(root, 'init', '-b', 'master');
  git(root, 'config', 'user.email', 'test@example.com');
  git(root, 'config', 'user.name', 'RBook Test');
  writeFileSync(path.join(root, 'tracked.txt'), 'initial\n');
  git(root, 'add', 'tracked.txt');
  git(root, 'commit', '-m', 'initial');
  return root;
}

test('pre-push input permits HEAD and deletion refs only', () => {
  const head = 'a'.repeat(40);
  const refs = parsePushRefs([
    `refs/heads/master ${head} refs/heads/master ${'b'.repeat(40)}`,
    `delete ${'0'.repeat(40)} refs/heads/old ${'c'.repeat(40)}`,
  ].join('\n'));
  assert.equal(refs.length, 2);
  assert.deepEqual(findNonHeadRefs(refs, head), []);

  refs.push({
    localRef: 'refs/tags/old',
    localSha: 'd'.repeat(40),
    remoteRef: 'refs/tags/old',
    remoteSha: '0'.repeat(40),
  });
  assert.equal(findNonHeadRefs(refs, head).length, 1);
});

test('pre-push checker rejects dirty worktrees and non-HEAD refs', () => {
  const root = createGitFixture();
  try {
    const head = git(root, 'rev-parse', 'HEAD');
    const validInput = `refs/heads/master ${head} refs/heads/master ${'0'.repeat(40)}\n`;
    const clean = spawnSync(process.execPath, [prePushCheck], {
      cwd: root,
      input: validInput,
      encoding: 'utf8',
    });
    assert.equal(clean.status, 0, clean.stderr);

    writeFileSync(path.join(root, 'untracked.txt'), 'not committed\n');
    const dirty = spawnSync(process.execPath, [prePushCheck], {
      cwd: root,
      input: validInput,
      encoding: 'utf8',
    });
    assert.equal(dirty.status, 1);
    assert.match(dirty.stderr, /工作区不是干净状态/);
    assert.match(dirty.stderr, /untracked\.txt/);
    rmSync(path.join(root, 'untracked.txt'));

    const nonHead = spawnSync(process.execPath, [prePushCheck], {
      cwd: root,
      input: `refs/tags/old ${'f'.repeat(40)} refs/tags/old ${'0'.repeat(40)}\n`,
      encoding: 'utf8',
    });
    assert.equal(nonHead.status, 1);
    assert.match(nonHead.stderr, /不指向当前 HEAD/);
  } finally {
    rmSync(root, { recursive: true, force: true });
  }
});

test('hook installer configures the repository-owned hooks directory', () => {
  const root = createGitFixture();
  try {
    const hooksDir = path.join(root, '.githooks');
    mkdirSync(hooksDir);
    const hookPath = path.join(hooksDir, 'pre-push');
    writeFileSync(hookPath, '#!/usr/bin/env bash\nexit 0\n');
    chmodSync(hookPath, 0o755);

    const result = spawnSync(process.execPath, [hookInstaller], {
      cwd: root,
      encoding: 'utf8',
    });
    assert.equal(result.status, 0, result.stderr);
    assert.equal(git(root, 'config', '--local', '--get', 'core.hooksPath'), '.githooks');
  } finally {
    rmSync(root, { recursive: true, force: true });
  }
});

test('committed pre-push hook is executable', () => {
  const hookPath = path.join(repoRoot, '.githooks', 'pre-push');
  const mode = statSync(hookPath).mode;
  assert.notEqual(mode & 0o111, 0);
  const source = readFileSync(hookPath, 'utf8');
  assert.match(source, /node \.\/scripts\/check-pre-push\.js/);
  assert.match(source, /npm run verify:push/);
});

test('directory comparison reports missing, unexpected, and changed files', () => {
  const root = mkdtempSync(path.join(os.tmpdir(), 'rbook-build-diff-'));
  const expected = path.join(root, 'expected');
  const actual = path.join(root, 'actual');
  try {
    mkdirSync(expected);
    mkdirSync(actual);
    writeFileSync(path.join(expected, 'same.txt'), 'same\n');
    writeFileSync(path.join(actual, 'same.txt'), 'same\n');
    writeFileSync(path.join(expected, 'missing.txt'), 'missing\n');
    writeFileSync(path.join(actual, 'unexpected.txt'), 'unexpected\n');
    writeFileSync(path.join(expected, 'changed.txt'), 'before\n');
    writeFileSync(path.join(actual, 'changed.txt'), 'after\n');

    assert.deepEqual(compareDirectoryTrees(expected, actual), {
      missing: ['missing.txt'],
      unexpected: ['unexpected.txt'],
      changed: ['changed.txt'],
    });
  } finally {
    rmSync(root, { recursive: true, force: true });
  }
});

test('health validators require live and fully healthy content responses', () => {
  assert.doesNotThrow(() => validateLiveHealth({ status: 200, body: { status: 'ok' } }));
  assert.throws(
    () => validateLiveHealth({ status: 503, body: { status: 'down' } }),
    /存活检查失败/,
  );

  const health = { state: 'healthy', ready: true, errorCount: 0 };
  assert.equal(validateContentHealth({ status: 200, body: health }), health);
  assert.throws(
    () => validateContentHealth({
      status: 200,
      body: { state: 'degraded', ready: true, errorCount: 1 },
    }),
    /内容健康检查失败/,
  );
});

test('verification orchestration preserves failed stage metadata', () => {
  const originalLog = console.log;
  console.log = () => {};
  try {
    assert.throws(
      () => runVerification([{
        name: '测试阶段',
        command: 'failing-command',
        run() { throw new Error('boom'); },
      }]),
      (error) => {
        assert.ok(error instanceof VerificationFailure);
        assert.equal(error.stage, '测试阶段');
        assert.equal(error.command, 'failing-command');
        assert.match(error.message, /boom/);
        return true;
      },
    );
  } finally {
    console.log = originalLog;
  }
});

test('GitHub workflow verifies every push before master deployment', () => {
  const workflow = yaml.load(
    readFileSync(path.join(repoRoot, '.github', 'workflows', 'deploy.yml'), 'utf8'),
    { schema: yaml.JSON_SCHEMA },
  );
  assert.ok(Object.hasOwn(workflow.on, 'push'));
  assert.ok(Object.hasOwn(workflow.on, 'pull_request'));
  assert.ok(Object.hasOwn(workflow.on, 'workflow_dispatch'));
  assert.equal(workflow.jobs.deploy.needs, 'verify');
  assert.match(workflow.jobs.deploy.if, /refs\/heads\/master/);

  const setupNode = workflow.jobs.verify.steps.find((step) => step.uses === 'actions/setup-node@v4');
  assert.equal(setupNode.with['node-version'], 22);
  assert.ok(workflow.jobs.verify.steps.some((step) => step.run === 'npm run verify:push'));
});

test('Docker build copies the prepare installer before npm ci', () => {
  const dockerfile = readFileSync(path.join(repoRoot, 'Dockerfile'), 'utf8');
  const installerCopy = dockerfile.indexOf(
    'COPY scripts/install-git-hooks.js ./scripts/install-git-hooks.js',
  );
  const npmInstall = dockerfile.indexOf('npm ci --omit=dev');
  assert.notEqual(installerCopy, -1);
  assert.notEqual(npmInstall, -1);
  assert.ok(installerCopy < npmInstall);
});
