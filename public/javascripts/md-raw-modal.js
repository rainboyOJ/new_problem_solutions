(function () {
  const Modal = window.bootstrap && window.bootstrap.Modal;
  const api = window.RbookApi;

  if (!Modal || !api) return;

  // 每种 kind 对应一份原文接口，页面只传业务标识，不传完整 URL。
  function buildUrl(trigger) {
    const kind = trigger.dataset.mdRawKind || 'article';
    const oj = encodeURIComponent(trigger.dataset.problemOj || '');
    const problemId = encodeURIComponent(trigger.dataset.problemId || '');
    const base = `/api/problems/${oj}/${problemId}`;

    if (kind === 'statement') return `${base}/statement/raw`;
    if (kind === 'ai-note') {
      const slug = encodeURIComponent(trigger.dataset.noteSlug || '');
      return `${base}/ai-notes/${slug}/raw`;
    }
    return base;
  }

  // 题面原文与“复制题面”共用同一份缓存，避免重复请求。
  function fetchMarkdown(trigger) {
    const kind = trigger.dataset.mdRawKind || 'article';
    if (kind === 'statement' && window.RbookStatement) {
      return window.RbookStatement.load();
    }
    return api.getJSON(buildUrl(trigger)).then((data) => {
      if (!data || typeof data.md_content !== 'string') {
        throw new Error('Markdown response is invalid');
      }
      return data.md_content;
    });
  }

  function createController(trigger) {
    const key = trigger.dataset.mdRawKey || 'article';
    const modalElement = document.querySelector(`[data-md-raw-modal][data-md-raw-key="${key}"]`);
    if (!modalElement) return null;

    const copyButton = modalElement.querySelector('[data-md-raw-copy]');
    const retryButton = modalElement.querySelector('[data-md-raw-retry]');
    const status = modalElement.querySelector('[data-md-raw-status]');
    const content = modalElement.querySelector('[data-md-raw-content]');
    const lineNumbers = modalElement.querySelector('[data-md-raw-line-numbers]');
    const code = modalElement.querySelector('[data-md-raw-code]');

    if (!copyButton || !retryButton || !status || !content || !lineNumbers || !code) {
      return null;
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
      if (cachedMarkdown !== null) return Promise.resolve(cachedMarkdown);
      if (inFlight) return inFlight;

      showLoading();
      inFlight = fetchMarkdown(trigger)
        .then((markdown) => {
          cachedMarkdown = markdown;
          showReady(cachedMarkdown);
          return cachedMarkdown;
        })
        .catch(() => {
          showError();
          return null;
        })
        .finally(() => {
          inFlight = null;
        });

      return inFlight;
    }

    trigger.addEventListener('click', () => {
      modal.show(trigger);
      return loadMarkdown();
    });

    // 触发按钮在另一个弹窗（题面 modal）里时，焦点会留在那层弹窗上，
    // 于是 Esc 事件冒泡进外层 modal，被它先关掉。切完动画后把焦点移进来，
    // 让 Esc 关的是当前这层原文弹窗。
    modalElement.addEventListener('shown.bs.modal', () => {
      if (typeof trigger.closest !== 'function' || !trigger.closest('.modal')) return;
      const closeButton = modalElement.querySelector('.btn-close');
      const target = closeButton || modalElement;
      if (typeof target.focus === 'function') target.focus();
    });

    retryButton.addEventListener('click', () => loadMarkdown());

    modalElement.addEventListener('hidden.bs.modal', () => {
      window.setTimeout(() => trigger.focus(), 0);
    });

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
    return { modal, loadMarkdown };
  }

  const triggers = document.querySelectorAll('[data-md-raw-trigger]');
  for (const trigger of triggers) createController(trigger);
}());
