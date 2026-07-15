(function () {
  const storageKey = 'rbook.problem-set.progress';
  const tasks = Array.from(document.querySelectorAll('[data-problem-task]'));

  if (!tasks.length) return;

  function readProgress() {
    try {
      const raw = window.localStorage.getItem(storageKey);
      const parsed = raw ? JSON.parse(raw) : {};
      return parsed && typeof parsed === 'object' ? parsed : {};
    } catch (error) {
      return {};
    }
  }

  function writeProgress(progress) {
    try {
      window.localStorage.setItem(storageKey, JSON.stringify(progress));
    } catch (error) {
      // Ignore storage failures; the page still works for the current session.
    }
  }

  function syncCount() {
    const completed = tasks.filter((task) => task.classList.contains('is-completed')).length;
    const counter = document.querySelector('[data-problem-set-progress]');
    if (counter) {
      counter.textContent = `${completed} / ${tasks.length} 已完成`;
    }
  }

  function applyTaskState(task, checked) {
    const input = task.querySelector('[data-problem-toggle]');
    if (input) input.checked = checked;
    task.classList.toggle('is-completed', checked);
  }

  function applyKeyState(key, checked) {
    for (const task of tasks) {
      if ((task.dataset.problemKey || '') === key) {
        applyTaskState(task, checked);
      }
    }
  }

  const progress = readProgress();

  for (const task of tasks) {
    const key = task.dataset.problemKey || '';
    applyTaskState(task, Boolean(progress[key]));
  }
  syncCount();

  document.addEventListener('change', (event) => {
    const input = event.target.closest('[data-problem-toggle]');
    if (!input) return;

    const task = input.closest('[data-problem-task]');
    if (!task) return;

    const key = task.dataset.problemKey || '';
    if (!key) return;

    if (input.checked) {
      progress[key] = true;
    } else {
      delete progress[key];
    }

    applyKeyState(key, input.checked);
    writeProgress(progress);
    syncCount();
  });
}());
