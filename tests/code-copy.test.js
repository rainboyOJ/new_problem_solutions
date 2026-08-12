import test from 'node:test';
import assert from 'node:assert/strict';
import { readFileSync } from 'node:fs';
import vm from 'node:vm';

function createClassList() {
  const values = new Set();
  return {
    contains: (name) => values.has(name),
    remove: (...names) => names.forEach((name) => values.delete(name)),
    toggle(name, force) {
      if (force) values.add(name);
      else values.delete(name);
    },
  };
}

function createButton(text = '复制') {
  return {
    classList: createClassList(),
    dataset: {},
    textContent: text,
  };
}

function loadClipboard({ clipboard, execResult = true, secure = true } = {}) {
  const listeners = new Map();
  const timers = [];
  const textareas = [];
  const removed = [];
  const document = {
    addEventListener(type, listener) {
      listeners.set(type, listener);
    },
    body: {
      appendChild(element) {
        textareas.push(element);
      },
      removeChild(element) {
        removed.push(element);
      },
    },
    createElement(tagName) {
      assert.equal(tagName, 'textarea');
      return {
        attributes: {},
        selected: false,
        style: {},
        value: '',
        select() {
          this.selected = true;
        },
        setAttribute(name, value) {
          this.attributes[name] = value;
        },
      };
    },
    execCommand(command) {
      assert.equal(command, 'copy');
      return execResult;
    },
  };
  const window = {
    isSecureContext: secure,
    setTimeout(callback, delay) {
      timers.push({ callback, delay });
    },
  };
  const script = readFileSync('public/javascripts/code-copy.js', 'utf8');

  vm.runInNewContext(script, {
    document,
    navigator: clipboard ? { clipboard } : {},
    window,
  });

  return { listeners, removed, textareas, timers, window };
}

test('shared clipboard prefers the secure Clipboard API and preserves rejection', async () => {
  const copied = [];
  const state = loadClipboard({
    clipboard: {
      async writeText(text) {
        copied.push(text);
      },
    },
  });

  assert.equal(await state.window.RbookClipboard.copyText('# raw\n'), true);
  assert.deepEqual(copied, ['# raw\n']);
  assert.equal(state.textareas.length, 0);

  const failure = new Error('permission denied');
  const rejected = loadClipboard({
    clipboard: { writeText: async () => { throw failure; } },
  });
  await assert.rejects(rejected.window.RbookClipboard.copyText('raw'), failure);
});

test('shared clipboard falls back to a temporary textarea', async () => {
  const state = loadClipboard({ secure: false, execResult: false });

  assert.equal(await state.window.RbookClipboard.copyText('exact source'), false);
  assert.equal(state.textareas.length, 1);
  assert.equal(state.textareas[0].value, 'exact source');
  assert.equal(state.textareas[0].attributes.readonly, '');
  assert.equal(state.textareas[0].selected, true);
  assert.deepEqual(state.removed, state.textareas);
});

test('shared button feedback reports status and resets after 1.5 seconds', () => {
  const state = loadClipboard();
  const button = createButton('复制全部');

  state.window.RbookClipboard.setButtonState(button, '已复制', 'is-copied');
  assert.equal(button.textContent, '已复制');
  assert.equal(button.classList.contains('is-copied'), true);
  assert.equal(state.timers[0].delay, 1500);

  state.timers[0].callback();
  assert.equal(button.textContent, '复制全部');
  assert.equal(button.classList.contains('is-copied'), false);

  state.window.RbookClipboard.setButtonState(button, '复制失败', 'is-copy-failed');
  assert.equal(button.classList.contains('is-copy-failed'), true);
});

test('delegated code copy uses only the code element text', async () => {
  const copied = [];
  const state = loadClipboard({
    clipboard: { writeText: async (text) => copied.push(text) },
  });
  const button = createButton();
  const code = { textContent: 'int main() {}\n' };
  const block = {
    querySelector(selector) {
      assert.equal(selector, 'pre code');
      return code;
    },
  };
  button.closest = (selector) => {
    assert.equal(selector, '.code-block');
    return block;
  };
  const target = {
    closest(selector) {
      assert.equal(selector, '[data-code-copy]');
      return button;
    },
  };

  await state.listeners.get('click')({ target });

  assert.deepEqual(copied, ['int main() {}\n']);
  assert.equal(button.textContent, '已复制');
  assert.equal(button.classList.contains('is-copied'), true);
});
