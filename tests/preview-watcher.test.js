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
  const fakes = [];
  const watchPaths = [];
  const logs = { info: [], error: [] };
  const watcher = createPreviewWatcher(active, {
    projectRoot: root,
    stabilityMs: 10,
    watchFactory: (watchPath) => {
      watchPaths.push(watchPath);
      const fake = new FakeWatcher();
      fakes.push(fake);
      return fake;
    },
    logger: {
      info(message) { logs.info.push(message); },
      error(message) { logs.error.push(message); },
    },
  });
  t.after(() => watcher.close());
  return { root, first, second, active, fakes, watchPaths, logs, watcher };
}

test('preview watcher coalesces active problem changes into one reload', async (t) => {
  const state = setup(t);
  const codePath = path.join(state.first.problemDir, 'main.cpp');
  fs.writeFileSync(codePath, 'int changed = 2;\n');

  state.fakes[0].emit('all', 'change', codePath);
  state.fakes[0].emit('all', 'change', codePath);
  await state.watcher.flush();

  assert.equal(state.active.version, 2);
  assert.match(state.active.snapshot.mdContent, /int changed = 2;/);
  assert.equal(state.logs.info.length, 1);
});

test('preview watcher watches one directory and retargets after navigation', async (t) => {
  const state = setup(t);
  assert.deepEqual(state.watchPaths, [state.first.problemDir]);
  assert.equal(state.watcher.watchedDirectory, state.first.problemDir);

  const inactiveCode = path.join(state.second.problemDir, 'main.cpp');
  fs.writeFileSync(inactiveCode, 'int inactive = 3;\n');
  state.fakes[0].emit('all', 'change', inactiveCode);
  await state.watcher.flush();
  assert.equal(state.active.version, 1);

  const secondDescriptor = resolvePreviewProblemFromIndex(state.second.indexPath, {
    projectRoot: state.root,
  });
  state.active.commit(createPreviewSnapshot(secondDescriptor), {
    path: '/problems/luogu/P1002/',
    reason: 'navigation',
  });

  assert.deepEqual(state.watchPaths, [state.first.problemDir, state.second.problemDir]);
  assert.equal(state.watcher.watchedDirectory, state.second.problemDir);
  await Promise.resolve();
  assert.equal(state.fakes[0].closed, true);

  state.fakes[0].emit('all', 'change', path.join(state.first.problemDir, 'main.cpp'));
  state.fakes[1].emit('all', 'change', inactiveCode);
  await state.watcher.flush();

  assert.equal(state.active.version, 3);
  assert.equal(state.active.snapshot.problem.problem_id, 'P1002');
  assert.match(state.active.snapshot.mdContent, /int inactive = 3;/);
  assert.match(state.logs.info.join('\n'), /Activated \/problems\/luogu\/P1002\//);
});

test('preview watcher retains the last valid snapshot and recovers later', async (t) => {
  const state = setup(t);
  fs.writeFileSync(state.first.indexPath, '---\ntitle: [invalid\n---\n');
  state.fakes[0].emit('all', 'change', state.first.indexPath);
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
  state.fakes[0].emit('all', 'change', state.first.indexPath);
  await state.watcher.flush();

  assert.equal(state.active.version, 2);
  assert.equal(state.active.snapshot.problem.title, 'Recovered');
});

test('preview watcher processes changes after the stability interval and closes cleanly', async (t) => {
  const state = setup(t);
  const codePath = path.join(state.first.problemDir, 'main.cpp');
  state.fakes[0].emit('all', 'change', codePath);

  await new Promise((resolve) => setTimeout(resolve, 30));
  assert.equal(state.active.version, 2);

  await state.watcher.close();
  assert.equal(state.fakes[0].closed, true);
  state.fakes[0].emit('all', 'change', codePath);
  await new Promise((resolve) => setTimeout(resolve, 20));
  assert.equal(state.active.version, 2);
});
