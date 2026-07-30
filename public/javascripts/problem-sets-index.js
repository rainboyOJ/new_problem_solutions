(function () {
  const storageKey = 'rbook.problem-set.progress';
  const root = document.querySelector('[data-problem-set-directory]');

  if (!root) return;

  const searchInput = root.querySelector('[data-problem-set-search]');
  const resultCount = root.querySelector('[data-problem-set-result-count]');
  const rows = Array.from(root.querySelectorAll('[data-problem-set-row]'));
  const body = root.querySelector('tbody');
  const sortButtons = Array.from(root.querySelectorAll('[data-problem-set-sort]'));
  let sortKey = '';
  let sortDirection = 'asc';

  function readProgress() {
    try {
      const raw = window.localStorage.getItem(storageKey);
      const parsed = raw ? JSON.parse(raw) : {};
      return parsed && typeof parsed === 'object' && !Array.isArray(parsed) ? parsed : {};
    } catch (error) {
      return {};
    }
  }

  function taskKeys(row) {
    try {
      const parsed = JSON.parse(row.dataset.problemSetTaskKeys || '[]');
      return Array.isArray(parsed) ? parsed : [];
    } catch (error) {
      return [];
    }
  }

  function completedCount(row, progress) {
    return taskKeys(row).filter((key) => progress[key] === true).length;
  }

  function updateProgress() {
    const progress = readProgress();

    for (const row of rows) {
      const total = Number(row.dataset.problemSetTaskCount || 0);
      const completed = completedCount(row, progress);
      const value = row.querySelector('[data-problem-set-progress-value]');
      if (value) value.textContent = `${completed} / ${total}`;
      row.dataset.problemSetCompleted = String(completed);
    }
  }

  function compareRows(left, right) {
    if (!sortKey) {
      return Number(left.dataset.problemSetPosition) - Number(right.dataset.problemSetPosition);
    }

    let result = 0;
    if (sortKey === 'title' || sortKey === 'description') {
      const field = sortKey === 'title' ? 'problemSetTitle' : 'problemSetDescription';
      result = (left.dataset[field] || '').localeCompare(
        right.dataset[field] || '',
        'zh-CN',
      );
    } else if (sortKey === 'count') {
      result = Number(left.dataset.problemSetTaskCount) - Number(right.dataset.problemSetTaskCount);
    } else {
      const leftTotal = Number(left.dataset.problemSetTaskCount || 0);
      const rightTotal = Number(right.dataset.problemSetTaskCount || 0);
      const leftRatio = leftTotal ? Number(left.dataset.problemSetCompleted || 0) / leftTotal : 0;
      const rightRatio = rightTotal ? Number(right.dataset.problemSetCompleted || 0) / rightTotal : 0;
      result = leftRatio - rightRatio;
    }

    if (result === 0) {
      result = Number(left.dataset.problemSetPosition) - Number(right.dataset.problemSetPosition);
    }
    return sortDirection === 'asc' ? result : -result;
  }

  function updateSortState() {
    for (const button of sortButtons) {
      const key = button.dataset.problemSetSort || '';
      const header = root.querySelector(`[data-problem-set-sort-header="${key}"]`);
      if (!header) continue;

      const active = key === sortKey;
      header.setAttribute('aria-sort', active ? (sortDirection === 'asc' ? 'ascending' : 'descending') : 'none');
      button.dataset.sortDirection = active ? sortDirection : '';
    }
  }

  function render() {
    const query = (searchInput?.value || '').trim().toLocaleLowerCase('zh-CN');
    const orderedRows = [...rows].sort(compareRows);
    let matched = 0;

    for (const row of orderedRows) {
      const searchable = `${row.dataset.problemSetTitle || ''} ${row.dataset.problemSetDescription || ''}`
        .toLocaleLowerCase('zh-CN');
      const visible = !query || searchable.includes(query);
      row.hidden = !visible;
      if (visible) matched += 1;
      body.appendChild(row);
    }

    if (resultCount) {
      resultCount.textContent = query ? `匹配 ${matched} 份题目单` : `共 ${rows.length} 份题目单`;
    }
    updateSortState();
  }

  for (const button of sortButtons) {
    button.addEventListener('click', () => {
      const nextKey = button.dataset.problemSetSort || '';
      if (sortKey === nextKey) {
        sortDirection = sortDirection === 'asc' ? 'desc' : 'asc';
      } else {
        sortKey = nextKey;
        sortDirection = 'asc';
      }
      render();
    });
  }

  searchInput?.addEventListener('input', render);
  window.addEventListener('storage', (event) => {
    if (event.key === storageKey) {
      updateProgress();
      render();
    }
  });
  window.addEventListener('rbook:problem-set-progress-updated', () => {
    updateProgress();
    render();
  });

  updateProgress();
  render();
}());
