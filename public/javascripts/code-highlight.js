(function () {
  const selector = 'code[class*="language-"]';
  const loadPromises = new Map();
  const elementPromises = new WeakMap();
  let warned = false;

  function warnOnce(message) {
    if (warned) return;
    warned = true;
    console.warn(message);
  }

  function getPrism() {
    return window.Prism;
  }

  function getLanguage(code) {
    const Prism = getPrism();
    if (Prism && Prism.util && typeof Prism.util.getLanguage === 'function') {
      return Prism.util.getLanguage(code);
    }

    const match = /(?:^|\s)language-([\w-]+)(?=\s|$)/i.exec(code.className || '');
    return match ? match[1].toLowerCase() : 'none';
  }

  function loadLanguage(language) {
    if (loadPromises.has(language)) {
      return loadPromises.get(language);
    }

    const Prism = getPrism();
    const autoloader = Prism && Prism.plugins && Prism.plugins.autoloader;
    if (!autoloader || typeof autoloader.loadLanguages !== 'function') {
      return Promise.reject(new Error(`Prism language unavailable: ${language}`));
    }

    const promise = new Promise((resolve, reject) => {
      autoloader.loadLanguages(language, resolve, () => {
        reject(new Error(`Prism language unavailable: ${language}`));
      });
    });
    loadPromises.set(language, promise);
    return promise;
  }

  async function performHighlight(code) {
    if (!code) return false;

    const previousSource = code.dataset.rbookHighlightSource;
    const currentSource = code.textContent;
    const state = code.dataset.rbookHighlight;
    if (state === 'done' && previousSource === currentSource) return true;
    if (state === 'failed' && previousSource === currentSource) return false;

    const language = getLanguage(code);
    if (!language || language === 'none') {
      code.dataset.rbookHighlight = 'skipped';
      code.dataset.rbookHighlightSource = currentSource;
      return false;
    }

    if (code.querySelector && code.querySelector('.token')) {
      code.dataset.rbookHighlight = 'done';
      code.dataset.rbookHighlightSource = currentSource;
      return true;
    }

    const Prism = getPrism();
    if (!Prism || typeof Prism.highlightElement !== 'function') {
      code.dataset.rbookHighlight = 'failed';
      code.dataset.rbookHighlightSource = currentSource;
      warnOnce('Prism is unavailable; code remains unhighlighted.');
      return false;
    }

    code.dataset.rbookHighlight = 'loading';
    code.dataset.rbookHighlightSource = currentSource;

    try {
      if (!Prism.languages[language]) {
        await loadLanguage(language);
      }
      Prism.highlightElement(code);
      code.dataset.rbookHighlight = 'done';
      code.dataset.rbookHighlightSource = code.textContent;
      return true;
    } catch (error) {
      code.dataset.rbookHighlight = 'failed';
      code.dataset.rbookHighlightSource = code.textContent;
      warnOnce(`Code highlighting failed: ${error.message}`);
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
