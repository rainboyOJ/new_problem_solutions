import test from 'node:test';
import assert from 'node:assert/strict';

import { buildApp } from '../app.js';
import { RbookArticleService } from '../lib/rbook-articles.js';

function createCatalogResponse(items) {
  return new Response(JSON.stringify({ items }), {
    status: 200,
    headers: { 'content-type': 'application/json' },
  });
}

test('RBook article service keeps showAtRbook order and caches the compact full catalog', async () => {
  const requests = [];
  const service = new RbookArticleService({
    apiBaseUrl: 'http://rbook.test',
    publicBaseUrl: 'https://public-rbook.test',
    logger: { warn() {} },
    fetchImpl: async (url) => {
      requests.push(url);
      return createCatalogResponse([
        { id: 'binary-search', title: '二分查找', url: '/algorithm/binary-search/' },
        { id: 'fhq-treap', title: 'FHQ Treap', url: '/data-structure/fhq-treap/' },
      ]);
    },
  });

  assert.deepEqual(await service.getArticles(['fhq-treap', 'missing', 'binary-search']), [
    { id: 'fhq-treap', title: 'FHQ Treap', url: 'https://public-rbook.test/data-structure/fhq-treap/' },
    { id: 'binary-search', title: '二分查找', url: 'https://public-rbook.test/algorithm/binary-search/' },
  ]);
  await service.getArticles(['binary-search']);

  assert.deepEqual(requests, ['http://rbook.test/api/catalog?compact=true&includeHidden=true']);
});

test('RBook article service uses the last successful catalog when refresh fails', async () => {
  let attempts = 0;
  const service = new RbookArticleService({
    apiBaseUrl: 'http://rbook.test',
    publicBaseUrl: 'https://public-rbook.test',
    cacheTtlMs: 0,
    logger: { warn() {} },
    fetchImpl: async () => {
      attempts += 1;
      if (attempts === 1) return createCatalogResponse([
        { id: 'bit', title: '树状数组', url: '/algorithm/bit/' },
      ]);
      throw new Error('RBook is unavailable');
    },
  });

  assert.equal((await service.getArticles(['bit']))[0].title, '树状数组');
  assert.equal((await service.getArticles(['bit']))[0].title, '树状数组');
  assert.equal(attempts, 2);
});

test('problem page renders resolved RBook article links without changing the public detail API', async () => {
  const calls = [];
  const app = await buildApp({
    logger: false,
    rbookArticleService: {
      async getArticles(ids) {
        calls.push(ids);
        return [
          { id: 'fhq-treap', title: 'FHQ Treap', url: 'https://rbook2.roj.ac.cn/data-structure/fhq-treap/' },
          { id: 'binary-search', title: '二分查找', url: 'https://rbook2.roj.ac.cn/algorithm/binary-search/' },
        ];
      },
    },
  });

  try {
    const page = await app.inject('/problems/luogu/P4036/');
    assert.equal(page.statusCode, 200);
    assert.match(page.body, /RBook 文章:/);
    assert.match(page.body, /href="https:\/\/rbook2\.roj\.ac\.cn\/data-structure\/fhq-treap\/"[^>]*target="_blank"[^>]*rel="noopener noreferrer"/);
    assert.match(page.body, /href="https:\/\/rbook2\.roj\.ac\.cn\/algorithm\/binary-search\/"[^>]*>二分查找<\/a>/);
    assert.deepEqual(calls, [['fhq-treap', 'binary-search']]);

    const detail = await app.inject('/api/problems/luogu/P4036');
    assert.equal(detail.statusCode, 200);
    assert.deepEqual(detail.json().showAtRbook, ['fhq-treap', 'binary-search']);
    assert.equal(Object.hasOwn(detail.json(), 'rbookArticles'), false);
  } finally {
    await app.close();
  }
});
