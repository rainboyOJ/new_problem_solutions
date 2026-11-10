import test from 'node:test';
import assert from 'node:assert/strict';
import { readFileSync } from 'node:fs';
import vm from 'node:vm';

function loadApi({ fetchImpl } = {}) {
  const calls = [];
  const window = {};
  const fetch = async (url) => {
    calls.push(url);
    return fetchImpl(url);
  };
  const script = readFileSync('public/javascripts/api-client.js', 'utf8');
  vm.runInNewContext(script, { fetch, Promise, window });
  return { api: window.RbookApi, calls };
}

function okResponse(body, { json } = {}) {
  return {
    ok: true,
    status: 200,
    async json() {
      if (json) return json(body);
      return body;
    },
    async text() {
      return body;
    },
  };
}

test('RbookApi.getJSON returns the parsed payload', async () => {
  const { api, calls } = loadApi({ fetchImpl: async () => okResponse({ md_content: '# hi' }) });

  const data = await api.getJSON('/api/problems/luogu/P1001/statement/raw');

  assert.deepEqual(data, { md_content: '# hi' });
  assert.deepEqual(calls, ['/api/problems/luogu/P1001/statement/raw']);
});

test('RbookApi.getText returns the raw body', async () => {
  const { api } = loadApi({ fetchImpl: async () => okResponse('plain text') });

  assert.equal(await api.getText('/some/url'), 'plain text');
});

test('RbookApi throws with the status on a non-2xx response', async () => {
  const { api } = loadApi({
    fetchImpl: async () => ({ ok: false, status: 404, async json() { return {}; } }),
  });

  await assert.rejects(
    () => api.getJSON('/api/problems/luogu/P9999/statement/raw'),
    (error) => {
      assert.equal(error.status, 404);
      assert.match(error.message, /404/);
      return true;
    },
  );
});

test('RbookApi propagates JSON parse failures', async () => {
  const { api } = loadApi({
    fetchImpl: async () => okResponse(null, { json: () => { throw new Error('bad json'); } }),
  });

  await assert.rejects(() => api.getJSON('/api/whatever'), /bad json/);
});
