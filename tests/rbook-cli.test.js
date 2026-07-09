import test from 'node:test';
import assert from 'node:assert/strict';

import { DEFAULT_PREVIEW_HOST, parsePreviewArgs } from '../bin/rbook.js';

test('preview command listens on all interfaces by default', () => {
  const parsed = parsePreviewArgs(['luogu', '1001'], {});

  assert.equal(DEFAULT_PREVIEW_HOST, '0.0.0.0');
  assert.equal(parsed.options.host, '0.0.0.0');
  assert.equal(parsed.options.port, 3000);
  assert.deepEqual(parsed.positionals, ['luogu', '1001']);
});

test('preview command host can be overridden by env or CLI flag', () => {
  const envHost = parsePreviewArgs(['luogu', '1001'], {
    HOST: '127.0.0.1',
    PORT: '3100',
  });
  assert.equal(envHost.options.host, '127.0.0.1');
  assert.equal(envHost.options.port, 3100);

  const cliHost = parsePreviewArgs(['luogu', '1001', '--host', '192.168.1.20', '--port', '3200'], {
    HOST: '127.0.0.1',
    PORT: '3100',
  });
  assert.equal(cliHost.options.host, '192.168.1.20');
  assert.equal(cliHost.options.port, 3200);
});
