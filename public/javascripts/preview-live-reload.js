(function () {
  const storageKey = `rbook.preview.scroll:${window.location.pathname}`;

  try {
    const storedPosition = window.sessionStorage.getItem(storageKey);
    if (storedPosition) {
      window.sessionStorage.removeItem(storageKey);
      const [x, y] = JSON.parse(storedPosition);
      window.requestAnimationFrame(() => window.scrollTo(x, y));
    }
  } catch {
    // Live reload must remain usable when storage is unavailable.
  }

  function readEvent(event) {
    try {
      return JSON.parse(event.data);
    } catch {
      return null;
    }
  }

  function replaceIfStale(event) {
    const update = readEvent(event);
    if (update && update.url && update.url !== window.location.pathname) {
      window.location.replace(update.url);
    }
  }

  const events = new window.EventSource('/__preview/events');
  events.addEventListener('state', replaceIfStale);
  events.addEventListener('switch', replaceIfStale);
  events.addEventListener('reload', (event) => {
    const update = readEvent(event);
    if (!update || update.url !== window.location.pathname) {
      if (update?.url) window.location.replace(update.url);
      return;
    }

    try {
      window.sessionStorage.setItem(
        storageKey,
        JSON.stringify([window.scrollX, window.scrollY]),
      );
    } catch {
      // Reload still works when storage is unavailable.
    }
    window.location.reload();
  });
}());
