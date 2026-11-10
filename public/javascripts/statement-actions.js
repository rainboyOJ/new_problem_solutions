(function () {
  const copyButton = document.querySelector('[data-statement-copy]');
  const clipboard = window.RbookClipboard;
  const api = window.RbookApi;

  if (!copyButton || !clipboard || !api) return;

  const oj = copyButton.dataset.problemOj;
  const problemId = copyButton.dataset.problemId;

  let cachedMarkdown = null;
  let inFlight = null;

  // 题面原文只在第一次需要时请求，复制与“查看原文”共用这份结果。
  function load() {
    if (cachedMarkdown !== null) return Promise.resolve(cachedMarkdown);
    if (inFlight) return inFlight;

    const url = `/api/problems/${encodeURIComponent(oj)}/${encodeURIComponent(problemId)}/statement/raw`;
    inFlight = api.getJSON(url)
      .then((data) => {
        if (!data || typeof data.md_content !== 'string') {
          throw new Error('Statement response is invalid');
        }
        cachedMarkdown = data.md_content;
        return cachedMarkdown;
      })
      .finally(() => {
        inFlight = null;
      });

    return inFlight;
  }

  window.RbookStatement = { load };

  copyButton.addEventListener('click', async () => {
    try {
      const markdown = await load();
      const copied = await clipboard.copyText(markdown);
      clipboard.setButtonState(
        copyButton,
        copied ? '已复制' : '复制失败',
        copied ? 'is-copied' : 'is-copy-failed'
      );
    } catch (error) {
      clipboard.setButtonState(copyButton, '复制失败', 'is-copy-failed');
    }
  });

  copyButton.hidden = false;
}());
