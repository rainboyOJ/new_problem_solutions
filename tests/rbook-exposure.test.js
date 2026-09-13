import test from 'node:test';
import assert from 'node:assert/strict';
import fs from 'node:fs';
import os from 'node:os';
import path from 'node:path';
import { buildApp } from '../app.js';
import ProblemManager, { normalizeShowAtRbook, sortProblemsForApi } from '../lib/problem.js';

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

test('showAtRbook normalizes optional arrays and rejects invalid values', () => {
  assert.deepEqual(normalizeShowAtRbook(undefined), []);
  assert.deepEqual(normalizeShowAtRbook([' bit ', 'bit', 'treap']), ['bit', 'treap']);
  assert.throws(() => normalizeShowAtRbook('bit'), /array of strings/);
  assert.throws(() => normalizeShowAtRbook(['']), /non-empty strings/);
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
    { oj: 'test', problem_id: 'medium', title: 'Medium', difficulty: '提高', dateA: 3, showAtRbook: ['bit'], tags: [] },
    { oj: 'test', problem_id: 'easy', title: 'Easy', difficulty: '入门', dateA: 2, showAtRbook: ['bit'], tags: [] },
    { oj: 'test', problem_id: 'other', title: 'Other', difficulty: '入门', dateA: 1, showAtRbook: ['treap'], tags: [] },
  ]);
  const app = await buildApp({ logger: false, problemManager: manager, contentService: createContentService() });

  try {
    const response = await app.inject({
      method: 'GET',
      url: '/api/problems?showAtRbook=bit&sort=difficulty&order=asc&limit=20',
    });

    assert.equal(response.statusCode, 200);
    const payload = response.json();
    assert.deepEqual(payload.data.map((item) => item.problem_id), ['easy', 'medium']);
    assert.deepEqual(payload.data[0].showAtRbook, ['bit']);

    const detail = await app.inject({ method: 'GET', url: '/api/problems/test/easy' });
    assert.equal(detail.statusCode, 200);
    assert.deepEqual(detail.json().showAtRbook, ['bit']);

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
