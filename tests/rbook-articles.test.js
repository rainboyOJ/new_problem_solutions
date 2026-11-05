import test from 'node:test';
import assert from 'node:assert/strict';
import fs from 'node:fs';
import os from 'node:os';
import path from 'node:path';

import { buildApp } from '../app.js';
import ProblemManager from '../lib/problem.js';
import { RbookArticleService, parseRbookRef } from '../lib/rbook-articles.js';

function jsonResponse(payload, status = 200) {
  return new Response(JSON.stringify(payload), {
    status,
    headers: { 'content-type': 'application/json' },
  });
}

// rbook2 是带 /api/catalog 的 Node 服务，rbook1 是静态站只提供 /catalog.json。
const RBOOK2_CATALOG = [
  { id: 'binary-search', title: '二分查找', url: '/algorithm/binary-search/' },
  { id: 'fhq-treap', title: 'FHQ Treap', url: '/data-structure/fhq-treap/' },
  { id: 'bit', title: '树状数组', url: '/algorithm/bit/' },
  { id: 'base', title: 'rbook2 的 base', url: '/rbook2/base/' },
];
const RBOOK1_CATALOG = [
  { id: 'presum', title: '前缀和', url: '/base/presum/index.html' },
  { id: 'base', title: 'rbook1 的 base', url: '/base/index.html' },
];

function createFetch(requests, options = {}) {
  return async (url) => {
    requests.push(url);
    if (String(url).includes('/api/catalog')) {
      if (options.rbook2Fails) throw new Error('rbook2 down');
      return jsonResponse({ items: RBOOK2_CATALOG });
    }
    if (String(url).endsWith('/catalog.json')) {
      if (options.rbook1Fails) return jsonResponse({ error: 'not found' }, 404);
      return jsonResponse({ site: 'rbook1', items: RBOOK1_CATALOG });
    }
    throw new Error(`unexpected url ${url}`);
  };
}

function createService(options = {}) {
  const requests = [];
  const service = new RbookArticleService({
    apiBaseUrl: 'http://rbook2.test',
    publicBaseUrl: 'https://rbook2.public.test',
    rbook1CatalogUrl: 'https://rbook1.test/catalog.json',
    rbook1PublicBaseUrl: 'https://rbook1.public.test',
    logger: { warn() {} },
    fetchImpl: createFetch(requests, options),
    ...(options.cacheTtlMs === undefined ? {} : { cacheTtlMs: options.cacheTtlMs }),
  });
  return { service, requests };
}

test('rbook 引用必须带站点前缀，解析器拒绝裸 id 与未知站点', () => {
  assert.deepEqual(parseRbookRef('rbook2:binary-search'), { site: 'rbook2', id: 'binary-search' });
  assert.deepEqual(parseRbookRef('rbook1:presum'), { site: 'rbook1', id: 'presum' });
  assert.equal(parseRbookRef('binary-search'), null);
  assert.equal(parseRbookRef('rbook3:base'), null);
  assert.equal(parseRbookRef('rbook2:'), null);
  assert.equal(parseRbookRef('rbook2:a/b'), null);
});

test('前缀决定查哪本书，两本的同名 id 不会串', async () => {
  const { service, requests } = createService();

  const articles = await service.getArticles([
    'rbook1:presum',
    'rbook2:base',
    'rbook1:base',
    'rbook2:missing',
    'rbook1:presum',
  ]);

  assert.deepEqual(articles, [
    { site: 'rbook1', id: 'presum', title: '前缀和', url: 'https://rbook1.public.test/base/presum/index.html' },
    { site: 'rbook2', id: 'base', title: 'rbook2 的 base', url: 'https://rbook2.public.test/rbook2/base/' },
    { site: 'rbook1', id: 'base', title: 'rbook1 的 base', url: 'https://rbook1.public.test/base/index.html' },
  ]);

  assert.deepEqual(requests, [
    'https://rbook1.test/catalog.json',
    'http://rbook2.test/api/catalog?compact=true&includeHidden=true',
  ]);
});

test('目录按站点缓存，60 秒内不重复请求', async () => {
  const { service, requests } = createService();

  await service.getArticles(['rbook2:bit', 'rbook1:presum']);
  await service.getArticles(['rbook2:binary-search', 'rbook1:base']);

  assert.equal(requests.filter((url) => url.includes('/api/catalog')).length, 1);
  assert.equal(requests.filter((url) => url.endsWith('/catalog.json')).length, 1);
});

test('单站刷新失败时退回上一次成功的快照', async () => {
  let attempts = 0;
  const service = new RbookArticleService({
    apiBaseUrl: 'http://rbook2.test',
    publicBaseUrl: 'https://rbook2.public.test',
    rbook1CatalogUrl: 'https://rbook1.test/catalog.json',
    rbook1PublicBaseUrl: 'https://rbook1.public.test',
    cacheTtlMs: 0,
    logger: { warn() {} },
    fetchImpl: async (url) => {
      if (String(url).endsWith('/catalog.json')) return jsonResponse({ items: RBOOK1_CATALOG });
      attempts += 1;
      if (attempts === 1) return jsonResponse({ items: RBOOK2_CATALOG });
      throw new Error('RBook is unavailable');
    },
  });

  assert.equal((await service.getArticles(['rbook2:fhq-treap']))[0].title, 'FHQ Treap');
  assert.equal((await service.getArticles(['rbook2:fhq-treap']))[0].title, 'FHQ Treap');
  assert.equal(attempts, 2);
});

test('rbookLinks 保持录入顺序：id 形态查目录，url 形态用 label', async () => {
  const { service } = createService();

  const links = await service.getRbookLinks([
    { id: 'rbook1:presum', reason: '先读前缀和' },
    { url: 'https://rbook.roj.ac.cn/base/presum/index.html#sec', label: '前缀和（小程序）', reason: '逃生口形态' },
    { id: 'rbook2:missing', reason: '目录里没有，应被隐藏' },
  ]);

  assert.deepEqual(links, [
    { site: 'rbook1', id: 'presum', title: '前缀和', url: 'https://rbook1.public.test/base/presum/index.html', reason: '先读前缀和' },
    { site: null, id: null, title: '前缀和（小程序）', url: 'https://rbook.roj.ac.cn/base/presum/index.html#sec', reason: '逃生口形态' },
  ]);
});

test('只校验被引用的站点；被引用的站点不可用就报错', async () => {
  const { service, requests } = createService();

  assert.deepEqual(await service.assertSitesAvailable(['rbook2', 'rbook2']), ['rbook2']);
  assert.deepEqual(requests, ['http://rbook2.test/api/catalog?compact=true&includeHidden=true']);

  const broken = createService({ rbook1Fails: true }).service;
  await assert.rejects(
    () => broken.assertSitesAvailable(['rbook1']),
    /RBook 站点 rbook1 不可用：catalog request failed with HTTP 404/,
  );
});

function writeProblem(root, { oj, id, showAtRbook = [], rbookLinks = [] }) {
  const dir = path.join(root, oj, id);
  fs.mkdirSync(dir, { recursive: true });
  const lines = [
    '---',
    `oj: ${oj}`,
    `problem_id: ${id}`,
    'title: 测试题目',
    'description: 用于渲染测试',
    'difficulty: 普及',
    'date: 2026-11-05 10:00',
    'updated: 2026-11-05 10:00',
    'toc: true',
    'tags: []',
    'favorite: false',
    'favorite_reason: ""',
    'categories: []',
    `showAtRbook: [${showAtRbook.map((ref) => `"${ref}"`).join(', ')}]`,
  ];
  if (rbookLinks.length === 0) {
    lines.push('rbookLinks: []');
  } else {
    lines.push('rbookLinks:');
    for (const link of rbookLinks) {
      if (link.id) lines.push(`  - id: "${link.id}"`);
      if (link.url) lines.push(`  - url: "${link.url}"`, `    label: "${link.label}"`);
      lines.push(`    reason: "${link.reason}"`);
    }
  }
  lines.push('pre: []', 'common: []', 'recommend: []', 'source: https://example.com', '---', '', '正文');
  fs.writeFileSync(path.join(dir, 'index.md'), lines.join('\n'));
}

function createContentService() {
  return {
    state: 'ready',
    acquireRequest() {
      return () => {};
    },
    render() {
      return { htmlContent: '', hasStatement: false, statementHtml: '', genFileName: null };
    },
  };
}

test('题目页渲染「前置阅读」卡片，详情 API 返回解析后的 rbook_links', async () => {
  const root = fs.mkdtempSync(path.join(os.tmpdir(), 'pcs2-rbook-links-'));
  writeProblem(root, {
    oj: 'test',
    id: 'demo',
    showAtRbook: ['rbook2:binary-search'],
    rbookLinks: [
      { id: 'rbook1:presum', reason: '先读前缀和再做本题' },
      { url: 'https://rbook.roj.ac.cn/base/presum/index.html#sec', label: '前缀和（小程序）', reason: '逃生口形态' },
    ],
  });

  const problemManager = new ProblemManager({ auto_load: false, baseDir: root });
  problemManager.init();
  const { service } = createService();

  const app = await buildApp({
    logger: false,
    problemManager,
    contentService: createContentService(),
    rbookArticleService: service,
  });

  try {
    const page = await app.inject('/problems/test/demo/');
    assert.equal(page.statusCode, 200);
    assert.match(page.body, /前置阅读/);
    assert.match(
      page.body,
      /href="https:\/\/rbook1\.public\.test\/base\/presum\/index\.html" target="_blank" rel="noopener noreferrer"><span class="problem-relation-name">前缀和<\/span>/,
    );
    assert.match(page.body, /<span class="problem-relation-reason">先读前缀和再做本题<\/span>/);
    assert.match(
      page.body,
      /href="https:\/\/rbook\.roj\.ac\.cn\/base\/presum\/index\.html#sec" target="_blank" rel="noopener noreferrer"><span class="problem-relation-name">前缀和（小程序）<\/span>/,
    );
    // 反向字段照旧渲染，两者互不干扰
    assert.match(page.body, /RBook 文章:/);
    assert.match(page.body, /二分查找/);

    const detail = await app.inject('/api/problems/test/demo');
    assert.equal(detail.statusCode, 200);
    const payload = detail.json();
    assert.deepEqual(payload.showAtRbook, ['rbook2:binary-search']);
    assert.deepEqual(payload.rbook_links, [
      { site: 'rbook1', id: 'presum', title: '前缀和', url: 'https://rbook1.public.test/base/presum/index.html', reason: '先读前缀和再做本题' },
      { site: null, id: null, title: '前缀和（小程序）', url: 'https://rbook.roj.ac.cn/base/presum/index.html#sec', reason: '逃生口形态' },
    ]);
  } finally {
    await app.close();
    fs.rmSync(root, { recursive: true, force: true });
  }
});
