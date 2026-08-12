(function () {
  const trigger = document.querySelector('[data-md-raw-trigger]');
  const modalElement = document.querySelector('[data-md-raw-modal]');
  const copyButton = document.querySelector('[data-md-raw-copy]');
  const retryButton = document.querySelector('[data-md-raw-retry]');
  const status = document.querySelector('[data-md-raw-status]');
  const content = document.querySelector('[data-md-raw-content]');
  const lineNumbers = document.querySelector('[data-md-raw-line-numbers]');
  const code = document.querySelector('[data-md-raw-code]');
  const Modal = window.bootstrap && window.bootstrap.Modal;

  if (!trigger || !modalElement || !copyButton || !retryButton || !status
    || !content || !lineNumbers || !code || !Modal) {
    return;
  }

  const modal = Modal.getOrCreateInstance(modalElement);
  let cachedMarkdown = null;
  let inFlight = null;

  function showLoading() {
    status.textContent = '加载中...';
    status.hidden = false;
    retryButton.hidden = true;
    content.hidden = true;
    copyButton.disabled = true;
  }

  function showReady(markdown) {
    code.textContent = markdown;
    lineNumbers.textContent = markdown
      .split('\n')
      .map((_, index) => index + 1)
      .join('\n');
    status.hidden = true;
    retryButton.hidden = true;
    content.hidden = false;
    copyButton.disabled = false;

    const highlighter = window.RbookCodeHighlight;
    if (highlighter && typeof highlighter.highlightElement === 'function') {
      Promise.resolve(highlighter.highlightElement(code)).catch(() => {});
    }
  }

  function showError() {
    status.textContent = 'Markdown 加载失败';
    status.hidden = false;
    retryButton.hidden = false;
    content.hidden = true;
    copyButton.disabled = true;
  }

  function loadMarkdown() {
    if (cachedMarkdown !== null) {
      return Promise.resolve(cachedMarkdown);
    }
    if (inFlight) return inFlight;

    showLoading();
    inFlight = (async () => {
      try {
        const response = await fetch(trigger.dataset.mdRawUrl);
        if (!response.ok) throw new Error('Markdown request failed');

        const data = await response.json();
        if (!data || typeof data.md_content !== 'string') {
          throw new Error('Markdown response is invalid');
        }

        cachedMarkdown = data.md_content;
        showReady(cachedMarkdown);
        return cachedMarkdown;
      } catch (error) {
        showError();
        return null;
      } finally {
        inFlight = null;
      }
    })();

    return inFlight;
  }

  trigger.addEventListener('click', () => {
    modal.show(trigger);
    return loadMarkdown();
  });

  retryButton.addEventListener('click', () => loadMarkdown());

  copyButton.addEventListener('click', async () => {
    const clipboard = window.RbookClipboard;
    if (cachedMarkdown === null || !clipboard) return;

    try {
      const copied = await clipboard.copyText(cachedMarkdown);
      clipboard.setButtonState(
        copyButton,
        copied ? '已复制' : '复制失败',
        copied ? 'is-copied' : 'is-copy-failed'
      );
    } catch (error) {
      clipboard.setButtonState(copyButton, '复制失败', 'is-copy-failed');
    }
  });

  trigger.hidden = false;
}());
