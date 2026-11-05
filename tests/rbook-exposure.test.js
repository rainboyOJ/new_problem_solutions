import test from 'node:test';
import assert from 'node:assert/strict';
import fs from 'node:fs';
import os from 'node:os';
import path from 'node:path';
import { buildApp } from '../app.js';
import ProblemManager, {
  normalizeRbookLinks,
  normalizeShowAtRbook,
  sortProblemsForApi,
} from '../lib/problem.js';

function createContentService() {
  return {
    state: 'ready',
    acquireRequest() {
      return () => {};
    },
    render() {
      return { html_content: '', md_content: '' };
    },
  };
}

function createManager(problems) {
  const manager = new ProblemManager({ auto_load: false, baseDir: path.join(os.tmpdir(), 'unused-rbook-exposure-problems') });
  manager.problems = problems.map((problem) => manager.normalizeProblem({ md_path: 'test/index.md', ...problem }));
  manager.buildIndex();
  return manager;
}

test('showAtRbook 要求站点前缀并去重', () => {
  assert.deepEqual(normalizeShowAtRbook(undefined), []);
  assert.deepEqual(
    normalizeShowAtRbook([' rbook2:bit ', 'rbook2:bit', 'rbook1:treap']),
    ['rbook2:bit', 'rbook1:treap'],
  );
  assert.throws(() => normalizeShowAtRbook('bit'), /array of strings/);
  assert.throws(() => normalizeShowAtRbook(['bit']), /必须写成 rbook1:<id> 或 rbook2:<id>/);
  assert.throws(() => normalizeShowAtRbook(['rbook3:bit']), /必须写成 rbook1:<id> 或 rbook2:<id>/);
  assert.throws(() => normalizeShowAtRbook(['rbook2:bit#anchor']), /不能带锚点/);
  assert.throws(() => normalizeShowAtRbook(['']), /必须是非空字符串/);
});

test('rbookLinks 校验 id/url 二选一、label 与 reason', () => {
  assert.deepEqual(normalizeRbookLinks(undefined), []);

  // id 形态：reason 必填，label 不允许
  assert.deepEqual(
    normalizeRbookLinks([{ id: 'rbook2:bit', reason: '先读树状数组' }]),
    [{ id: 'rbook2:bit', reason: '先读树状数组' }],
  );
  assert.throws(() => normalizeRbookLinks([{ id: 'rbook2:bit' }]), /必须写 reason/);
  assert.throws(() => normalizeRbookLinks([{ id: 'rbook2:bit', reason: 'x', label: 'y' }]), /不要写 label/);
  assert.throws(() => normalizeRbookLinks([{ id: 'bit', reason: 'x' }]), /必须写成 rbook1:<id> 或 rbook2:<id>/);

  // url 形态：必须 http(s) 绝对地址且带 label
  assert.deepEqual(
    normalizeRbookLinks([{ url: 'https://rbook.roj.ac.cn/base/presum/index.html#sec', label: '前缀和', reason: 'x' }]),
    [{ url: 'https://rbook.roj.ac.cn/base/presum/index.html#sec', label: '前缀和', reason: 'x' }],
  );
  assert.throws(() => normalizeRbookLinks([{ url: 'https://rbook.roj.ac.cn/a', reason: 'x' }]), /必须写 label/);
  assert.throws(() => normalizeRbookLinks([{ url: '/base/presum/', label: '前缀和', reason: 'x' }]), /http\(s\) 绝对地址/);
  assert.throws(() => normalizeRbookLinks([{ url: 'https://a.test/x', id: 'rbook2:bit', label: 'l', reason: 'x' }]), /二选一/);

  // 重复项去重
  assert.deepEqual(
    normalizeRbookLinks([
      { id: 'rbook2:bit', reason: '一' },
      { id: 'rbook2:bit', reason: '二' },
    ]),
    [{ id: 'rbook2:bit', reason: '一' }],
  );
});

test('difficulty sorting keeps unknown values last in both directions', () => {
  const problems = [
    { problem_id: 'unknown', difficulty: '未知', dateA: 1 },
    { problem_id: 'easy', difficulty: '入门', dateA: 1 },
    { problem_id: 'medium', difficulty: '提高', dateA: 1 },
  ];

  assert.deepEqual(
    sortProblemsForApi(problems, 'difficulty', 'asc').map((item) => item.problem_id),
    ['easy', 'medium', 'unknown'],
  );
  assert.deepEqual(
    sortProblemsForApi(problems, 'difficulty', 'desc').map((item) => item.problem_id),
    ['medium', 'easy', 'unknown'],
  );
});

test('API filters by rbook exposure and returns difficulty-sorted results', async () => {
  const manager = createManager([
    { oj: 'test', problem_id: 'medium', title: 'Medium', difficulty: '提高', dateA: 3, showAtRbook: ['rbook2:bit'], tags: [] },
    { oj: 'test', problem_id: 'easy', title: 'Easy', difficulty: '入门', dateA: 2, showAtRbook: ['rbook2:bit'], tags: [] },
    { oj: 'test', problem_id: 'other', title: 'Other', difficulty: '入门', dateA: 1, showAtRbook: ['rbook2:treap'], tags: [] },
  ]);
  const app = await buildApp({ logger: false, problemManager: manager, contentService: createContentService() });

  try {
    const response = await app.inject({
      method: 'GET',
      url: '/api/problems?showAtRbook=rbook2%3Abit&sort=difficulty&order=asc&limit=20',
    });

    assert.equal(response.statusCode, 200);
    const payload = response.json();
    assert.deepEqual(payload.data.map((item) => item.problem_id), ['easy', 'medium']);
    assert.deepEqual(payload.data[0].showAtRbook, ['rbook2:bit']);

    const detail = await app.inject({ method: 'GET', url: '/api/problems/test/easy' });
    assert.equal(detail.statusCode, 200);
    assert.deepEqual(detail.json().showAtRbook, ['rbook2:bit']);

  } finally {
    await app.close();
  }
});

test('invalid showAtRbook front matter is rejected by catalog validation', () => {
  const root = fs.mkdtempSync(path.join(os.tmpdir(), 'pcs2-rbook-exposure-'));
  const problemDir = path.join(root, 'test', 'broken');
  fs.mkdirSync(problemDir, { recursive: true });
  fs.writeFileSync(path.join(problemDir, 'index.md'), [
    '---',
    'oj: test',
    'problem_id: broken',
    'showAtRbook: bit',
    '---',
    '',
  ].join('\n'));

  try {
    const manager = new ProblemManager({ auto_load: false, baseDir: root });
    const catalog = manager.buildCatalog();
    assert.equal(catalog.problems.length, 0);
    assert.match(catalog.errors[0].message, /showAtRbook must be an array/);
  } finally {
    fs.rmSync(root, { recursive: true, force: true });
  }
});
