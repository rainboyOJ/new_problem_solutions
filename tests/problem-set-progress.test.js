import test from 'node:test';
import assert from 'node:assert/strict';
import { readFileSync } from 'node:fs';
import vm from 'node:vm';

function createTask(key) {
  const classes = new Set();
  const task = {
    dataset: { problemKey: key },
    classList: {
      contains: (name) => classes.has(name),
      toggle(name, enabled) {
        if (enabled) classes.add(name);
        else classes.delete(name);
      },
    },
  };
  const input = {
    checked: false,
    closest(selector) {
      if (selector === '[data-problem-toggle]') return input;
      if (selector === '[data-problem-task]') return task;
      return null;
    },
  };
  task.querySelector = (selector) => selector === '[data-problem-toggle]' ? input : null;
  task.input = input;
  return task;
}

test('problem set progress synchronizes duplicate problem keys', () => {
  const tasks = [createTask('luogu/P1001'), createTask('luogu/P1001'), createTask('luogu/P5710')];
  const counter = { textContent: '' };
  let changeHandler = null;
  let stored = null;
  const document = {
    querySelectorAll: () => tasks,
    querySelector: () => counter,
    addEventListener(type, handler) {
      if (type === 'change') changeHandler = handler;
    },
  };
  const window = {
    localStorage: {
      getItem: () => null,
      setItem: (_key, value) => { stored = value; },
    },
  };

  const script = readFileSync('public/javascripts/problem-set-progress.js', 'utf8');
  vm.runInNewContext(script, { document, window, JSON });

  tasks[0].input.checked = true;
  changeHandler({ target: tasks[0].input });
  assert.equal(tasks[0].input.checked, true);
  assert.equal(tasks[1].input.checked, true);
  assert.equal(tasks[2].input.checked, false);
  assert.equal(counter.textContent, '2 / 3 已完成');
  assert.deepEqual(JSON.parse(stored), { 'luogu/P1001': true });

  tasks[1].input.checked = false;
  changeHandler({ target: tasks[1].input });
  assert.equal(tasks[0].input.checked, false);
  assert.equal(tasks[1].input.checked, false);
  assert.equal(counter.textContent, '0 / 3 已完成');
  assert.deepEqual(JSON.parse(stored), {});
});
