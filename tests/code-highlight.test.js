import test from 'node:test';
import assert from 'node:assert/strict';
import { readFileSync } from 'node:fs';
import vm from 'node:vm';

function createCode(language, text = 'source', { hasTokens = false } = {}) {
  return {
    className: `language-${language}`,
    dataset: {},
    textContent: text,
    parentElement: null,
    matches(selector) {
      return selector === 'code[class*="language-"]';
    },
    querySelector(selector) {
      return selector === '.token' && hasTokens ? {} : null;
    },
    querySelectorAll() {
      return [];
    },
  };
}

function loadHighlighter(codes, loadedLanguages = {}) {
  const highlighted = [];
  const pending = new Map();
  const warnings = [];
  const document = {
    querySelectorAll: () => codes,
  };
  const Prism = {
    languages: { ...loadedLanguages },
    util: {
      getLanguage(code) {
        return /language-([\w-]+)/.exec(code.className)?.[1] || 'none';
      },
    },
    highlightElement(code) {
      highlighted.push(code.textContent);
      code.hasHighlightedMarkup = true;
    },
    plugins: {
      autoloader: {
        loadLanguages(language, success, error) {
          pending.set(language, { success, error });
        },
      },
    },
  };
  const window = { Prism };
  const script = readFileSync('public/javascripts/code-highlight.js', 'utf8');

  vm.runInNewContext(script, {
    console: { warn: (message) => warnings.push(message) },
    document,
    Promise,
    window,
  });

  return { highlighted, pending, Prism, warnings, window };
}

function nextTurn() {
  return new Promise((resolve) => setImmediate(resolve));
}

test('client highlighter handles initial, ignored, and pre-highlighted code', async () => {
  const cpp = createCode('cpp', 'int main() {}');
  const plain = createCode('none', '1 2 3');
  const existing = createCode('python', 'print(1)', { hasTokens: true });
  const state = loadHighlighter([cpp, plain, existing], { cpp: {}, python: {} });

  await Promise.resolve();

  assert.deepEqual(state.highlighted, ['int main() {}']);
  assert.equal(cpp.dataset.rbookHighlight, 'done');
  assert.equal(plain.dataset.rbookHighlight, 'skipped');
  assert.equal(existing.dataset.rbookHighlight, 'done');
  assert.equal(state.pending.size, 0);
});

test('client highlighter loads languages independently and isolates failures', async () => {
  const rust = createCode('rust', 'fn main() {}');
  const unknown = createCode('not-a-language', 'raw');
  const state = loadHighlighter([rust, unknown]);

  assert.deepEqual([...state.pending.keys()].sort(), ['not-a-language', 'rust']);
  assert.equal(rust.dataset.rbookHighlight, 'loading');
  assert.equal(unknown.dataset.rbookHighlight, 'loading');

  state.Prism.languages.rust = {};
  state.pending.get('rust').success();
  state.pending.get('not-a-language').error();
  await nextTurn();

  assert.deepEqual(state.highlighted, ['fn main() {}']);
  assert.equal(rust.dataset.rbookHighlight, 'done');
  assert.equal(unknown.dataset.rbookHighlight, 'failed');
  assert.equal(state.warnings.length, 1);

  await state.window.RbookCodeHighlight.highlight({ querySelectorAll: () => [rust, unknown] });
  assert.deepEqual(state.highlighted, ['fn main() {}']);
  assert.equal(state.warnings.length, 1);
});

test('client highlighter coalesces in-flight loads and rehighlights changed dynamic code', async () => {
  const code = createCode('python', 'loading');
  const state = loadHighlighter([]);

  const first = state.window.RbookCodeHighlight.highlightElement(code);
  const second = state.window.RbookCodeHighlight.highlightElement(code);
  assert.equal(state.pending.size, 1);

  code.textContent = 'print(42)';
  state.Prism.languages.python = {};
  state.pending.get('python').success();
  await Promise.all([first, second]);
  await Promise.resolve();

  assert.deepEqual(state.highlighted, ['print(42)']);
  assert.equal(code.dataset.rbookHighlight, 'done');

  code.textContent = 'print(43)';
  await state.window.RbookCodeHighlight.highlightElement(code);
  assert.deepEqual(state.highlighted, ['print(42)', 'print(43)']);
});
