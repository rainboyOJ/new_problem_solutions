(function () {
  function getResourceUrl(fileName) {
    const baseUrl = window.location.pathname.replace(/\/$/, '');
    return `${baseUrl}/${encodeURIComponent(fileName)}`;
  }

  async function openGenModal(fileName) {
    const modalEl = document.getElementById('genModal');
    const codeEl = document.getElementById('genCodeContent');
    const fileNameEl = document.getElementById('genModalFileName');
    const downloadBtn = document.getElementById('genDownloadBtn');

    if (!modalEl || !codeEl || !fileNameEl || !downloadBtn || !fileName) {
      return;
    }

    const modal = new bootstrap.Modal(modalEl);
    const fileUrl = getResourceUrl(fileName);
    const lang = fileName.endsWith('.py') ? 'python' : 'cpp';

    fileNameEl.textContent = `(${fileName})`;
    downloadBtn.href = fileUrl;
    downloadBtn.setAttribute('download', fileName);
    codeEl.className = `language-${lang}`;
    codeEl.textContent = '加载中...';
    modal.show();

    try {
      const response = await fetch(fileUrl);
      if (!response.ok) {
        throw new Error(`HTTP ${response.status}`);
      }

      codeEl.textContent = await response.text();
      if (typeof Prism !== 'undefined') {
        Prism.highlightElement(codeEl);
      }
    } catch (error) {
      codeEl.className = `language-${lang}`;
      codeEl.textContent = `// 加载 ${fileName} 失败: ${error.message}`;
    }
  }

  window.openGenModal = openGenModal;

  document.addEventListener('click', (event) => {
    const button = event.target.closest('[data-gen-file]');
    if (!button || button.disabled || button.classList.contains('disabled')) {
      return;
    }

    openGenModal(button.dataset.genFile);
  });
}());
