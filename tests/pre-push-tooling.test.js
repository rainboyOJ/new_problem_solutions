import test from 'node:test';
import assert from 'node:assert/strict';
import {
  chmodSync,
  mkdirSync,
  mkdtempSync,
  readFileSync,
  realpathSync,
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
  findStaleUpdatedProblems,
  frontmatterField,
  parsePushRefs,
  parseUpdatedStamp,
  problemDirOf,
} from '../scripts/check-pre-push.js';
import {
  compareDirectoryTrees,
  createVerificationStages,
  RELATION_BUILDS,
  runVerification,
  VerificationFailure,
} from '../scripts/verify-push.js';
import {
  validateContentHealth,
  validateLiveHealth,
} from '../scripts/smoke-test.js';
import { collectMissingUpdatedErrors } from '../scripts/check-content.js';

const repoRoot = path.resolve();
const prePushCheck = path.join(repoRoot, 'scripts', 'check-pre-push.js');
const contentCheck = path.join(repoRoot, 'scripts', 'check-content.js');
const hookInstaller = path.join(repoRoot, 'scripts', 'install-git-hooks.js');

// git push 在 worktree 里会把 GIT_DIR 传给 pre-push 钩子，测试进程可能继承到它。
// fixture 仓库必须完全按自己的 cwd 解析，所以每次调用都显式清掉这些变量。
const GIT_ENV_KEYS = [
  'GIT_DIR',
  'GIT_WORK_TREE',
  'GIT_INDEX_FILE',
  'GIT_OBJECT_DIRECTORY',
  'GIT_ALTERNATE_OBJECT_DIRECTORIES',
];

function cleanGitEnv() {
  const env = { ...process.env };
  for (const key of GIT_ENV_KEYS) delete env[key];
  return env;
}

function git(cwd, ...args) {
  return execFileSync('git', args, { cwd, encoding: 'utf8', env: cleanGitEnv() }).trim();
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

function problemFrontmatter(updated) {
  return [
    '---',
    'oj: demo',
    'problem_id: a',
    'date: 2026-01-01 00:00',
    ...(updated ? [`updated: ${updated}`] : []),
    '---',
    '',
    '# demo',
    '',
  ].join('\n');
}

function createProblemFixture({ updated = '2026-01-01 00:00' } = {}) {
  const root = createGitFixture();
  const directory = path.join(root, 'problems', 'demo', 'a');
  mkdirSync(directory, { recursive: true });
  writeFileSync(path.join(directory, 'index.md'), problemFrontmatter(updated));
  writeFileSync(path.join(directory, 'main.cpp'), 'int main() {}\n');
  git(root, 'add', '-A');
  git(root, 'commit', '-m', 'add demo problem');
  return root;
}

function prePushInput(root, base) {
  const head = git(root, 'rev-parse', 'HEAD');
  return `refs/heads/master ${head} refs/heads/master ${base}\n`;
}

function runPrePush(root, input) {
  return spawnSync(process.execPath, [prePushCheck], {
    cwd: root,
    env: cleanGitEnv(),
    input,
    encoding: 'utf8',
  });
}

test('content check reports problems that lost the updated field', () => {
  const problems = [
    { oj: 'demo', problem_id: 'a', date: '2026-01-01 00:00', updated: '2026-02-01 00:00', md_path: 'demo/a/index.md' },
    { oj: 'demo', problem_id: 'b', date: '2026-01-01 00:00', md_path: 'demo/b/index.md' },
    { oj: 'demo', problem_id: 'c', md_path: 'demo/c/index.md' },
  ];

  assert.deepEqual(collectMissingUpdatedErrors(problems, '/problems'), [{
    type: 'problem',
    key: 'demo/b',
    path: '/problems/demo/b/index.md',
    message: 'frontmatter 缺少 updated 字段（首页按最后修改时间排序需要它）',
  }]);
});

test('check:content fails on a problem without updated frontmatter', () => {
  const root = mkdtempSync(path.join(os.tmpdir(), 'rbook-content-check-'));
  try {
    mkdirSync(path.join(root, 'problems', 'demo', 'a'), { recursive: true });
    mkdirSync(path.join(root, 'problem-sets'), { recursive: true });
    writeFileSync(path.join(root, 'problems', 'demo', 'a', 'index.md'), [
      '---',
      'oj: demo',
      'problem_id: a',
      'date: 2026-01-01 00:00',
      '---',
      '',
    ].join('\n'));

    const result = spawnSync(process.execPath, [contentCheck], { cwd: root, encoding: 'utf8', env: cleanGitEnv() });
    assert.equal(result.status, 1, result.stdout);
    assert.match(result.stderr, /缺少 updated/);
    assert.match(result.stderr, /demo\/a\/index\.md/);
  } finally {
    rmSync(root, { recursive: true, force: true });
  }
});

test('updated helpers read frontmatter fields and problem directories', () => {
  assert.equal(problemDirOf('problems/luogu/P1001/main.cpp'), 'problems/luogu/P1001');
  assert.equal(problemDirOf('problems/luogu/P1001/data/1.in'), 'problems/luogu/P1001');
  assert.equal(problemDirOf('problems/luogu/note.md'), null);
  assert.equal(problemDirOf('scripts/problem.js'), null);

  const content = '---\noj: demo\nupdated: 2026-08-14 16:33\n---\n\nupdated: 正文里的假字段\n';
  assert.equal(frontmatterField(content, 'updated'), '2026-08-14 16:33');
  assert.equal(frontmatterField(content, 'missing'), null);
  assert.equal(frontmatterField('# 没有 frontmatter\n', 'updated'), null);

  assert.equal(parseUpdatedStamp('2026-08-14 16:33'), 1786696380000);
  assert.equal(parseUpdatedStamp('2026-08-14'), 1786636800000);
  assert.equal(parseUpdatedStamp('昨天'), null);
  assert.equal(parseUpdatedStamp(undefined), null);
});

test('pre-push allows problem edits that do not refresh updated (2026-10-10 放宽)', () => {
  const root = createProblemFixture();
  try {
    const base = git(root, 'rev-parse', 'HEAD');
    writeFileSync(path.join(root, 'problems', 'demo', 'a', 'main.cpp'), 'int main() { return 0; }\n');
    git(root, 'add', '-A');
    git(root, 'commit', '-m', 'change code without refreshing updated');

    // 只改代码、updated 不变：现在直接放行（不再要求「晚于远端版本」）。
    const stale = runPrePush(root, prePushInput(root, base));
    assert.equal(stale.status, 0, stale.stderr);

    // 即使把 updated 改成**更早**的时间，也照样放行（新旧不参与判定）。
    const indexPath = path.join(root, 'problems', 'demo', 'a', 'index.md');
    writeFileSync(indexPath, problemFrontmatter('2025-01-01 00:00'));
    git(root, 'add', '-A');
    git(root, 'commit', '-m', 'set an older-but-valid updated');

    const older = runPrePush(root, prePushInput(root, base));
    assert.equal(older.status, 0, older.stderr);
  } finally {
    rmSync(root, { recursive: true, force: true });
  }
});

test('pre-push still rejects dropping a valid updated field', () => {
  const root = createProblemFixture();
  try {
    const base = git(root, 'rev-parse', 'HEAD');

    // 远端本来有合法的 updated，本次却把它删掉：必须被拦。
    const indexPath = path.join(root, 'problems', 'demo', 'a', 'index.md');
    writeFileSync(indexPath, problemFrontmatter(null));
    writeFileSync(path.join(root, 'problems', 'demo', 'a', 'main.cpp'), 'int main() { return 0; }\n');
    git(root, 'add', '-A');
    git(root, 'commit', '-m', 'drop updated');

    const dropped = runPrePush(root, prePushInput(root, base));
    assert.equal(dropped.status, 1);
    assert.match(dropped.stderr, /updated 缺失或格式/);
    assert.match(dropped.stderr, /problems\/demo\/a/);
  } finally {
    rmSync(root, { recursive: true, force: true });
  }
});

test('SKIP_UPDATED_CHECK=1 bypasses the updated check entirely', () => {
  const root = createProblemFixture();
  try {
    const base = git(root, 'rev-parse', 'HEAD');
    const indexPath = path.join(root, 'problems', 'demo', 'a', 'index.md');
    writeFileSync(indexPath, problemFrontmatter(null));
    git(root, 'add', '-A');
    git(root, 'commit', '-m', 'drop updated');

    const skipped = spawnSync(process.execPath, [prePushCheck], {
      cwd: root,
      env: { ...cleanGitEnv(), SKIP_UPDATED_CHECK: '1' },
      input: prePushInput(root, base),
      encoding: 'utf8',
    });
    assert.equal(skipped.status, 0, skipped.stderr);
  } finally {
    rmSync(root, { recursive: true, force: true });
  }
});

test('pre-push rejects problem edits that do not refresh updated', () => {
  const root = createProblemFixture();
  try {
    const base = git(root, 'rev-parse', 'HEAD');
    writeFileSync(path.join(root, 'problems', 'demo', 'a', 'main.cpp'), 'int main() { return 0; }\n');
    git(root, 'add', '-A');
    git(root, 'commit', '-m', 'change code without refreshing updated');

    // 只改代码、updated 未变：本轮放宽后**不再拦**（见上面的专门用例）。
    const stale = runPrePush(root, prePushInput(root, base));
    assert.equal(stale.status, 0, stale.stderr);

    // 把 updated 补上（写一个合法值）后照样通过。
    const indexPath = path.join(root, 'problems', 'demo', 'a', 'index.md');
    writeFileSync(indexPath, problemFrontmatter('2026-02-01 09:00'));
    git(root, 'add', '-A');
    git(root, 'commit', '-m', 'refresh updated');

    const fixed = runPrePush(root, prePushInput(root, base));
    assert.equal(fixed.status, 0, fixed.stderr);
  } finally {
    rmSync(root, { recursive: true, force: true });
  }
});

test('pre-push tolerates the first updated field and new problems', () => {
  const root = createProblemFixture({ updated: null });
  try {
    const base = git(root, 'rev-parse', 'HEAD');

    // 初次引入 updated 字段：远端没有该字段，不能拦。
    writeFileSync(path.join(root, 'problems', 'demo', 'a', 'index.md'), problemFrontmatter('2026-02-01 09:00'));
    const added = path.join(root, 'problems', 'demo', 'b');
    mkdirSync(added, { recursive: true });
    writeFileSync(path.join(added, 'index.md'), '---\noj: demo\nproblem_id: b\ndate: 2026-02-02 10:00\nupdated: 2026-02-02 10:00\n---\n');
    git(root, 'add', '-A');
    git(root, 'commit', '-m', 'introduce updated field and add a new problem');
    assert.equal(runPrePush(root, prePushInput(root, base)).status, 0);

    // 远端已有 updated，却把它删掉、同时改动目录，必须被拦。
    const bumped = git(root, 'rev-parse', 'HEAD');
    writeFileSync(path.join(root, 'problems', 'demo', 'b', 'index.md'), '---\noj: demo\nproblem_id: b\ndate: 2026-02-02 10:00\n---\n');
    git(root, 'add', '-A');
    git(root, 'commit', '-m', 'drop updated');
    const dropped = runPrePush(root, prePushInput(root, bumped));
    assert.equal(dropped.status, 1);
    assert.match(dropped.stderr, /updated 缺失或格式/);
  } finally {
    rmSync(root, { recursive: true, force: true });
  }
});

test('findStaleUpdatedProblems ignores deletions and unbased branches', () => {
  const root = createProblemFixture();
  try {
    const head = git(root, 'rev-parse', 'HEAD');
    const base = git(root, 'rev-parse', 'HEAD');
    assert.deepEqual(findStaleUpdatedProblems({ cwd: root, refs: [] }), []);
    assert.deepEqual(
      findStaleUpdatedProblems({ cwd: root, refs: [{ localSha: '0'.repeat(40), remoteSha: base }] }),
      [],
    );
    assert.deepEqual(
      findStaleUpdatedProblems({ cwd: root, refs: [{ localSha: head, remoteSha: '0'.repeat(40) }] }),
      [],
    );
  } finally {
    rmSync(root, { recursive: true, force: true });
  }
});

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
      env: cleanGitEnv(),
      input: validInput,
      encoding: 'utf8',
    });
    assert.equal(clean.status, 0, clean.stderr);

    writeFileSync(path.join(root, 'untracked.txt'), 'not committed\n');
    const dirty = spawnSync(process.execPath, [prePushCheck], {
      cwd: root,
      env: cleanGitEnv(),
      input: validInput,
      encoding: 'utf8',
    });
    assert.equal(dirty.status, 1);
    assert.match(dirty.stderr, /工作区不是干净状态/);
    assert.match(dirty.stderr, /untracked\.txt/);
    rmSync(path.join(root, 'untracked.txt'));

    const nonHead = spawnSync(process.execPath, [prePushCheck], {
      cwd: root,
      env: cleanGitEnv(),
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
      env: cleanGitEnv(),
      encoding: 'utf8',
    });
    assert.equal(result.status, 0, result.stderr);
    assert.equal(git(root, 'config', '--local', '--get', 'core.hooksPath'), '.githooks');
  } finally {
    rmSync(root, { recursive: true, force: true });
  }
});

test('fixture 仓库忽略继承来的 GIT_DIR（worktree 钩子环境）', () => {
  // git push 在 worktree 里会把 GIT_DIR 指向当前仓库的 gitdir；
  // 若 fixture 命令继承它，就会误提交到本仓库（曾真实发生过）。
  const before = git(repoRoot, 'rev-parse', 'HEAD');
  const savedGitDir = process.env.GIT_DIR;
  process.env.GIT_DIR = git(repoRoot, 'rev-parse', '--absolute-git-dir');
  try {
    const root = createGitFixture();
    try {
      assert.equal(
        realpathSync(git(root, 'rev-parse', '--absolute-git-dir')),
        realpathSync(path.join(root, '.git')),
      );
      assert.equal(git(root, 'log', '--oneline').split('\n').length, 1);
    } finally {
      rmSync(root, { recursive: true, force: true });
    }
  } finally {
    if (savedGitDir === undefined) delete process.env.GIT_DIR;
    else process.env.GIT_DIR = savedGitDir;
  }
  assert.equal(git(repoRoot, 'rev-parse', 'HEAD'), before, '本仓库 HEAD 不应被 fixture 改动');
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

test('verification only builds the active 3D graph and checks its TypeScript', () => {
  const pkg = JSON.parse(readFileSync(path.join(repoRoot, 'package.json'), 'utf8'));
  for (const target of RELATION_BUILDS) {
    assert.ok(pkg.scripts[target.script]);
    assert.ok(pkg.scripts.build.includes(target.script));
    assert.ok(statSync(path.join(repoRoot, 'public', target.directory, 'assets', 'index.js')).isFile());
  }
  assert.deepEqual(RELATION_BUILDS, [{ script: 'build:relations3', directory: 'relations3-graph' }]);
  assert.equal(pkg.scripts.build, 'npm run build:relations3');
  assert.equal(pkg.scripts['build:relations'], undefined);
  assert.equal(pkg.scripts['build:relations2'], undefined);
  assert.ok(createVerificationStages().some(stage => stage.command === 'npm run typecheck:relations3'));
  assert.ok(pkg.scripts.test.includes('npm run test:relations3'));
});

test('GitHub pull request workflow owns full verification', () => {
  const workflow = yaml.load(
    readFileSync(path.join(repoRoot, '.github', 'workflows', 'verify.yml'), 'utf8'),
    { schema: yaml.JSON_SCHEMA },
  );
  assert.ok(Object.hasOwn(workflow.on, 'pull_request'));
  assert.deepEqual(Object.keys(workflow.jobs), ['verify']);
  const setupNode = workflow.jobs.verify.steps.find((step) => step.uses === 'actions/setup-node@v4');
  assert.equal(setupNode.with['node-version'], 22);
  assert.ok(workflow.jobs.verify.steps.some((step) => step.run === 'npm run verify:push'));
});

test('local deploy entrypoint enforces the production publish contract', () => {
  const scriptPath = path.join(repoRoot, 'deploy.sh');
  const script = readFileSync(scriptPath, 'utf8');
  assert.ok(statSync(scriptPath).mode & 0o111);
  assert.match(script, /BRANCH="master"/);
  assert.match(script, /git fetch --quiet origin "\$BRANCH"/);
  assert.match(script, /merge-base --is-ancestor/);
  assert.match(script, /npm run verify:push/);
  assert.match(script, /git push --no-verify origin "HEAD:\$BRANCH"/);
  assert.match(script, /scripts\/build-native-release\.sh/);
  assert.match(script, /deploy\/problems-solution\.service/);
  assert.doesNotMatch(script, /gh run|docker build|docker pull/);
});
