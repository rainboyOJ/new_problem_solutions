(function () {
  const modal = document.getElementById('tagFilterModal');
  const search = document.getElementById('tagFilterSearch');
  const tagList = document.querySelector('[data-tag-list]');
  const resultCount = document.getElementById('tagFilterResultCount');
  const emptyMessage = document.getElementById('tagFilterEmpty');

  if (!modal || !search || !tagList) {
    return;
  }

  const options = Array.from(tagList.querySelectorAll('[data-tag-option]'));
  const popularSection = document.querySelector('[data-tag-popular]');

  function visibleOptions() {
    return options.filter((option) => !option.hidden);
  }

  function updateResultCount(query, count) {
    if (!resultCount) {
      return;
    }

    resultCount.textContent = query
      ? `匹配 ${count} 个标签`
      : `共 ${Math.max(0, options.length - 1)} 个标签`;
  }

  function filterOptions() {
    const query = search.value.trim().toLocaleLowerCase('zh-CN');
    let matchCount = 0;

    for (const option of options) {
      const name = option.dataset.tagName || '';
      const matches = query.length === 0
        ? true
        : name.length > 0 && name.toLocaleLowerCase('zh-CN').includes(query);
      option.hidden = !matches;
      if (matches && name.length > 0) {
        matchCount += 1;
      }
    }

    if (popularSection) {
      popularSection.hidden = query.length > 0;
    }
    if (emptyMessage) {
      emptyMessage.hidden = matchCount > 0 || query.length === 0;
    }
    updateResultCount(query, matchCount);
  }

  function navigateToTag(tag) {
    const url = new URL(window.location.href);
    if (tag) {
      url.searchParams.set('tag', tag);
    } else {
      url.searchParams.delete('tag');
    }
    url.searchParams.delete('page');
    window.location.assign(url.toString());
  }

  function moveFocus(direction) {
    const available = visibleOptions();
    if (!available.length) {
      return;
    }

    const current = document.activeElement;
    const currentIndex = available.indexOf(current);
    const nextIndex = currentIndex === -1
      ? (direction > 0 ? 0 : available.length - 1)
      : (currentIndex + direction + available.length) % available.length;
    available[nextIndex].focus();
  }

  function focusBoundary(last) {
    const available = visibleOptions();
    if (available.length) {
      available[last ? available.length - 1 : 0].focus();
    }
  }

  modal.addEventListener('shown.bs.modal', () => {
    search.focus();
    search.select();
  });

  modal.addEventListener('hidden.bs.modal', () => {
    search.value = '';
    filterOptions();
  });

  search.addEventListener('input', filterOptions);

  document.addEventListener('click', (event) => {
    const option = event.target.closest('[data-tag-option]');
    const clearButton = event.target.closest('[data-tag-clear]');

    if (option) {
      navigateToTag(option.dataset.tagName || '');
    } else if (clearButton) {
      navigateToTag('');
    }
  });

  document.addEventListener('keydown', (event) => {
    const option = event.target.closest('[data-tag-option]');
    if (option) {
      if (event.key === 'ArrowDown') {
        event.preventDefault();
        moveFocus(1);
      } else if (event.key === 'ArrowUp') {
        event.preventDefault();
        moveFocus(-1);
      } else if (event.key === 'Home') {
        event.preventDefault();
        focusBoundary(false);
      } else if (event.key === 'End') {
        event.preventDefault();
        focusBoundary(true);
      } else if (event.key === 'Enter' || event.key === ' ') {
        event.preventDefault();
        navigateToTag(option.dataset.tagName || '');
      }
      return;
    }

    if (event.target === search && event.key === 'ArrowDown') {
      event.preventDefault();
      focusBoundary(false);
    } else if (event.target === search && event.key === 'ArrowUp') {
      event.preventDefault();
      focusBoundary(true);
    }
  });

  filterOptions();
}());
