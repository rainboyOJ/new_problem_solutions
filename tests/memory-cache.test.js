import test from 'node:test';
import assert from 'node:assert/strict';
import fs from 'node:fs';
import os from 'node:os';
import path from 'node:path';
import matter from 'gray-matter';
import LruCache from '../lib/lru-cache.js';
import parseFrontmatter from '../lib/frontmatter.js';
import MarkdownRenderer from '../lib/markdown.js';
import ProblemManager from '../lib/problem.js';
import ProblemSetManager from '../lib/problem-set.js';
import ContentService from '../lib/content-service.js';
import { readAiNoteMarkdown, readAiNoteRawContent, scanAiNotes } from '../lib/ai-notes.js';
import { resolvePreviewProblemFromIndex } from '../lib/preview-state.js';
import { getHighlightCacheStats, renderCodeHtml } from '../lib/highlight.js';

test('LRU evicts by bytes in access order and accounts for overwrite, delete and clear', () => {
  const cache = new LruCache(10, { maxBytes: 10, sizeOf: (value) => value.length });
  cache.set('a', 'aaaa');
  cache.set('b', 'bbbb');
  cache.get('a');
  cache.set('c', 'cccc');
  assert.equal(cache.get('b'), undefined);
  assert.equal(cache.bytes, 8);
  cache.set('a', 'aa');
  assert.equal(cache.bytes, 6);
  cache.delete('c');
  assert.equal(cache.bytes, 2);
  cache.clear();
  assert.equal(cache.bytes, 0);
  assert.equal(cache.size, 0);
});

test('oversized renders are returned without evicting useful entries or retaining stale values', () => {
  const cache = new LruCache(10, {
    maxBytes: 10, maxEntryBytes: 6, sizeOf: (value) => value.length,
  });
  cache.set('small', 'ok');
  assert.equal(cache.set('large', '1234567'), '1234567');
  assert.equal(cache.get('large'), undefined);
  assert.equal(cache.get('small'), 'ok');
  cache.set('small', '1234567');
  assert.equal(cache.get('small'), undefined);
  assert.equal(cache.bytes, 0);
});

test('text budgets count keys, Unicode and object payloads across many unique renders', () => {
  const cache = new LruCache(200, { maxBytes: 4096, maxEntryBytes: 1024 });
  for (let index = 0; index < 500; index += 1) {
    cache.set(`page-${index}`, { html: '中文'.repeat(100), statement: 'x'.repeat(100) });
    assert.ok(cache.bytes <= 4096);
  }
  assert.ok(cache.size > 0 && cache.size < 200);
  cache.set('x'.repeat(2048), 'small');
  assert.equal(cache.get('x'.repeat(2048)), undefined);
});

test('frontmatter parsing does not retain full sources, including malformed YAML', () => {
  const before = Object.keys(matter.cache);
  for (let index = 0; index < 50; index += 1) {
    const source = `---\ntitle: Article ${index}\n---\n${'body '.repeat(1000)}`;
    assert.equal(parseFrontmatter(source).data.title, `Article ${index}`);
  }
  assert.throws(() => parseFrontmatter('---\ntitle: [broken\n---\nbody'));
  assert.deepEqual(Object.keys(matter.cache), before);
});

test('catalog scans, included code, AI notes and preview leave no gray-matter cache behind', () => {
  const root = fs.mkdtempSync(path.join(os.tmpdir(), 'rbook-memory-'));
  const problemsRoot = path.join(root, 'problems');
  const problemDir = path.join(problemsRoot, 'test', 'one');
  const setsRoot = path.join(root, 'problem-sets');
  fs.mkdirSync(path.join(problemDir, 'talking_with_ai'), { recursive: true });
  fs.mkdirSync(setsRoot);
  const manager = new ProblemManager({ auto_load: false, baseDir: problemsRoot });
  const sets = new ProblemSetManager(manager, { auto_load: false, baseDir: setsRoot });
  const before = Object.keys(matter.cache);
  try {
    const indexPath = path.join(problemDir, 'index.md');
    fs.writeFileSync(indexPath, '---\noj: test\nproblem_id: one\ntitle: One\n---\n@include-code(./main.cpp, cpp)');
    for (let index = 0; index < 10; index += 1) {
      fs.writeFileSync(path.join(problemDir, 'main.cpp'), `int value = ${index};`);
      fs.writeFileSync(path.join(setsRoot, 'one.md'), `---\ntitle: Set ${index}\n---\n# Body ${index}`);
      fs.writeFileSync(path.join(problemDir, 'talking_with_ai', 'note.md'),
        `---\ntitle: Note\ndescription: Discussion\ndate: 2026-11-14\nslug: note\n---\n# Note\n\nBody ${index}`);
      assert.equal(manager.buildCatalog().errors.length, 0);
      assert.equal(sets.buildCatalog().errors.length, 0);
      assert.match(new MarkdownRenderer(indexPath, manager).toHTML(), /shiki-token/);
      const note = scanAiNotes(problemDir).notes[0];
      assert.match(readAiNoteMarkdown(problemDir, note), new RegExp(`Body ${index}`));
      assert.match(readAiNoteRawContent(problemDir, note), /^# Note/);
      assert.equal(resolvePreviewProblemFromIndex(indexPath, { projectRoot: root }).problem.title, 'One');
    }
    assert.deepEqual(Object.keys(matter.cache), before);
  } finally {
    fs.rmSync(root, { recursive: true, force: true });
  }
});

test('ContentService budgets both API and HTML payloads and does not quarantine large pages', () => {
  const service = new ContentService({ cacheMaxBytes: 4096, cacheMaxEntryBytes: 2048 });
  for (let index = 0; index < 500; index += 1) {
    const rendered = service.render('problem', `test/${index}`, () => ({
      html_content: 'x'.repeat(500), md_content: 'y'.repeat(100),
    }), 'api');
    assert.equal(rendered.html_content.length, 500);
    assert.ok(service.cache.bytes <= 4096);
  }
  let calls = 0;
  const factory = () => { calls += 1; return { htmlContent: '大'.repeat(3000) }; };
  assert.equal(service.render('problem', 'test/large', factory).htmlContent.length, 3000);
  service.render('problem', 'test/large', factory);
  assert.equal(calls, 2);
  assert.equal(service.errors.length, 0);
});

test('highlight cache stays bounded with unique code and skips oversized HTML', () => {
  for (let index = 0; index < 820; index += 1) {
    assert.match(renderCodeHtml(`int memory_test_${index} = ${index};`, 'cpp'), /shiki-token/);
  }
  const before = getHighlightCacheStats();
  assert.ok(before.entries <= 800);
  assert.ok(before.bytes <= 16 * 1024 * 1024);
  assert.match(renderCodeHtml(`// ${'x'.repeat(300_000)}`, 'cpp'), /shiki-token/);
  assert.deepEqual(getHighlightCacheStats(), before);
  assert.notEqual(renderCodeHtml('int x = 1;', 'cpp'), renderCodeHtml('int x = 2;', 'cpp'));
});

test('measuring a payload walks it instead of serialising it', () => {
  // A page-sized payload used to be JSON.stringify()ed purely to weigh it, which
  // cost milliseconds and allocated a temporary string as large as the page.
  const page = '<div>' + '内容'.repeat(200_000) + '</div>';
  const payload = { htmlContent: page, statementHtml: page, hasStatement: true };

  const stringified = 2 * JSON.stringify(payload).length;
  const cache = new LruCache(10, { maxBytes: stringified + 4096 });
  const started = process.hrtime.bigint();
  for (let index = 0; index < 20; index += 1) {
    cache.set(`page-${index}`, payload);
  }
  const elapsedMs = Number(process.hrtime.bigint() - started) / 1e6;

  assert.ok(cache.bytes > 0);
  // Serialising 20 copies took ~90ms on the deploy host; walking should be far
  // cheaper. Keep a generous ceiling so this stays a regression guard, not a benchmark.
  assert.ok(elapsedMs < 40, `weighing 20 pages took ${elapsedMs.toFixed(1)}ms`);
});

test('a payload that cannot be measured is still rendered and never quarantined', () => {
  const removed = [];
  const service = new ContentService({
    problemManager: {
      remove: (oj, id) => { removed.push(`${oj}/${id}`); return true; },
      getAll: () => [],
    },
    problemSetManager: { remove() {}, list() {}, baseDir: '/tmp' },
    cacheMaxBytes: 1024 * 1024,
    cacheMaxEntryBytes: 512 * 1024,
  });
  service.state = 'healthy';
  service.activeRevision = 'test';

  const circular = { htmlContent: 'ok' };
  circular.self = circular;
  assert.equal(service.render('problem', 'testoj/circular', () => circular).htmlContent, 'ok');

  const bigints = { htmlContent: 'ok', value: 1n };
  assert.equal(service.render('problem', 'testoj/bigint', () => bigints).htmlContent, 'ok');

  const throwing = { htmlContent: 'ok', get boom() { throw new Error('getter'); } };
  assert.equal(service.render('problem', 'testoj/getter', () => throwing).htmlContent, 'ok');

  // Cycle and BigInt payloads are measurable now, so they are retained; only the
  // throwing getter is skipped. Either way the catalog stays intact.
  assert.deepEqual(removed, []);
  assert.equal(service.errors.length, 0);
  assert.equal(service.state, 'healthy');
  assert.equal(service.cache.get('problem:testoj/circular:default').htmlContent, 'ok');
  assert.equal(service.cache.get('problem:testoj/getter:default'), undefined);
});

test('a factory failure still quarantines, distinct from a caching failure', () => {
  const removed = [];
  const service = new ContentService({
    problemManager: {
      remove: (oj, id) => { removed.push(`${oj}/${id}`); return true; },
      getAll: () => [],
    },
    problemSetManager: { remove() {}, list() {}, baseDir: '/tmp' },
  });
  service.state = 'healthy';
  service.activeRevision = 'test';

  assert.throws(
    () => service.render('problem', 'testoj/broken', () => { throw new Error('broken include'); }),
    { name: 'ContentRenderError' },
  );
  assert.deepEqual(removed, ['testoj/broken']);
  assert.equal(service.errors.length, 1);
  assert.equal(service.state, 'degraded');
});
