import test from 'node:test';
import assert from 'node:assert/strict';
import { EventEmitter } from 'node:events';
import fs from 'fs';
import os from 'os';
import path from 'path';

import {
  ActivePreview,
  createPreviewSnapshot,
  resolvePreviewProblemFromIndex,
} from '../lib/preview-state.js';
import { createPreviewWatcher } from '../lib/preview-watcher.js';

class FakeWatcher extends EventEmitter {
  closed = false;

  async close() {
    this.closed = true;
  }
}

function makeTempRepo(t) {
  const root = fs.mkdtempSync(path.join(os.tmpdir(), 'rbook-preview-watcher-'));
  t.after(() => fs.rmSync(root, { recursive: true, force: true }));
  return root;
}

function writeProblem(root, id) {
  const problemDir = path.join(root, 'problems', 'luogu', id);
  const indexPath = path.join(problemDir, 'index.md');
  fs.mkdirSync(problemDir, { recursive: true });
  fs.writeFileSync(path.join(problemDir, 'main.cpp'), `int value_${id} = 1;\n`);
  fs.writeFileSync(indexPath, [
    '---',
    `title: Problem ${id}`,
    'oj: luogu',
    `problem_id: ${id}`,
    '---',
    '',
    `# Article ${id}`,
    '',
    '@include-code(./main.cpp, cpp)',
    '',
  ].join('\n'));
  return { problemDir, indexPath };
}

function setup(t) {
  const root = makeTempRepo(t);
  const first = writeProblem(root, 'P1001');
  const second = writeProblem(root, 'P1002');
  const descriptor = resolvePreviewProblemFromIndex(first.indexPath, { projectRoot: root });
  const active = new ActivePreview(createPreviewSnapshot(descriptor));
  const fake = new FakeWatcher();
  const logs = { info: [], error: [] };
  const watcher = createPreviewWatcher(active, {
    projectRoot: root,
    stabilityMs: 10,
    watchFactory: () => fake,
    logger: {
      info(message) { logs.info.push(message); },
      error(message) { logs.error.push(message); },
    },
  });
  t.after(() => watcher.close());
  return { root, first, second, active, fake, logs, watcher };
}

test('preview watcher coalesces active problem changes into one reload', async (t) => {
  const state = setup(t);
  const codePath = path.join(state.first.problemDir, 'main.cpp');
  fs.writeFileSync(codePath, 'int changed = 2;\n');

  state.fake.emit('all', 'change', codePath);
  state.fake.emit('all', 'change', codePath);
  await state.watcher.flush();

  assert.equal(state.active.version, 2);
  assert.match(state.active.snapshot.mdContent, /int changed = 2;/);
  assert.equal(state.logs.info.length, 1);
});

test('preview watcher switches to a valid changed index and ignores inactive files', async (t) => {
  const state = setup(t);
  const inactiveCode = path.join(state.second.problemDir, 'main.cpp');
  fs.writeFileSync(inactiveCode, 'int inactive = 3;\n');
  state.fake.emit('all', 'change', inactiveCode);
  await state.watcher.flush();
  assert.equal(state.active.version, 1);

  const raw = fs.readFileSync(state.second.indexPath, 'utf8');
  fs.writeFileSync(state.second.indexPath, raw + '\nNew section.\n');
  state.fake.emit('all', 'change', state.second.indexPath);
  await state.watcher.flush();

  assert.equal(state.active.version, 2);
  assert.equal(state.active.snapshot.problem.problem_id, 'P1002');
  assert.match(state.active.snapshot.mdContent, /int inactive = 3;/);
});

test('preview watcher retains the last valid snapshot and recovers later', async (t) => {
  const state = setup(t);
  fs.writeFileSync(state.first.indexPath, '---\ntitle: [invalid\n---\n');
  state.fake.emit('all', 'change', state.first.indexPath);
  await state.watcher.flush();

  assert.equal(state.active.version, 1);
  assert.equal(state.active.snapshot.problem.problem_id, 'P1001');
  assert.match(state.logs.error.join('\n'), /Kept last valid page/);

  fs.writeFileSync(state.first.indexPath, [
    '---',
    'title: Recovered',
    'oj: luogu',
    'problem_id: P1001',
    '---',
    '',
    '# Recovered article',
    '',
  ].join('\n'));
  state.fake.emit('all', 'change', state.first.indexPath);
  await state.watcher.flush();

  assert.equal(state.active.version, 2);
  assert.equal(state.active.snapshot.problem.title, 'Recovered');
});

test('preview watcher processes changes after the stability interval and closes cleanly', async (t) => {
  const state = setup(t);
  const codePath = path.join(state.first.problemDir, 'main.cpp');
  state.fake.emit('all', 'change', codePath);

  await new Promise((resolve) => setTimeout(resolve, 30));
  assert.equal(state.active.version, 2);

  await state.watcher.close();
  assert.equal(state.fake.closed, true);
  state.fake.emit('all', 'change', codePath);
  await new Promise((resolve) => setTimeout(resolve, 20));
  assert.equal(state.active.version, 2);
});
