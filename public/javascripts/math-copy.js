(function () {
  const FORMULA_SELECTOR = '.markdown-body .katex-display';
  const SOURCE_SELECTOR = 'annotation[encoding="application/x-tex"]';
  const RESET_DELAY_MS = 1500;
  const resetTimers = new WeakMap();

  const ICONS = [
    // Lucide: copy, check, triangle-alert
    '<svg class="math-copy-icon math-copy-icon-copy" xmlns="http://www.w3.org/2000/svg" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round" aria-hidden="true" focusable="false"><rect width="14" height="14" x="8" y="8" rx="2" ry="2"></rect><path d="M4 16c-1.1 0-2-.9-2-2V4c0-1.1.9-2 2-2h10c1.1 0 2 .9 2 2"></path></svg>',
    '<svg class="math-copy-icon math-copy-icon-success" xmlns="http://www.w3.org/2000/svg" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round" aria-hidden="true" focusable="false"><path d="M20 6 9 17l-5-5"></path></svg>',
    '<svg class="math-copy-icon math-copy-icon-failure" xmlns="http://www.w3.org/2000/svg" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round" aria-hidden="true" focusable="false"><path d="m21.73 18-8-14a2 2 0 0 0-3.46 0l-8 14A2 2 0 0 0 4 21h16a2 2 0 0 0 1.73-3"></path><path d="M12 9v4"></path><path d="M12 17h.01"></path></svg>',
  ].join('');

  function formatFormula(source) {
    const tex = String(source || '').replace(/\r\n?/g, '\n').trim();
    return tex ? `$$\n${tex}\n$$` : null;
  }

  function setButtonLabel(button, label) {
    button.title = label;
    button.setAttribute('aria-label', label);
  }

  function resetButton(button) {
    delete button.dataset.mathCopyState;
    setButtonLabel(button, '复制公式 Markdown');
    resetTimers.delete(button);
  }

  function showButtonState(button, state) {
    const previousTimer = resetTimers.get(button);
    if (previousTimer) window.clearTimeout(previousTimer);

    button.dataset.mathCopyState = state;
    setButtonLabel(button, state === 'success' ? '已复制' : '复制失败');
    resetTimers.set(button, window.setTimeout(() => resetButton(button), RESET_DELAY_MS));
  }

  function createButton() {
    const button = document.createElement('button');
    button.type = 'button';
    button.className = 'math-copy-button';
    button.setAttribute('data-math-copy', '');
    button.setAttribute('aria-live', 'polite');
    setButtonLabel(button, '复制公式 Markdown');
    button.innerHTML = ICONS;
    return button;
  }

  function enhance(root = document) {
    root.querySelectorAll(FORMULA_SELECTOR).forEach((formula) => {
      if (formula.querySelector('[data-math-copy]')) return;

      const source = formula.querySelector(SOURCE_SELECTOR);
      if (!source || !formatFormula(source.textContent)) return;

      formula.classList.add('has-math-copy');
      formula.appendChild(createButton());
    });
  }

  document.addEventListener('click', async (event) => {
    const button = event.target.closest('[data-math-copy]');
    if (!button) return;

    const formula = button.closest('.katex-display');
    const source = formula && formula.querySelector(SOURCE_SELECTOR);
    const markdown = source && formatFormula(source.textContent);
    const clipboard = window.RbookClipboard;

    if (!markdown || !clipboard || typeof clipboard.copyText !== 'function') {
      showButtonState(button, 'failure');
      return;
    }

    try {
      const copied = await clipboard.copyText(markdown);
      showButtonState(button, copied ? 'success' : 'failure');
    } catch (error) {
      showButtonState(button, 'failure');
    }
  });

  window.RbookMathCopy = { enhance, formatFormula };
  enhance();
}());
