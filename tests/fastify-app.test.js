import test from 'node:test';
import assert from 'node:assert/strict';
import { buildApp } from '../app.js';

test('Fastify app renders the index page', async () => {
  const app = await buildApp({ logger: false });

  const response = await app.inject({
    method: 'GET',
    url: '/',
  });

  assert.equal(response.statusCode, 200);
  assert.match(response.headers['content-type'], /text\/html/);
  assert.match(response.body, /题目列表/);

  await app.close();
});

test('Fastify app returns paginated problem JSON', async () => {
  const app = await buildApp({ logger: false });

  const response = await app.inject({
    method: 'GET',
    url: '/api/problems?limit=2',
  });

  assert.equal(response.statusCode, 200);
  assert.match(response.headers['content-type'], /application\/json/);

  const body = response.json();
  assert.equal(body.data.length, 2);
  assert.equal(body.pagination.limit, 2);

  await app.close();
});

test('Fastify app returns a problem detail page', async () => {
  const app = await buildApp({ logger: false });

  const response = await app.inject({
    method: 'GET',
    url: '/problems/poj/3061',
  });

  assert.equal(response.statusCode, 200);
  assert.match(response.headers['content-type'], /text\/html/);
  assert.match(response.body, /3061/);

  await app.close();
});

test('Fastify app renders TOC and KaTeX on markdown problem pages', async () => {
  const app = await buildApp({ logger: false });

  const response = await app.inject({
    method: 'GET',
    url: '/problems/OpenJ_Bailian/1651',
  });

  assert.equal(response.statusCode, 200);
  assert.match(response.body, /table-of-contents|toc-body/);
  assert.match(response.body, /class="katex"/);
  assert.match(response.body, /class="katex-display"/);

  await app.close();
});

test('Fastify app returns JSON 404s under /api', async () => {
  const app = await buildApp({ logger: false });

  const response = await app.inject({
    method: 'GET',
    url: '/api/not-found',
  });

  assert.equal(response.statusCode, 404);
  assert.match(response.headers['content-type'], /application\/json/);
  assert.equal(response.json().error, 'Not found');

  await app.close();
});
