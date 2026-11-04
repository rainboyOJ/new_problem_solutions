(function () {
  const SOURCE_SELECTOR = 'annotation[encoding="application/x-tex"]';
  const TOAST_DURATION_MS = 1600;

  // 公式复制：点击 KaTeX 公式，复制它的 LaTeX 源码。
  // 源码就存在 KaTeX 隐藏 MathML 的 annotation 里，不需要给公式额外打标记。
  let toast = null;
  let toastTimer = 0;
  // 点击会把选区收成光标，所以必须在 mousedown 时先记住「用户本来选着字」。
  let hadTextSelection = false;

  function hasTextSelection() {
    const selection = window.getSelection();
    return Boolean(selection && !selection.isCollapsed && selection.toString().trim());
  }

  document.addEventListener('mousedown', () => {
    hadTextSelection = hasTextSelection();
  }, true);

  function showToast(message) {
    if (!toast) {
      toast = document.createElement('div');
      toast.className = 'math-copy-toast';
      toast.setAttribute('role', 'status');
      toast.setAttribute('aria-live', 'polite');
      document.body.appendChild(toast);
    }

    toast.textContent = message;
    toast.classList.add('show');
    window.clearTimeout(toastTimer);
    toastTimer = window.setTimeout(() => {
      toast.classList.remove('show');
    }, TOAST_DURATION_MS);
  }

  function formatFormula(katex) {
    const source = katex.querySelector(SOURCE_SELECTOR);
    const latex = source && source.textContent.trim();
    if (!latex) return null;

    return katex.closest('.katex-display') ? `$$${latex}$$` : `$${latex}$`;
  }

  document.addEventListener('click', async (event) => {
    const target = event.target;
    if (!(target instanceof Element)) return;

    const katex = target.closest('.katex');
    if (!katex || !katex.closest('.markdown-body')) return;

    // 拖选正文时不要抢走这次点击。
    if (hadTextSelection || hasTextSelection()) return;

    const markdown = formatFormula(katex);
    if (!markdown) return;

    event.stopPropagation();

    const clipboard = window.RbookClipboard;
    if (!clipboard || typeof clipboard.copyText !== 'function') {
      showToast('复制失败');
      return;
    }

    try {
      const copied = await clipboard.copyText(markdown);
      showToast(copied ? '已复制 LaTeX' : '复制失败');
    } catch (error) {
      showToast('复制失败');
    }
  }, true);
}());
