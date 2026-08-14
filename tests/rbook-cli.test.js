import test from 'node:test';
import assert from 'node:assert/strict';

import { DEFAULT_PREVIEW_HOST, parsePreviewArgs } from '../bin/rbook.js';

test('preview command listens on all interfaces by default', () => {
  const parsed = parsePreviewArgs([], {});

  assert.equal(DEFAULT_PREVIEW_HOST, '0.0.0.0');
  assert.equal(parsed.options.host, '0.0.0.0');
  assert.equal(parsed.options.port, 3000);
  assert.deepEqual(parsed.positionals, []);
});

test('preview command host can be overridden by env or CLI flag', () => {
  const envHost = parsePreviewArgs([], {
    HOST: '127.0.0.1',
    PORT: '3100',
  });
  assert.equal(envHost.options.host, '127.0.0.1');
  assert.equal(envHost.options.port, 3100);

  const cliHost = parsePreviewArgs(['--host', '192.168.1.20', '--port', '3200'], {
    HOST: '127.0.0.1',
    PORT: '3100',
  });
  assert.equal(cliHost.options.host, '192.168.1.20');
  assert.equal(cliHost.options.port, 3200);
});

test('preview command rejects legacy problem positionals', () => {
  assert.throws(
    () => parsePreviewArgs(['luogu', 'P1001'], {}),
    (error) => {
      assert.equal(error.code, 'PREVIEW_POSITIONALS_UNSUPPORTED');
      assert.match(error.message, /no longer accepts problem arguments/);
      return true;
    },
  );
});
