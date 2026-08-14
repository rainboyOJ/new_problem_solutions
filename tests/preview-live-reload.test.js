import test from 'node:test';
import assert from 'node:assert/strict';
import fs from 'fs';
import vm from 'node:vm';

function loadClient(options = {}) {
  const stored = new Map(Object.entries(options.storage || {}));
  const calls = {
    reload: 0,
    replace: [],
    scrollTo: [],
  };

  class FakeEventSource {
    static instances = [];

    constructor(url) {
      this.url = url;
      this.listeners = new Map();
      FakeEventSource.instances.push(this);
    }

    addEventListener(type, listener) {
      this.listeners.set(type, listener);
    }

    emit(type, data) {
      this.listeners.get(type)?.({ data: JSON.stringify(data) });
    }
  }

  const window = {
    location: {
      pathname: options.pathname || '/problems/luogu/P1001/',
      reload() {
        calls.reload += 1;
      },
      replace(url) {
        calls.replace.push(url);
      },
    },
    scrollX: options.scrollX || 0,
    scrollY: options.scrollY || 0,
    scrollTo(x, y) {
      calls.scrollTo.push([x, y]);
    },
    sessionStorage: {
      getItem(key) {
        return stored.get(key) ?? null;
      },
      setItem(key, value) {
        stored.set(key, value);
      },
      removeItem(key) {
        stored.delete(key);
      },
    },
    requestAnimationFrame(callback) {
      callback();
    },
    EventSource: FakeEventSource,
  };
  window.window = window;

  const script = fs.readFileSync('public/javascripts/preview-live-reload.js', 'utf8');
  vm.runInNewContext(script, { window, JSON });

  return {
    calls,
    source: FakeEventSource.instances[0],
    stored,
  };
}

test('preview live reload reconnect state corrects a stale problem URL', () => {
  const state = loadClient({ pathname: '/problems/luogu/P1001/' });

  assert.equal(state.source.url, '/__preview/events');
  state.source.emit('state', {
    type: 'state',
    version: 4,
    url: '/problems/luogu/P1002/',
  });

  assert.deepEqual(state.calls.replace, ['/problems/luogu/P1002/']);
  assert.equal(state.calls.reload, 0);
});

test('preview live reload saves and restores scroll for same-problem reloads', () => {
  const first = loadClient({
    pathname: '/problems/luogu/P1001/',
    scrollX: 12,
    scrollY: 345,
  });

  first.source.emit('reload', {
    type: 'reload',
    version: 2,
    url: '/problems/luogu/P1001/',
  });

  assert.equal(first.calls.reload, 1);
  assert.equal(
    first.stored.get('rbook.preview.scroll:/problems/luogu/P1001/'),
    '[12,345]',
  );

  const second = loadClient({
    pathname: '/problems/luogu/P1001/',
    storage: Object.fromEntries(first.stored),
  });

  assert.deepEqual(second.calls.scrollTo, [[12, 345]]);
  assert.equal(second.stored.size, 0);
});

test('preview live reload replaces the URL for switch events', () => {
  const state = loadClient({ pathname: '/problems/luogu/P1001/' });

  state.source.emit('switch', {
    type: 'switch',
    version: 2,
    url: '/problems/luogu/P1002/',
  });

  assert.deepEqual(state.calls.replace, ['/problems/luogu/P1002/']);
  assert.equal(state.stored.size, 0);
});
