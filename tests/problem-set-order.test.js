import test from 'node:test';
import assert from 'node:assert/strict';
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
    '2026-codeforces',
    '2025-codeforces',
    '2026-cspj-summer-first-prize',
    'luogu-official-basic-training',
    'luogu-official-advanced-training',
    'luogu-luoyongjun',
    'luogu-jinjiezhinan',
    'vjudge-shenru-qianchu-jinjie',
    'cps-j-math',
    'luogu-trial-ground',
    'luogu-trial-ground-popular',
    'luogu-trial-ground-advanced',
    'luogu-trial-ground-provincial',
    'greedy-basic',
    'search-basic',
    'data-structure-basic',
    'binary-two-pointers-basic',
    'graph-basic',
    'knapsack-basic',
    'string-basic',
    'tree-basic',
    'leetcode-hot-100',
    'haskell-practice',
    '2026-summer-practice',
    'csp-j-past',
    'csp-s-past',
    'csp-j-400',
    'csp-s-400',
  ]);
});
