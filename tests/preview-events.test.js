import test from 'node:test';
import assert from 'node:assert/strict';
import { EventEmitter } from 'node:events';

import { PreviewEventBroker } from '../lib/preview-events.js';

class FakeActivePreview {
  constructor() {
    this.listener = null;
  }

  getClientState() {
    return {
      type: 'state',
      version: 1,
      url: '/problems/luogu/P1001/',
    };
  }

  subscribe(listener) {
    this.listener = listener;
    return () => {
      this.listener = null;
    };
  }

  emit(update) {
    this.listener?.(update);
  }
}

class FakeStream {
  constructor() {
    this.chunks = [];
    this.ended = false;
  }

  write(chunk) {
    this.chunks.push(chunk);
    return true;
  }

  end() {
    this.ended = true;
  }
}

test('PreviewEventBroker sends initial state and broadcasts to every client', () => {
  const active = new FakeActivePreview();
  const broker = new PreviewEventBroker(active, { heartbeatMs: 0 });
  const firstRequest = new EventEmitter();
  const secondRequest = new EventEmitter();
  const first = new FakeStream();
  const second = new FakeStream();

  broker.connect(first, firstRequest);
  broker.connect(second, secondRequest);

  assert.match(first.chunks.join(''), /event: state/);
  assert.match(first.chunks.join(''), /"url":"\/problems\/luogu\/P1001\/"/);
  assert.equal(broker.clientCount, 2);

  active.emit({
    type: 'switch',
    version: 2,
    url: '/problems/luogu/P1002/',
  });

  assert.match(first.chunks.join(''), /event: switch/);
  assert.match(second.chunks.join(''), /"version":2/);

  firstRequest.emit('close');
  assert.equal(broker.clientCount, 1);

  broker.close();
  assert.equal(second.ended, true);
  assert.equal(broker.clientCount, 0);
  assert.equal(active.listener, null);
});
