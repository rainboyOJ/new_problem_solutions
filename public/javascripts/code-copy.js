(function () {
  function fallbackCopy(text) {
    const textarea = document.createElement('textarea');
    textarea.value = text;
    textarea.setAttribute('readonly', '');
    textarea.style.position = 'fixed';
    textarea.style.top = '-9999px';
    textarea.style.left = '-9999px';
    document.body.appendChild(textarea);
    textarea.select();

    try {
      return document.execCommand('copy');
    } finally {
      document.body.removeChild(textarea);
    }
  }

  async function copyText(text) {
    if (navigator.clipboard && window.isSecureContext) {
      await navigator.clipboard.writeText(text);
      return true;
    }

    return fallbackCopy(text);
  }

  function setButtonState(button, text, className) {
    const originalText = button.dataset.originalText || button.textContent;
    button.dataset.originalText = originalText;
    button.textContent = text;
    button.classList.toggle('is-copied', className === 'is-copied');
    button.classList.toggle('is-copy-failed', className === 'is-copy-failed');

    window.setTimeout(() => {
      button.textContent = originalText;
      button.classList.remove('is-copied', 'is-copy-failed');
    }, 1500);
  }

  window.RbookClipboard = { copyText, setButtonState };

  document.addEventListener('click', async (event) => {
    const button = event.target.closest('[data-code-copy]');
    if (!button) return;

    const block = button.closest('.code-block');
    const code = block && block.querySelector('pre code');
    if (!code) {
      window.RbookClipboard.setButtonState(button, '复制失败', 'is-copy-failed');
      return;
    }

    try {
      const copied = await window.RbookClipboard.copyText(code.textContent);
      window.RbookClipboard.setButtonState(
        button,
        copied ? '已复制' : '复制失败',
        copied ? 'is-copied' : 'is-copy-failed'
      );
    } catch (error) {
      window.RbookClipboard.setButtonState(button, '复制失败', 'is-copy-failed');
    }
  });
}());
