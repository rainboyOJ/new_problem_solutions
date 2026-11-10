import test from 'node:test';
import assert from 'node:assert/strict';
import { readFileSync } from 'node:fs';
import vm from 'node:vm';

function createElement({ dataset = {}, hidden = true, textContent = '' } = {}) {
  const listeners = new Map();
  return {
    dataset,
    disabled: false,
    hidden,
    listeners,
    textContent,
    addEventListener(type, listener) {
      listeners.set(type, listener);
    },
    async dispatch(type) {
      return listeners.get(type)?.({ currentTarget: this, target: this });
    },
  };
}

function loadActions({ copyText, fetchImpl } = {}) {
  const button = createElement({
    dataset: { problemId: 'P1001', problemOj: 'luogu' },
    textContent: '复制题面',
  });
  const calls = { copied: [], fetch: [], states: [] };
  const window = {
    RbookApi: {
      async getJSON(url) {
        calls.fetch.push(url);
        return fetchImpl(url);
      },
    },
    RbookClipboard: {
      async copyText(text) {
        calls.copied.push(text);
        return copyText ? copyText(text) : true;
      },
      setButtonState(target, text, stateClass) {
        calls.states.push({ button: target, stateClass, text });
      },
    },
  };
  const document = {
    querySelector(selector) {
      return selector === '[data-statement-copy]' ? button : null;
    },
  };

  const script = readFileSync('public/javascripts/statement-actions.js', 'utf8');
  vm.runInNewContext(script, { document, Promise, window });

  return { button, calls, window };
}

test('Statement copy is progressive and copies the markdown statement', async () => {
  const markdown = '# P1001 A+B Problem\n\n## 题目描述\n';
  const { button, calls } = loadActions({
    fetchImpl: async () => ({ md_content: markdown }),
  });

  assert.equal(button.hidden, false);

  await button.dispatch('click');

  assert.deepEqual(calls.fetch, ['/api/problems/luogu/P1001/statement/raw']);
  assert.deepEqual(calls.copied, [markdown]);
  assert.deepEqual(calls.states.at(-1), {
    button,
    stateClass: 'is-copied',
    text: '已复制',
  });
});

test('Statement copy caches the markdown across clicks', async () => {
  const { button, calls } = loadActions({
    fetchImpl: async () => ({ md_content: 'raw statement' }),
  });

  await button.dispatch('click');
  await button.dispatch('click');

  assert.equal(calls.fetch.length, 1);
  assert.deepEqual(calls.copied, ['raw statement', 'raw statement']);
});

test('Statement copy reports failure when the request fails', async () => {
  const { button, calls } = loadActions({
    fetchImpl: async () => { throw new Error('Statement not found'); },
  });

  await button.dispatch('click');

  assert.deepEqual(calls.copied, []);
  assert.deepEqual(calls.states.at(-1), {
    button,
    stateClass: 'is-copy-failed',
    text: '复制失败',
  });
});

test('Statement copy reports failure when the payload is invalid', async () => {
  const { button, calls } = loadActions({
    fetchImpl: async () => ({ md_content: 42 }),
  });

  await button.dispatch('click');

  assert.deepEqual(calls.copied, []);
  assert.equal(calls.states.at(-1).text, '复制失败');
});

test('Statement actions expose the shared loader for the raw modal', async () => {
  const { window, calls } = loadActions({
    fetchImpl: async () => ({ md_content: 'shared statement' }),
  });

  assert.equal(typeof window.RbookStatement.load, 'function');
  assert.equal(await window.RbookStatement.load(), 'shared statement');
  assert.equal(await window.RbookStatement.load(), 'shared statement');
  assert.equal(calls.fetch.length, 1);
});

test('Statement actions do nothing when the copy button is absent', async () => {
  const window = {
    RbookApi: { async getJSON() { throw new Error('should not fetch'); } },
    RbookClipboard: { async copyText() { return true; }, setButtonState() {} },
  };
  const document = { querySelector: () => null };
  const script = readFileSync('public/javascripts/statement-actions.js', 'utf8');

  vm.runInNewContext(script, { document, Promise, window });

  assert.equal(window.RbookStatement, undefined);
});
