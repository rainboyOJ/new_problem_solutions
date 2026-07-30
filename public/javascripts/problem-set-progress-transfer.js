(function () {
  const storageKey = 'rbook.problem-set.progress';
  const fileType = 'rbook.problem-set.progress';
  const fileVersion = 1;
  const root = document.querySelector('[data-problem-set-transfer]');

  if (!root) return;

  const importButton = root.querySelector('[data-progress-import]');
  const exportButton = root.querySelector('[data-progress-export]');
  const fileInput = root.querySelector('[data-progress-file]');
  const statusNode = root.querySelector('[data-progress-status]');

  function setStatus(message, isError) {
    if (!statusNode) return;
    statusNode.textContent = message;
    statusNode.classList.toggle('text-danger', Boolean(isError));
    statusNode.classList.toggle('text-muted', !isError);
  }

  function readProgress() {
    try {
      const raw = window.localStorage.getItem(storageKey);
      const parsed = raw ? JSON.parse(raw) : {};
      return parsed && typeof parsed === 'object' && !Array.isArray(parsed) ? parsed : {};
    } catch (error) {
      return {};
    }
  }

  function writeProgress(progress) {
    window.localStorage.setItem(storageKey, JSON.stringify(progress));
    window.dispatchEvent(new CustomEvent('rbook:problem-set-progress-updated'));
  }

  function normalizeProgress(progress) {
    if (!progress || typeof progress !== 'object' || Array.isArray(progress)) {
      return null;
    }

    const normalized = {};
    for (const [key, value] of Object.entries(progress)) {
      if (value === true && typeof key === 'string' && key.length > 0) {
        normalized[key] = true;
      }
    }
    return normalized;
  }

  function validateImportPayload(payload) {
    if (!payload || typeof payload !== 'object' || Array.isArray(payload)) {
      throw new Error('文件格式不正确');
    }

    if (payload.type !== fileType) {
      throw new Error('文件类型不正确');
    }

    if (payload.version !== fileVersion) {
      throw new Error('文件版本不支持');
    }

    const progress = normalizeProgress(payload.progress);
    if (!progress) {
      throw new Error('进度数据不正确');
    }

    return progress;
  }

  function countProgress(progress) {
    return Object.keys(progress).length;
  }

  function exportProgress() {
    try {
      const progress = normalizeProgress(readProgress()) || {};
      const payload = {
        type: fileType,
        version: fileVersion,
        exportedAt: new Date().toISOString(),
        progress,
      };
      const blob = new Blob([JSON.stringify(payload, null, 2) + '\n'], {
        type: 'application/json',
      });
      const url = URL.createObjectURL(blob);
      const link = document.createElement('a');
      const date = new Date().toISOString().slice(0, 10);

      link.href = url;
      link.download = `rbook-progress-${date}.json`;
      document.body.appendChild(link);
      link.click();
      link.remove();
      URL.revokeObjectURL(url);
      setStatus(`已导出 ${countProgress(progress)} 条进度`, false);
    } catch (error) {
      setStatus(`导出失败：${error.message}`, true);
    }
  }

  function chooseImportMode() {
    const choice = window.prompt('请选择导入方式：\n1. 合并到当前进度\n2. 覆盖当前进度', '1');

    if (choice === '1') {
      return 'merge';
    }

    if (choice === '2') {
      return 'overwrite';
    }

    return '';
  }

  function importProgress(importedProgress) {
    const mode = chooseImportMode();
    if (!mode) {
      setStatus('已取消导入', false);
      return;
    }

    const nextProgress = mode === 'merge'
      ? { ...readProgress(), ...importedProgress }
      : { ...importedProgress };

    writeProgress(nextProgress);
    const action = mode === 'merge' ? '合并' : '覆盖';
    setStatus(`已${action}导入 ${countProgress(importedProgress)} 条进度`, false);
  }

  function readSelectedFile(file) {
    const reader = new FileReader();

    reader.addEventListener('load', () => {
      try {
        const payload = JSON.parse(String(reader.result || ''));
        importProgress(validateImportPayload(payload));
      } catch (error) {
        setStatus(`导入失败：${error.message}`, true);
      } finally {
        fileInput.value = '';
      }
    });

    reader.addEventListener('error', () => {
      setStatus('导入失败：无法读取文件', true);
      fileInput.value = '';
    });

    reader.readAsText(file);
  }

  if (exportButton) {
    exportButton.addEventListener('click', exportProgress);
  }

  if (importButton && fileInput) {
    importButton.addEventListener('click', () => fileInput.click());
    fileInput.addEventListener('change', () => {
      const file = fileInput.files && fileInput.files[0];
      if (!file) return;
      readSelectedFile(file);
    });
  }
}());
