import test from 'node:test';
import assert from 'node:assert/strict';
import fs from 'fs';
import os from 'os';
import path from 'path';

import { readMarkdownWithIncludes } from '../lib/markdown-includes.js';

function makeTempTree(t) {
  const root = fs.mkdtempSync(path.join(os.tmpdir(), 'rbook-markdown-includes-'));
  t.after(() => fs.rmSync(root, { recursive: true, force: true }));
  return root;
}

function writeFile(filePath, content) {
  fs.mkdirSync(path.dirname(filePath), { recursive: true });
  fs.writeFileSync(filePath, content);
}

test('readMarkdownWithIncludes expands code with explicit and inferred languages', (t) => {
  const root = makeTempTree(t);
  const markdownPath = path.join(root, 'index.md');
  writeFile(path.join(root, 'main.py'), 'print("root")\n');
  writeFile(markdownPath, [
    '@include-code(./main.py, javascript)',
    '@include-code(./main.py)',
  ].join('\n'));

  assert.equal(readMarkdownWithIncludes(markdownPath), [
    '```javascript',
    'print("root")',
    '```',
    '```py',
    'print("root")',
    '```',
  ].join('\n'));
});

test('readMarkdownWithIncludes resolves nested directives from their Markdown files', (t) => {
  const root = makeTempTree(t);
  const markdownPath = path.join(root, 'index.md');
  writeFile(path.join(root, 'main.js'), 'console.log("root");\n');
  writeFile(path.join(root, 'chapters', 'snippet.ts'), 'console.log("chapter");\n');
  writeFile(path.join(root, 'chapters', 'deep', 'main.py'), 'print("deep")\n');
  writeFile(path.join(root, 'chapters', 'deep', 'detail.md'), [
    '## Deep',
    '@include-code(./main.py, python)',
  ].join('\n'));
  writeFile(path.join(root, 'chapters', 'part.md'), [
    '## Part',
    '@include-code(./snippet.ts)',
    '@include_md("./deep/detail.md")',
  ].join('\n'));
  writeFile(markdownPath, [
    '# Root',
    '@include-code(./main.js)',
    '@include_md("./chapters/part.md")',
  ].join('\n'));

  const expanded = readMarkdownWithIncludes(markdownPath);

  assert.match(expanded, /```js\nconsole\.log\("root"\);\n```/);
  assert.match(expanded, /```ts\nconsole\.log\("chapter"\);\n```/);
  assert.match(expanded, /```python\nprint\("deep"\)\n```/);
  assert.doesNotMatch(expanded, /@include(?:-code|_md)/);
});

test('readMarkdownWithIncludes uses a fence longer than source backtick runs', (t) => {
  const root = makeTempTree(t);
  const markdownPath = path.join(root, 'index.md');
  const source = 'first\n`````\nlast\n';
  writeFile(path.join(root, 'example.md'), source);
  writeFile(markdownPath, [
    'before',
    '',
    '@include-code(./example.md, markdown)',
    '',
    'after',
    '',
  ].join('\n'));

  assert.equal(readMarkdownWithIncludes(markdownPath), [
    'before',
    '',
    '``````markdown',
    'first',
    '`````',
    'last',
    '``````',
    '',
    'after',
    '',
  ].join('\n'));
});

test('readMarkdownWithIncludes preserves source endings at fence boundaries', (t) => {
  const cases = [
    { name: 'empty', source: '', expected: '```text\n```' },
    { name: 'no-newline', source: 'alpha', expected: '```text\nalpha\n```' },
    { name: 'one-newline', source: 'alpha\n', expected: '```text\nalpha\n```' },
    { name: 'two-newlines', source: 'alpha\n\n', expected: '```text\nalpha\n\n```' },
  ];

  for (const item of cases) {
    const root = makeTempTree(t);
    const markdownPath = path.join(root, 'index.md');
    writeFile(path.join(root, `${item.name}.txt`), item.source);
    writeFile(markdownPath, `@include-code(./${item.name}.txt, text)`);

    assert.equal(readMarkdownWithIncludes(markdownPath), item.expected, item.name);
  }
});

test('readMarkdownWithIncludes preserves failed and malformed code directives', (t) => {
  const root = makeTempTree(t);
  const markdownPath = path.join(root, 'index.md');
  fs.mkdirSync(path.join(root, 'directory'));
  const content = [
    '@include-code(./missing.py, python)',
    '@include-code(./directory, text)',
    '@include-code(, cpp)',
    'prefix @include-code(./missing.py, python)',
  ].join('\n');
  writeFile(markdownPath, content);

  assert.equal(readMarkdownWithIncludes(markdownPath), content);
});

test('readMarkdownWithIncludes retains the existing missing Markdown warning', (t) => {
  const root = makeTempTree(t);
  const markdownPath = path.join(root, 'index.md');
  writeFile(markdownPath, '@include_md("./missing.md")');

  assert.equal(
    readMarkdownWithIncludes(markdownPath),
    '<!-- Warning: File not found: ./missing.md -->',
  );
});
