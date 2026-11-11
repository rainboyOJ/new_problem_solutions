import test from 'node:test';
import assert from 'node:assert/strict';
import { readFileSync } from 'node:fs';
import vm from 'node:vm';

function createCode(language, text = 'source', { dataset = {} } = {}) {
  return {
    className: `language-${language}`,
    dataset,
    innerHTML: '',
    textContent: text,
    matches(selector) {
      return selector === 'code[class*="language-"]';
    },
    querySelectorAll() {
      return [];
    },
  };
}

function loadHighlighter(codes, respond = async () => ({ html: '<span>token</span>' })) {
  const requests = [];
  const warnings = [];
  const document = {
    querySelectorAll: () => codes,
  };
  const window = {};
  const fetch = async (url, options) => {
    const body = JSON.parse(options.body);
    requests.push({ body, url });
    const data = await respond(body);
    return {
      ok: true,
      status: 200,
      async json() { return data; },
    };
  };
  const script = readFileSync('public/javascripts/code-highlight.js', 'utf8');

  vm.runInNewContext(script, {
    console: { warn: (message) => warnings.push(message) },
    document,
    fetch,
    Promise,
    window,
  });

  return { requests, warnings, window };
}

function nextTurn() {
  return new Promise((resolve) => setImmediate(resolve));
}

test('client highlighter sends dynamic code to the server and installs returned HTML', async () => {
  const cpp = createCode('cpp', 'int main() {}');
  const plain = createCode('none', '1 2 3');
  const state = loadHighlighter([cpp, plain]);

  await nextTurn();

  // language-none 的块（输入输出样例）不发请求。
  assert.equal(state.requests.length, 1);
  assert.deepEqual(state.requests[0], {
    url: '/api/highlight',
    body: { code: 'int main() {}', language: 'cpp' },
  });
  assert.equal(cpp.innerHTML, '<span>token</span>');
  assert.equal(cpp.dataset.rbookHighlight, 'done');
  assert.equal(plain.dataset.rbookHighlight, 'skipped');
});

test('client highlighter skips blocks the server already highlighted', async () => {
  const rendered = createCode('cpp', 'int main() {}', { dataset: { rbookHighlight: 'server' } });
  const state = loadHighlighter([rendered]);

  await nextTurn();

  assert.equal(state.requests.length, 0);
  assert.equal(rendered.dataset.rbookHighlight, 'server');
});

test('client highlighter keeps plain text when the server cannot highlight', async () => {
  const unknown = createCode('not-a-language', 'raw text');
  const state = loadHighlighter([unknown], async () => ({ html: null }));

  await nextTurn();

  assert.equal(state.requests.length, 1);
  assert.equal(unknown.dataset.rbookHighlight, 'skipped');
  assert.equal(unknown.innerHTML, '');
});

test('client highlighter isolates request failures and warns once', async () => {
  const first = createCode('rust', 'fn main() {}');
  const second = createCode('python', 'print(1)');
  const state = loadHighlighter([first, second], async () => {
    throw new Error('offline');
  });

  await nextTurn();

  assert.equal(first.dataset.rbookHighlight, 'failed');
  assert.equal(second.dataset.rbookHighlight, 'failed');
  assert.equal(state.warnings.length, 1);
  assert.match(state.warnings[0], /代码高亮失败/);
});

test('client highlighter coalesces in-flight requests for the same element', async () => {
  let release;
  const gate = new Promise((resolve) => { release = resolve; });
  const code = createCode('python', 'print(1)');
  const state = loadHighlighter([], async () => {
    await gate;
    return { html: '<span>ok</span>' };
  });

  const first = state.window.RbookCodeHighlight.highlightElement(code);
  const second = state.window.RbookCodeHighlight.highlightElement(code);
  release();
  await Promise.all([first, second]);

  assert.equal(state.requests.length, 1);
  assert.equal(code.dataset.rbookHighlight, 'done');
});
