(function () {
  const selector = 'code[class*="language-"]';
  const endpoint = '/api/highlight';
  const elementPromises = new WeakMap();
  let warned = false;

  function warnOnce(message) {
    if (warned) return;
    warned = true;
    console.warn(message);
  }

  function getLanguage(code) {
    const match = /(?:^|\s)language-([\w+#.-]+)(?=\s|$)/i.exec(code.className || '');
    return match ? match[1].toLowerCase() : 'none';
  }

  // 语法高亮在服务端做（Shiki）：页面里的代码块服务端已经染好色，
  // 这里只处理运行时才出现的代码（Md Raw 弹窗、随机数据生成器）。
  // 浏览器因此不需要背一份完整的语法包。
  async function performHighlight(code) {
    if (!code) return false;

    // 服务端渲染的块已经带 token，直接跳过。
    if (code.dataset.rbookHighlight === 'server') return true;

    const source = code.textContent;
    const language = getLanguage(code);
    if (!language || language === 'none') {
      code.dataset.rbookHighlight = 'skipped';
      return false;
    }

    code.dataset.rbookHighlight = 'loading';

    try {
      const response = await fetch(endpoint, {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({ code: source, language }),
      });
      if (!response.ok) throw new Error(`HTTP ${response.status}`);

      const data = await response.json();
      // 服务端只返回转义后的 token 片段；拿不到就保留原来的纯文本。
      if (typeof data.html !== 'string') {
        code.dataset.rbookHighlight = 'skipped';
        return false;
      }

      code.innerHTML = data.html;
      code.dataset.rbookHighlight = 'done';
      return true;
    } catch (error) {
      code.dataset.rbookHighlight = 'failed';
      warnOnce(`代码高亮失败: ${error.message}`);
      return false;
    }
  }

  function highlightElement(code) {
    if (!code) return Promise.resolve(false);

    const inFlight = elementPromises.get(code);
    if (inFlight) return inFlight;

    const promise = performHighlight(code).finally(() => {
      elementPromises.delete(code);
    });
    elementPromises.set(code, promise);
    return promise;
  }

  function collectCode(root) {
    const elements = [];
    if (root && typeof root.matches === 'function' && root.matches(selector)) {
      elements.push(root);
    }
    if (root && typeof root.querySelectorAll === 'function') {
      elements.push(...root.querySelectorAll(selector));
    }
    return elements;
  }

  async function highlight(root) {
    const elements = collectCode(root || document);
    return Promise.all(elements.map((code) => highlightElement(code)));
  }

  window.RbookCodeHighlight = { highlight, highlightElement };
  highlight(document);
}());
