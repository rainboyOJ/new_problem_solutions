import test from 'node:test';
import assert from 'node:assert/strict';
import { readFileSync } from 'node:fs';
import vm from 'node:vm';

const SOURCE_SELECTOR = 'annotation[encoding="application/x-tex"]';

function createClassList(initial = []) {
  const values = new Set(initial);
  return {
    add(...names) {
      names.forEach((name) => values.add(name));
    },
    contains(name) {
      return values.has(name);
    },
  };
}

function createElement({ classes = [], source = undefined, textContent = '' } = {}) {
  const element = {
    attributes: {},
    children: [],
    classList: createClassList(classes),
    className: classes.join(' '),
    dataset: {},
    innerHTML: '',
    parentElement: null,
    textContent,
    title: '',
    type: '',
    appendChild(child) {
      child.parentElement = this;
      this.children.push(child);
      return child;
    },
    closest(selector) {
      let current = this;
      while (current) {
        if (selector === '[data-math-copy]'
          && Object.hasOwn(current.attributes, 'data-math-copy')) return current;
        if (selector === '.katex-display'
          && current.classList.contains('katex-display')) return current;
        current = current.parentElement;
      }
      return null;
    },
    querySelector(selector) {
      if (selector === SOURCE_SELECTOR) return this.annotation || null;
      if (selector === '[data-math-copy]') {
        return this.children.find((child) =>
          Object.hasOwn(child.attributes, 'data-math-copy')) || null;
      }
      return null;
    },
    setAttribute(name, value) {
      this.attributes[name] = value;
    },
  };

  if (source !== undefined) {
    element.annotation = source === null ? null : createElement({ textContent: source });
  }
  return element;
}

function loadMathCopy(sources, { copyText } = {}) {
  const formulas = sources.map((source) =>
    createElement({ classes: ['katex-display'], source }));
  const listeners = new Map();
  const calls = { cleared: [], copied: [], timers: [] };
  const document = {
    addEventListener(type, listener) {
      listeners.set(type, listener);
    },
    createElement(tagName) {
      assert.equal(tagName, 'button');
      return createElement();
    },
    querySelectorAll(selector) {
      assert.equal(selector, '.markdown-body .katex-display');
      return formulas;
    },
  };
  const window = {
    RbookClipboard: {
      async copyText(text) {
        calls.copied.push(text);
        return copyText ? copyText(text) : true;
      },
    },
    clearTimeout(timer) {
      calls.cleared.push(timer);
    },
    setTimeout(callback, delay) {
      const timer = { callback, delay };
      calls.timers.push(timer);
      return timer;
    },
  };
  const script = readFileSync('public/javascripts/math-copy.js', 'utf8');
  vm.runInNewContext(script, { document, window });

  return { calls, formulas, listeners, window };
}

test('math copy enhances only display formulas with source and stays idempotent', () => {
  const state = loadMathCopy(['\n a_i + b_i \n', null, '   ']);

  assert.equal(state.formulas[0].classList.contains('has-math-copy'), true);
  assert.equal(state.formulas[0].children.length, 1);
  assert.equal(state.formulas[1].children.length, 0);
  assert.equal(state.formulas[2].children.length, 0);

  const button = state.formulas[0].children[0];
  assert.equal(button.type, 'button');
  assert.equal(button.className, 'math-copy-button');
  assert.equal(button.attributes['data-math-copy'], '');
  assert.equal(button.attributes['aria-label'], '复制公式 Markdown');
  assert.equal(button.attributes['aria-live'], 'polite');
  assert.match(button.innerHTML, /math-copy-icon-copy/);
  assert.match(button.innerHTML, /math-copy-icon-success/);
  assert.match(button.innerHTML, /math-copy-icon-failure/);

  state.window.RbookMathCopy.enhance();
  assert.equal(state.formulas[0].children.length, 1);
});

test('math copy normalizes formula blocks and includes dollar delimiters', () => {
  const state = loadMathCopy([]);
  const format = state.window.RbookMathCopy.formatFormula;

  assert.equal(format('a+b'), '$$\na+b\n$$');
  assert.equal(format('\r\n  a+b\r\n'), '$$\na+b\n$$');
  assert.equal(
    format('\n\\begin{align}\na &= b \\\\\nc &= d\n\\end{align}\n'),
    '$$\n\\begin{align}\na &= b \\\\\nc &= d\n\\end{align}\n$$',
  );
  assert.equal(format(' \n '), null);
});

test('math copy writes exact Markdown and restores success feedback', async () => {
  const state = loadMathCopy(['\n\\sum_{i=1}^n i\n']);
  const button = state.formulas[0].children[0];
  const icons = button.innerHTML;

  await state.listeners.get('click')({ target: button });

  assert.deepEqual(state.calls.copied, ['$$\n\\sum_{i=1}^n i\n$$']);
  assert.equal(button.dataset.mathCopyState, 'success');
  assert.equal(button.title, '已复制');
  assert.equal(button.attributes['aria-label'], '已复制');
  assert.equal(button.innerHTML, icons);
  assert.equal(state.calls.timers[0].delay, 1500);

  state.calls.timers[0].callback();
  assert.equal(Object.hasOwn(button.dataset, 'mathCopyState'), false);
  assert.equal(button.title, '复制公式 Markdown');
  assert.equal(button.attributes['aria-label'], '复制公式 Markdown');
});

test('math copy reports false and rejected clipboard writes as failures', async () => {
  const refused = loadMathCopy(['a=b'], { copyText: () => false });
  const refusedButton = refused.formulas[0].children[0];
  await refused.listeners.get('click')({ target: refusedButton });
  assert.equal(refusedButton.dataset.mathCopyState, 'failure');
  assert.equal(refusedButton.title, '复制失败');

  const rejected = loadMathCopy(['a=b'], {
    copyText: async () => { throw new Error('denied'); },
  });
  const rejectedButton = rejected.formulas[0].children[0];
  await rejected.listeners.get('click')({ target: rejectedButton });
  assert.equal(rejectedButton.dataset.mathCopyState, 'failure');
  assert.equal(rejectedButton.attributes['aria-label'], '复制失败');
});
