import test from 'node:test';
import assert from 'node:assert/strict';
import { readFileSync } from 'node:fs';
import ProblemSetManager, { compareProblemSets } from '../lib/problem-set.js';

test('compareProblemSets uses explicit order instead of modification time', () => {
  const items = [
    { slug: 'late', order: 20, updatedAt: 300 },
    { slug: 'early', order: 10, updatedAt: 100 },
  ];

  assert.deepEqual(items.sort(compareProblemSets).map((item) => item.slug), ['early', 'late']);
});

test('compareProblemSets uses stable slug fallbacks for ties and missing orders', () => {
  const items = [
    { slug: 'unordered-z', order: null },
    { slug: 'ordered-z', order: 10 },
    { slug: 'ordered-a', order: 10 },
    { slug: 'invalid', order: Number.NaN },
    { slug: 'unordered-a', order: null },
  ];

  assert.deepEqual(items.sort(compareProblemSets).map((item) => item.slug), [
    'ordered-a',
    'ordered-z',
    'invalid',
    'unordered-a',
    'unordered-z',
  ]);
});

test('ProblemSetManager lists the existing problem sets in their explicit order', () => {
  const manager = new ProblemSetManager(null);

  assert.deepEqual(manager.list().map((item) => item.slug), [
    'luogu-trial-ground',
    'luogu-official-basic-training',
    'greedy-basic',
    'search-basic',
    'data-structure-basic',
    'binary-two-pointers-basic',
    'string-basic',
    'graph-basic',
    'tree-basic',
    'knapsack-basic',
    'luogu-trial-ground-popular',
    'cps-j-math',
    'csp-j-past',
    'csp-j-400',
    '2026-cspj-summer-first-prize',
    'luogu-trial-ground-advanced',
    'luogu-official-advanced-training',
    '2026-summer-practice',
    'csp-s-past',
    'csp-s-400',
    'luogu-trial-ground-provincial',
    'luogu-luoyongjun',
    'vjudge-shenru-qianchu-jinjie',
    'luogu-jinjiezhinan',
    'noi-openjudge-basic',
    '2025-codeforces',
    '2026-codeforces',
    'leetcode-hot-100',
    'haskell-practice',
  ]);
});

test('OpenJudge problem set includes the complete ch0101 chapter', () => {
  const source = readFileSync('problem-sets/noi-openjudge-basic.md', 'utf8');
  const chapter = source.match(/## 1\.1 编程基础之输入输出（10 题）\n\n([\s\S]*?)\n\n## /);

  assert.ok(chapter);
  assert.equal((source.match(/^\- \[ \] \[\[problem: noi_openjudge,/gm) || []).length, 617);
  assert.equal((chapter[1].match(/^\- \[ \]/gm) || []).length, 10);
  assert.match(chapter[1], /\[\[problem: noi_openjudge,ch0101-01\]\]/);
  assert.match(chapter[1], /\[\[problem: noi_openjudge,ch0101-10\]\]/);
  assert.doesNotMatch(source, /ch0101-(clarify|ranking|status)/);
});
