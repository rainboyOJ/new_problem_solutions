import test from 'node:test';
import assert from 'node:assert/strict';
import { readFileSync } from 'node:fs';
import { compareProblemSets } from '../lib/problem-set.js';

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

test('compareProblemSets keeps pinned sets ahead of every ordered set', () => {
  const items = [
    { slug: 'ordered-first', order: 0, pinned: false },
    { slug: 'pinned-late', order: 900, pinned: true },
    { slug: 'unordered', order: null, pinned: false },
  ];

  assert.deepEqual(items.sort(compareProblemSets).map((item) => item.slug), [
    'pinned-late',
    'ordered-first',
    'unordered',
  ]);
});

test('compareProblemSets orders pinned sets among themselves by order', () => {
  const items = [
    { slug: 'pinned-b', order: 20, pinned: true },
    { slug: 'pinned-a', order: 10, pinned: true },
    { slug: 'plain', order: 0, pinned: false },
  ];

  assert.deepEqual(items.sort(compareProblemSets).map((item) => item.slug), [
    'pinned-a',
    'pinned-b',
    'plain',
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
