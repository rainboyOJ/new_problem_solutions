import test from 'node:test';
import assert from 'node:assert/strict';
import { readFileSync } from 'node:fs';
import vm from 'node:vm';

function createElement({ dataset = {}, hidden = false, textContent = '' } = {}) {
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

function jsonResponse(payload, { ok = true } = {}) {
  return {
    ok,
    async json() {
      if (payload instanceof Error) throw payload;
      return payload;
    },
  };
}

function deferred() {
  let resolve;
  let reject;
  const promise = new Promise((resolvePromise, rejectPromise) => {
    resolve = resolvePromise;
    reject = rejectPromise;
  });
  return { promise, reject, resolve };
}

function nextTurn() {
  return new Promise((resolve) => setImmediate(resolve));
}

function loadController({ fetchImpl, highlightElement, copyText } = {}) {
  const trigger = createElement({
    dataset: { mdRawUrl: '/api/problems/luogu/P1001' },
    hidden: true,
  });
  const modalElement = createElement();
  const copy = createElement({ textContent: '复制全部' });
  copy.disabled = true;
  const retry = createElement({ hidden: true });
  const status = createElement({ textContent: '加载中...' });
  const content = createElement({ hidden: true });
  const lineNumbers = createElement();
  const code = createElement();
  const elements = new Map([
    ['[data-md-raw-trigger]', trigger],
    ['[data-md-raw-modal]', modalElement],
    ['[data-md-raw-copy]', copy],
    ['[data-md-raw-retry]', retry],
    ['[data-md-raw-status]', status],
    ['[data-md-raw-content]', content],
    ['[data-md-raw-line-numbers]', lineNumbers],
    ['[data-md-raw-code]', code],
  ]);
  const calls = {
    copied: [],
    fetch: [],
    highlighted: [],
    modalShows: 0,
    states: [],
  };
  const window = {
    bootstrap: {
      Modal: {
        getOrCreateInstance(element) {
          assert.equal(element, modalElement);
          return { show: () => { calls.modalShows += 1; } };
        },
      },
    },
    RbookClipboard: {
      async copyText(text) {
        calls.copied.push(text);
        return copyText ? copyText(text) : true;
      },
      setButtonState(button, text, stateClass) {
        calls.states.push({ button, stateClass, text });
      },
    },
    RbookCodeHighlight: highlightElement === null ? undefined : {
      highlightElement(element) {
        calls.highlighted.push(element.textContent);
        return highlightElement ? highlightElement(element) : Promise.resolve(true);
      },
    },
  };
  const fetch = async (...args) => {
    calls.fetch.push(args);
    return fetchImpl(...args);
  };
  const document = {
    querySelector(selector) {
      return elements.get(selector) || null;
    },
  };
  const script = readFileSync('public/javascripts/md-raw-modal.js', 'utf8');

  vm.runInNewContext(script, { console: { warn() {} }, document, fetch, Promise, window });

  return {
    calls,
    code,
    content,
    copy,
    lineNumbers,
    modalElement,
    retry,
    status,
    trigger,
    window,
  };
}

test('Md Raw initializes progressively and opens in a loading state', async () => {
  const request = deferred();
  const state = loadController({ fetchImpl: () => request.promise });

  assert.equal(state.trigger.hidden, false);
  const opening = state.trigger.dispatch('click');

  assert.equal(state.calls.modalShows, 1);
  assert.equal(state.calls.fetch.length, 1);
  assert.equal(state.calls.fetch[0][0], '/api/problems/luogu/P1001');
  assert.equal(state.status.hidden, false);
  assert.match(state.status.textContent, /加载/);
  assert.equal(state.retry.hidden, true);
  assert.equal(state.content.hidden, true);
  assert.equal(state.copy.disabled, true);

  request.resolve(jsonResponse({ md_content: '# title\n' }));
  await opening;
});

test('Md Raw renders exact Markdown, line numbers, highlights, copies, and caches', async () => {
  const markdown = '# title\n\n```cpp\nint main() {}\n```\n';
  const state = loadController({
    fetchImpl: async () => jsonResponse({ md_content: markdown }),
  });

  await state.trigger.dispatch('click');

  assert.equal(state.code.textContent, markdown);
  assert.equal(state.lineNumbers.textContent, '1\n2\n3\n4\n5\n6');
  assert.equal(state.status.hidden, true);
  assert.equal(state.retry.hidden, true);
  assert.equal(state.content.hidden, false);
  assert.equal(state.copy.disabled, false);
  assert.deepEqual(state.calls.highlighted, [markdown]);

  await state.copy.dispatch('click');
  assert.deepEqual(state.calls.copied, [markdown]);
  assert.deepEqual(state.calls.states.at(-1), {
    button: state.copy,
    stateClass: 'is-copied',
    text: '已复制',
  });

  await state.trigger.dispatch('click');
  assert.equal(state.calls.modalShows, 2);
  assert.equal(state.calls.fetch.length, 1);
  assert.deepEqual(state.calls.highlighted, [markdown]);
});

test('Md Raw line numbers cover empty, single-line, and trailing-newline content', async () => {
  for (const [markdown, expected] of [
    ['', '1'],
    ['one line', '1'],
    ['one line\n', '1\n2'],
  ]) {
    const state = loadController({
      fetchImpl: async () => jsonResponse({ md_content: markdown }),
    });
    await state.trigger.dispatch('click');
    assert.equal(state.lineNumbers.textContent, expected);
  }
});

test('Md Raw handles HTTP, JSON, and payload errors consistently and retries', async () => {
  const responses = [
    jsonResponse({}, { ok: false }),
    jsonResponse(new Error('bad json')),
    jsonResponse({ md_content: 42 }),
    jsonResponse({ md_content: '# recovered' }),
  ];
  const state = loadController({ fetchImpl: async () => responses.shift() });

  for (let attempt = 0; attempt < 3; attempt += 1) {
    if (attempt === 0) await state.trigger.dispatch('click');
    else await state.retry.dispatch('click');

    assert.equal(state.status.hidden, false);
    assert.match(state.status.textContent, /失败/);
    assert.equal(state.retry.hidden, false);
    assert.equal(state.content.hidden, true);
    assert.equal(state.copy.disabled, true);
  }

  await state.retry.dispatch('click');
  assert.equal(state.calls.fetch.length, 4);
  assert.equal(state.code.textContent, '# recovered');
  assert.equal(state.content.hidden, false);
});

test('Md Raw coalesces in-flight requests and remains usable without Prism', async () => {
  const request = deferred();
  const state = loadController({
    fetchImpl: () => request.promise,
    highlightElement: null,
  });

  const first = state.trigger.dispatch('click');
  const second = state.trigger.dispatch('click');
  assert.equal(state.calls.fetch.length, 1);

  request.resolve(jsonResponse({ md_content: 'readable raw' }));
  await Promise.all([first, second]);

  assert.equal(state.code.textContent, 'readable raw');
  assert.equal(state.copy.disabled, false);
  assert.equal(state.calls.highlighted.length, 0);
});

test('Md Raw ignores highlighting errors and reports copy failure', async () => {
  const state = loadController({
    fetchImpl: async () => jsonResponse({ md_content: 'raw' }),
    highlightElement: async () => { throw new Error('Prism unavailable'); },
    copyText: async () => false,
  });

  await state.trigger.dispatch('click');
  await nextTurn();
  assert.equal(state.code.textContent, 'raw');
  assert.equal(state.copy.disabled, false);

  await state.copy.dispatch('click');
  assert.deepEqual(state.calls.states.at(-1), {
    button: state.copy,
    stateClass: 'is-copy-failed',
    text: '复制失败',
  });

  state.window.RbookClipboard.copyText = async () => { throw new Error('denied'); };
  await state.copy.dispatch('click');
  assert.equal(state.calls.states.at(-1).text, '复制失败');
});
