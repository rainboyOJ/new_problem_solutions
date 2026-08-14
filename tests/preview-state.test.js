import test from 'node:test';
import assert from 'node:assert/strict';
import fs from 'fs';
import os from 'os';
import path from 'path';

import {
  ActivePreview,
  createPreviewSnapshot,
  findLatestPreviewSnapshot,
  resolvePreviewProblemFromIndex,
} from '../lib/preview-state.js';

function makeTempRepo(t) {
  const root = fs.mkdtempSync(path.join(os.tmpdir(), 'rbook-preview-state-'));
  t.after(() => fs.rmSync(root, { recursive: true, force: true }));
  return root;
}

function writeProblem(root, id, options = {}) {
  const oj = options.oj || 'luogu';
  const problemDir = path.join(root, 'problems', oj, id);
  const indexPath = path.join(problemDir, 'index.md');
  fs.mkdirSync(problemDir, { recursive: true });
  fs.writeFileSync(path.join(problemDir, 'main.cpp'), `int answer_${id} = 1;\n`);
  fs.writeFileSync(path.join(problemDir, 'problem.md'), `# Statement ${id}\n`);
  fs.writeFileSync(indexPath, options.raw || [
    '---',
    `title: Problem ${id}`,
    `oj: ${oj}`,
    `problem_id: ${id}`,
    '---',
    '',
    `# Article ${id}`,
    '',
    '@include-code(./main.cpp, cpp)',
    '',
  ].join('\n'));

  if (options.mtimeMs !== undefined) {
    const time = new Date(options.mtimeMs);
    fs.utimesSync(indexPath, time, time);
  }

  return { problemDir, indexPath };
}

test('findLatestPreviewSnapshot selects the newest valid article', (t) => {
  const root = makeTempRepo(t);
  writeProblem(root, 'P1001', { mtimeMs: 1000 });
  writeProblem(root, 'P1002', { mtimeMs: 3000, raw: '---\ntitle: [\n---\n' });
  writeProblem(root, 'P1003', { mtimeMs: 2000 });

  const snapshot = findLatestPreviewSnapshot({ projectRoot: root });

  assert.equal(snapshot.problem.problem_id, 'P1003');
  assert.equal(snapshot.canonicalUrl, '/problems/luogu/P1003/');
  assert.match(snapshot.mdContent, /int answer_P1003 = 1;/);
  assert.match(snapshot.htmlContent, /language-cpp/);
  assert.match(snapshot.statementHtml, /Statement P1003/);
});

test('findLatestPreviewSnapshot breaks equal timestamps by normalized path', (t) => {
  const root = makeTempRepo(t);
  writeProblem(root, 'P1002', { mtimeMs: 1000 });
  writeProblem(root, 'P1001', { mtimeMs: 1000 });

  const snapshot = findLatestPreviewSnapshot({ projectRoot: root });

  assert.equal(snapshot.problem.problem_id, 'P1001');
});

test('findLatestPreviewSnapshot reports repositories without a valid article', (t) => {
  const root = makeTempRepo(t);
  writeProblem(root, 'P1001', { raw: '---\ntitle: [\n---\n' });

  assert.throws(
    () => findLatestPreviewSnapshot({ projectRoot: root }),
    (error) => {
      assert.equal(error.code, 'PREVIEW_NO_VALID_PROBLEM');
      assert.match(error.message, /No valid problem article/);
      return true;
    },
  );
});

test('ActivePreview commits immutable reload and switch snapshots', (t) => {
  const root = makeTempRepo(t);
  const first = writeProblem(root, 'P1001', { mtimeMs: 1000 });
  const second = writeProblem(root, 'P1002', { mtimeMs: 2000 });
  const firstPreview = resolvePreviewProblemFromIndex(first.indexPath, { projectRoot: root });
  const secondPreview = resolvePreviewProblemFromIndex(second.indexPath, { projectRoot: root });
  const active = new ActivePreview(createPreviewSnapshot(firstPreview));
  const updates = [];
  const unsubscribe = active.subscribe((update) => updates.push(update));

  fs.writeFileSync(first.indexPath, fs.readFileSync(first.indexPath, 'utf8') + '\nUpdated.\n');
  const reload = active.commit(createPreviewSnapshot(firstPreview), {
    path: first.indexPath,
    reason: 'change',
  });
  const switched = active.commit(createPreviewSnapshot(secondPreview), {
    path: second.indexPath,
    reason: 'change',
  });
  unsubscribe();

  assert.equal(reload.type, 'reload');
  assert.equal(switched.type, 'switch');
  assert.equal(active.version, 3);
  assert.equal(active.snapshot.problem.problem_id, 'P1002');
  assert.deepEqual(updates.map((item) => item.type), ['reload', 'switch']);
  assert.deepEqual(active.getClientState(), {
    type: 'state',
    version: 3,
    url: '/problems/luogu/P1002/',
  });
});
