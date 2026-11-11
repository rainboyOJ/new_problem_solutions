import test from 'node:test';
import assert from 'node:assert/strict';
import { readFileSync } from 'node:fs';
import vm from 'node:vm';

function createElement({ dataset = {}, hidden = false, textContent = '', children = {}, closestModal = null } = {}) {
  const listeners = new Map();
  return {
    children,
    closestModal,
    dataset,
    disabled: false,
    focusCalls: 0,
    hidden,
    listeners,
    textContent,
    addEventListener(type, listener) {
      listeners.set(type, listener);
    },
    async dispatch(type) {
      return listeners.get(type)?.({ currentTarget: this, target: this });
    },
    closest(selector) {
      return selector === '.modal' ? this.closestModal : null;
    },
    focus() {
      this.focusCalls += 1;
    },
    querySelector(selector) {
      return children[selector] || null;
    },
  };
}

function payload(data) {
  return Promise.resolve(data);
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

// 一个 trigger 与它对应的 Raw 弹窗构成一份独立的控制器实例。
// nested 为 true 时模拟“触发按钮长在另一个弹窗里”（题面 modal 标题栏）。
function createWidget({ key = 'article', hidden = true, nested = false, noteSlug } = {}) {
  const dataset = {
    mdRawKind: key,
    mdRawKey: key,
    problemId: 'P1001',
    problemOj: 'luogu',
  };
  if (noteSlug) dataset.noteSlug = noteSlug;

  const trigger = createElement({ closestModal: nested ? { id: 'problemStatementModal' } : null, dataset, hidden });
  const close = createElement({ textContent: '' });
  const copy = createElement({ textContent: '复制全部' });
  copy.disabled = true;
  const retry = createElement({ hidden: true });
  const status = createElement({ textContent: '加载中...' });
  const content = createElement({ hidden: true });
  const lineNumbers = createElement();
  const code = createElement();

  const modalElement = createElement({
    dataset: { mdRawKey: key },
    children: {
      '.btn-close': close,
      '[data-md-raw-code]': code,
      '[data-md-raw-content]': content,
      '[data-md-raw-copy]': copy,
      '[data-md-raw-line-numbers]': lineNumbers,
      '[data-md-raw-retry]': retry,
      '[data-md-raw-status]': status,
    },
  });

  return { close, code, content, copy, lineNumbers, modalElement, retry, status, trigger };
}

function loadController({
  copyText,
  fetchImpl,
  highlightElement,
  statementLoader,
  widgets = [createWidget()],
} = {}) {
  const calls = {
    copied: [],
    fetch: [],
    highlighted: [],
    modalShows: [],
    states: [],
    statementLoads: 0,
    timers: [],
  };

  const modalsByKey = new Map(widgets.map((widget) => [widget.modalElement.dataset.mdRawKey, widget.modalElement]));
  const triggers = widgets.map((widget) => widget.trigger);

  const window = {
    bootstrap: {
      Modal: {
        getOrCreateInstance(element) {
          return { show: () => { calls.modalShows.push(element); } };
        },
      },
    },
    RbookApi: {
      async getJSON(url) {
        calls.fetch.push([url]);
        return fetchImpl(url);
      },
      async getText() {
        throw new Error('getText is not used by md-raw-modal');
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
    setTimeout(callback, delay) {
      calls.timers.push({ callback, delay });
    },
  };

  if (statementLoader) {
    window.RbookStatement = {
      load() {
        calls.statementLoads += 1;
        return statementLoader();
      },
    };
  }

  const document = {
    querySelector(selector) {
      const match = selector.match(/^\[data-md-raw-modal\]\[data-md-raw-key="(.+)"\]$/);
      if (match) return modalsByKey.get(match[1]) || null;
      return null;
    },
    querySelectorAll(selector) {
      return selector === '[data-md-raw-trigger]' ? triggers : [];
    },
  };

  const script = readFileSync('public/javascripts/md-raw-modal.js', 'utf8');

  vm.runInNewContext(script, { console: { warn() {} }, document, fetch: undefined, Promise, window });

  const [first] = widgets;
  return { calls, widgets, window, ...first };
}

test('Md Raw initializes progressively and opens in a loading state', async () => {
  const request = deferred();
  const state = loadController({ fetchImpl: () => request.promise });

  assert.equal(state.trigger.hidden, false);
  const opening = state.trigger.dispatch('click');

  assert.equal(state.calls.modalShows.length, 1);
  assert.equal(state.calls.fetch.length, 1);
  assert.equal(state.calls.fetch[0][0], '/api/problems/luogu/P1001');  assert.equal(state.status.hidden, false);
  assert.match(state.status.textContent, /加载/);
  assert.equal(state.retry.hidden, true);
  assert.equal(state.content.hidden, true);
  assert.equal(state.copy.disabled, true);

  request.resolve(payload({ md_content: '# title\n' }));
  await opening;

  await state.modalElement.dispatch('hidden.bs.modal');
  assert.equal(state.calls.timers.at(-1).delay, 0);
  state.calls.timers.at(-1).callback();
  assert.equal(state.trigger.focusCalls, 1);
});

test('Md Raw renders exact Markdown, line numbers, highlights, copies, and caches', async () => {
  const markdown = '# title\n\n```cpp\nint main() {}\n```\n';
  const state = loadController({
    fetchImpl: async () => payload({ md_content: markdown }),
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
  assert.equal(state.calls.modalShows.length, 2);
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
      fetchImpl: async () => payload({ md_content: markdown }),
    });
    await state.trigger.dispatch('click');
    assert.equal(state.lineNumbers.textContent, expected);
  }
});

test('Md Raw handles API, JSON, and payload errors consistently and retries', async () => {
  // RbookApi 已把非 2xx 与解析失败转成 throw，这里模拟三种失败 + 一次恢复。
  const responses = [
    () => { throw new Error('HTTP 500'); },
    () => { throw new Error('bad json'); },
    () => ({ md_content: 42 }),
    () => ({ md_content: '# recovered' }),
  ];
  const state = loadController({ fetchImpl: async () => responses.shift()() });

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

  request.resolve(payload({ md_content: 'readable raw' }));
  await Promise.all([first, second]);

  assert.equal(state.code.textContent, 'readable raw');
  assert.equal(state.copy.disabled, false);
  assert.equal(state.calls.highlighted.length, 0);
});

test('Md Raw ignores highlighting errors and reports copy failure', async () => {
  const state = loadController({
    fetchImpl: async () => payload({ md_content: 'raw' }),
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

test('Md Raw wires every trigger to its own modal and keeps caches separate', async () => {
  const article = createWidget({ key: 'article' });
  const statement = createWidget({ key: 'statement' });
  const statuses = {
    '/api/problems/luogu/P1001': payload({ md_content: 'article raw' }),
    '/api/problems/luogu/P1001/statement/raw': payload({ md_content: 'statement raw' }),
  };
  const state = loadController({
    fetchImpl: async (url) => statuses[url],
    widgets: [article, statement],
  });

  assert.equal(state.calls.modalShows.length, 0);
  assert.equal(article.trigger.hidden, false);
  assert.equal(statement.trigger.hidden, false);

  await article.trigger.dispatch('click');
  await statement.trigger.dispatch('click');

  assert.deepEqual(state.calls.modalShows, [article.modalElement, statement.modalElement]);
  assert.deepEqual(state.calls.fetch.map(([url]) => url), [
    '/api/problems/luogu/P1001',
    '/api/problems/luogu/P1001/statement/raw',
  ]);
  assert.equal(article.code.textContent, 'article raw');
  assert.equal(statement.code.textContent, 'statement raw');

  // 各自缓存，再点一次不重复请求。
  await article.trigger.dispatch('click');
  await statement.trigger.dispatch('click');
  assert.equal(state.calls.fetch.length, 2);
});

test('Md Raw builds the ai-note URL from oj, problem id, and slug', async () => {
  const note = createWidget({ key: 'ai-note', noteSlug: 'first-note' });
  const state = loadController({
    fetchImpl: async () => payload({ md_content: 'note raw' }),
    widgets: [note],
  });

  await note.trigger.dispatch('click');

  assert.deepEqual(state.calls.fetch.map(([url]) => url), [
    '/api/problems/luogu/P1001/ai-notes/first-note/raw',
  ]);
  assert.equal(note.code.textContent, 'note raw');
});

test('Md Raw reuses the shared statement markdown instead of fetching again', async () => {
  const statement = createWidget({ key: 'statement' });
  let loads = 0;
  const state = loadController({
    fetchImpl: async () => { throw new Error('should not fetch for statement kind'); },
    statementLoader: async () => {
      loads += 1;
      return 'shared statement markdown';
    },
    widgets: [statement],
  });

  await statement.trigger.dispatch('click');

  assert.equal(loads, 1);
  assert.equal(state.calls.statementLoads, 1);
  assert.equal(state.calls.fetch.length, 0);
  assert.equal(statement.code.textContent, 'shared statement markdown');

  await statement.copy.dispatch('click');
  assert.deepEqual(state.calls.copied, ['shared statement markdown']);
});

test('Md Raw moves focus into the modal when its trigger lives in another modal', async () => {
  const standalone = createWidget({ key: 'article' });
  const nested = createWidget({ key: 'statement', nested: true });
  const state = loadController({
    fetchImpl: async () => payload({ md_content: 'raw' }),
    widgets: [standalone, nested],
  });

  // 普通页面按钮不抢焦点：Bootstrap 自己会把焦点移进弹窗。
  await standalone.modalElement.dispatch('shown.bs.modal');
  assert.equal(standalone.close.focusCalls, 0);

  // 题面弹窗里的按钮打开原文弹窗时，焦点要进到原文弹窗，Esc 才关对层。
  await nested.modalElement.dispatch('shown.bs.modal');
  assert.equal(nested.close.focusCalls, 1);
});
