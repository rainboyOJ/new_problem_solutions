import test from 'node:test';
import assert from 'node:assert/strict';
import { buildApp } from '../app.js';
import ProblemManager from '../lib/problem.js';
import problemManagerInstance from '../lib/instance.js';

test('Fastify app renders the index page', async () => {
  const app = await buildApp({ logger: false });

  const response = await app.inject({
    method: 'GET',
    url: '/',
  });

  assert.equal(response.statusCode, 200);
  assert.match(response.headers['content-type'], /text\/html/);
  assert.match(response.body, /题目列表/);
  assert.match(response.body, /<table/);
  assert.match(response.body, /原题/);
  assert.match(response.body, /最后更新/);
  assert.match(response.body, /难度/);
  assert.match(response.body, /data-theme-mode/);
  assert.match(response.body, /value="auto"/);
  assert.match(response.body, /value="light"/);
  assert.match(response.body, /value="dark"/);
  assert.match(response.body, /src="\/javascripts\/theme-switcher\.js"/);
  assert.match(response.body, /href="\/problem-sets"/);
  assert.doesNotMatch(response.body, /problem-floating-toolbar/);

  await app.close();
});

test('Fastify app renders the problem set index page', async () => {
  const app = await buildApp({ logger: false });

  const response = await app.inject({
    method: 'GET',
    url: '/problem-sets',
  });

  assert.equal(response.statusCode, 200);
  assert.match(response.headers['content-type'], /text\/html/);
  assert.match(response.body, /题目单/);
  assert.match(response.body, /导入进度/);
  assert.match(response.body, /导出进度/);
  assert.match(response.body, /data-progress-file/);
  assert.match(response.body, /src="\/javascripts\/problem-set-progress-transfer\.js"/);
  assert.match(response.body, /图论入门题单/);
  assert.match(response.body, /href="\/problem-sets\/graph-basic"/);
  assert.match(response.body, /href="\/problem-sets\/csp-j-400"/);
  assert.match(response.body, /href="\/problem-sets\/csp-s-400"/);

  await app.close();
});

test('Fastify app renders the problem set detail page', async () => {
  const app = await buildApp({ logger: false });

  const response = await app.inject({
    method: 'GET',
    url: '/problem-sets/graph-basic',
  });

  assert.equal(response.statusCode, 200);
  assert.match(response.headers['content-type'], /text\/html/);
  assert.match(response.body, /图论入门题单/);
  assert.match(response.body, /data-problem-set-progress/);
  assert.match(response.body, /src="\/javascripts\/problem-set-progress\.js"/);
  assert.match(response.body, /src="\/javascripts\/theme-switcher\.js"/);
  assert.match(response.body, /data-problem-task/);
  assert.match(response.body, /data-problem-key="hdu\/1213"/);
  assert.match(response.body, /href="\/problems\/luogu\/P3387"/);
  assert.match(response.body, /problem-set-task-link/);
  assert.match(response.body, /未收录/);
  assert.match(response.body, /codeforces 20C/);

  await app.close();
});

test('Fastify app renders generated CSP problem set pages', async () => {
  const app = await buildApp({ logger: false });

  const cspj = await app.inject({
    method: 'GET',
    url: '/problem-sets/csp-j-400',
  });
  assert.equal(cspj.statusCode, 200);
  assert.match(cspj.body, /CSP-J 400 分题单/);
  assert.match(cspj.body, /luogu P1996/);
  assert.match(cspj.body, /经典知识点应用题/);

  const csps = await app.inject({
    method: 'GET',
    url: '/problem-sets/csp-s-400',
  });
  assert.equal(csps.statusCode, 200);
  assert.match(csps.body, /CSP-S 400 分题单/);
  assert.match(csps.body, /luogu P1807/);
  assert.match(csps.body, /树论/);

  const cspjPast = await app.inject({
    method: 'GET',
    url: '/problem-sets/csp-j-past',
  });
  assert.equal(cspjPast.statusCode, 200);
  assert.match(cspjPast.body, /CSP-J 历年真题题单/);
  assert.match(cspjPast.body, /前置训练/);
  assert.match(cspjPast.body, /problem-set-task-notes/);

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
  const expectedProblems = new ProblemManager().getAll().slice(0, 2);

  assert.equal(body.data.length, 2);
  assert.equal(body.pagination.limit, 2);
  assert.deepEqual(
    body.data.map((p) => `${p.oj}/${p.problem_id}`),
    expectedProblems.map((p) => `${p.oj}/${p.problem_id}`),
  );

  await app.close();
});

test('Fastify app returns a problem detail page', async () => {
  const app = await buildApp({ logger: false });

  const redirect = await app.inject({
    method: 'GET',
    url: '/problems/OpenJ_Bailian/1651',
  });

  assert.equal(redirect.statusCode, 302);
  assert.equal(redirect.headers.location, '/problems/OpenJ_Bailian/1651/');

  const response = await app.inject({
    method: 'GET',
    url: '/problems/OpenJ_Bailian/1651/',
  });

  assert.equal(response.statusCode, 200);
  assert.match(response.headers['content-type'], /text\/html/);
  assert.match(response.body, /1651/);
  assert.match(response.body, /href="https:\/\/github\.com\/RainboyOJ\/new_problem_solutions\/blob\/master\/problems\/OpenJ_Bailian\/1651\/index\.md"/);
  assert.match(response.body, />GitHub</);
  assert.match(response.body, /prism-tomorrow\.min\.css/);
  assert.match(response.body, /src="\/javascripts\/code-copy\.js"/);
  assert.match(response.body, /class="problem-floating-toolbar"/);
  assert.match(response.body, /data-problem-font="increase"/);
  assert.match(response.body, /data-scroll-top/);
  assert.match(response.body, /mermaid@11\/dist\/mermaid\.min\.js/);
  assert.match(response.body, /src="\/javascripts\/problem-toolbar\.js"/);
  assert.match(response.body, /src="\/javascripts\/problem-mermaid\.js"/);
  assert.match(response.body, /src="\/javascripts\/theme-switcher\.js"/);
  assert.match(response.body, /href="\/relations\?oj=OpenJ_Bailian&amp;pid=1651"/);
  assert.match(response.body, /难度:/);
  assert.match(response.body, /problem-difficulty-badge/);
  assert.match(response.body, />无题目</);
  assert.match(response.body, /disabled/);
  assert.doesNotMatch(response.body, /problemStatementModal/);

  await app.close();
});

test('Fastify app serves problem-local relative assets', async () => {
  const app = await buildApp({ logger: false });

  const page = await app.inject({
    method: 'GET',
    url: '/problems/luogu/P1129/',
  });

  assert.equal(page.statusCode, 200);
  assert.match(page.body, /src="\.\/one-page-explainer\.png"/);

  const image = await app.inject({
    method: 'GET',
    url: '/problems/luogu/P1129/one-page-explainer.png',
  });

  assert.equal(image.statusCode, 200);
  assert.match(image.headers['content-type'], /image\/png/);

  await app.close();
});

test('Fastify app renders problem statement modal when problem.md exists', async () => {
  const app = await buildApp({ logger: false });

  const redirect = await app.inject({
    method: 'GET',
    url: '/problems/luogu/P1968',
  });

  assert.equal(redirect.statusCode, 302);
  assert.equal(redirect.headers.location, '/problems/luogu/P1968/');

  const response = await app.inject({
    method: 'GET',
    url: '/problems/luogu/P1968/',
  });

  assert.equal(response.statusCode, 200);
  assert.match(response.headers['content-type'], /text\/html/);
  assert.match(response.body, />显示题目</);
  assert.match(response.body, /data-bs-target="#problemStatementModal"/);
  assert.match(response.body, /id="problemStatementModal"/);
  assert.match(response.body, /modal-xl/);
  assert.match(response.body, /modal-dialog-scrollable/);
  assert.match(response.body, /luogu P1968 - 题目/);
  assert.match(response.body, /题目描述/);
  assert.match(response.body, /输入输出样例/);
  assert.match(response.body, /class="katex"/);
  assert.doesNotMatch(response.body, />无题目</);

  await app.close();
});

test('Fastify app renders the relation graph page', async () => {
  const app = await buildApp({ logger: false });

  const response = await app.inject({
    method: 'GET',
    url: '/relations',
  });

  assert.equal(response.statusCode, 200);
  assert.match(response.headers['content-type'], /text\/html/);
  assert.match(response.body, /题目关系图/);
  assert.match(response.body, /id="relations-graph-root"/);
  assert.match(response.body, /href="\/relations-graph\/assets\/index\.css"/);
  assert.match(response.body, /src="\/relations-graph\/assets\/index\.js"/);
  assert.doesNotMatch(response.body, /cytoscape@3/);
  assert.doesNotMatch(response.body, /problem-relations-graph\.js/);
  assert.doesNotMatch(response.body, /theme-switcher\.js/);

  await app.close();
});

test('Fastify app returns relation graph JSON', async () => {
  const app = await buildApp({ logger: false });

  const response = await app.inject({
    method: 'GET',
    url: '/api/relations',
  });

  assert.equal(response.statusCode, 200);
  assert.match(response.headers['content-type'], /application\/json/);

  const body = response.json();
  assert.ok(Array.isArray(body.nodes));
  assert.ok(Array.isArray(body.edges));
  assert.ok(body.summary.nodes > 0);
  assert.ok(body.nodes.every((node) => typeof node.difficulty === 'string'));
  assert.ok(body.edges.some((edge) => edge.type === 'pre' || edge.type === 'common'));

  await app.close();
});

test('Fastify app returns problem description in detail API', async () => {
  const app = await buildApp({ logger: false });

  const response = await app.inject({
    method: 'GET',
    url: '/api/problems/OpenJ_Bailian/1651',
  });

  assert.equal(response.statusCode, 200);
  assert.equal(typeof response.json().description, 'string');

  await app.close();
});

test('Fastify app renders TOC and KaTeX on markdown problem pages', async () => {
  const app = await buildApp({ logger: false });

  const response = await app.inject({
    method: 'GET',
    url: '/problems/OpenJ_Bailian/1651/',
  });

  assert.equal(response.statusCode, 200);
  assert.match(response.body, /table-of-contents|toc-body/);
  assert.match(response.body, /class="katex"/);
  assert.match(response.body, /class="katex-display"/);

  await app.close();
});

test('Fastify app renders problem relation lists on detail pages', async () => {
  const app = await buildApp({ logger: false });

  const response = await app.inject({
    method: 'GET',
    url: '/problems/luogu/P3387/',
  });

  assert.equal(response.statusCode, 200);
  assert.match(response.body, /前置题目/);
  assert.match(response.body, /后置题目/);
  assert.match(response.body, /HDU 1269/);
  assert.match(response.body, /P2746/);
  assert.match(response.body, /P2272/);

  await app.close();
});

test('Fastify app renders external problem recommendations on detail pages', async () => {
  const problem = problemManagerInstance.find('OpenJ_Bailian', '1651');
  const originalRecommend = problem.recommend;
  problem.recommend = [
    {
      oj: 'leetcode',
      problem_id: '62',
      title: 'Unique Paths',
      url: 'https://leetcode.com/problems/unique-paths/',
      reason: '同样是基础网格路径计数 DP。',
      relation: 'similar',
    },
  ];

  const app = await buildApp({ logger: false });

  try {
    const response = await app.inject({
      method: 'GET',
      url: '/problems/OpenJ_Bailian/1651/',
    });

    assert.equal(response.statusCode, 200);
    assert.match(response.body, /推荐练习/);
    assert.match(response.body, /leetcode 62/);
    assert.match(response.body, /Unique Paths/);
    assert.match(response.body, /target="_blank"/);
    assert.match(response.body, /similar/);
    assert.match(response.body, /is-recommend-similar/);
  } finally {
    problem.recommend = originalRecommend;
    await app.close();
  }
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
