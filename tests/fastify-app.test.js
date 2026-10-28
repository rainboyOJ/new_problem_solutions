import test from 'node:test';
import assert from 'node:assert/strict';
import { existsSync, mkdirSync, mkdtempSync, rmSync, writeFileSync } from 'node:fs';
import { tmpdir } from 'node:os';
import { join } from 'node:path';
import http from 'node:http';
import { buildApp } from '../app.js';
import ProblemManager from '../lib/problem.js';
import problemManagerInstance from '../lib/instance.js';
import { buildTagOptions, findGenFileName } from '../routes/index.js';
import { contentGuard } from '../lib/content-http.js';

// 四个关系图版本的宿主页约定，路由、页面骨架和测试共用同一份描述。
const RELATIONS_PAGES = [
  { version: 1, label: 'v1 基础版', title: '关系图 v1 · 基础版', rootId: 'relations-graph-root', assetBase: '/relations-graph/' },
  { version: 2, label: 'v2 加速版', title: '关系图 v2 · 加速版', rootId: 'relations2-root', assetBase: '/relations2-graph/' },
  { version: 3, label: 'v3 立体版', title: '关系图 v3 · 立体版', rootId: 'relations3-root', assetBase: '/relations3-graph/' },
  { version: 4, label: 'v4 全景版', title: '关系图 v4 · 全景版', rootId: 'relations4-root', assetBase: '/relations4-graph/' },
];

test('findGenFileName prefers gen.py and falls back to gen.cpp', () => {
  const dir = mkdtempSync(join(tmpdir(), 'rbook-gen-file-'));

  try {
    assert.equal(findGenFileName(dir), null);

    writeFileSync(join(dir, 'gen.cpp'), 'int main() { return 0; }\n');
    assert.equal(findGenFileName(dir), 'gen.cpp');

    writeFileSync(join(dir, 'gen.py'), '#!/usr/bin/env python3\n');
    assert.equal(findGenFileName(dir), 'gen.py');
  } finally {
    rmSync(dir, { recursive: true, force: true });
  }
});

test('buildTagOptions counts each problem once and sorts by frequency', () => {
  const options = buildTagOptions([
    { tags: ['dp', 'dp', '动态规划'] },
    { tags: ['dp', '搜索'] },
    { tags: ['搜索', '图论'] },
    { tags: null },
  ]);

  assert.deepEqual(options, [
    { name: '搜索', count: 2 },
    { name: 'dp', count: 2 },
    { name: '动态规划', count: 1 },
    { name: '图论', count: 1 },
  ]);
});

test('Fastify app serves only local Prism assets under the vendor prefix', async () => {
  const app = await buildApp({ logger: false });

  try {
    const assets = [
      ['/vendor/prism/components/prism-core.min.js', /javascript/],
      ['/vendor/prism/components/prism-cpp.min.js', /javascript/],
      ['/vendor/prism/plugins/autoloader/prism-autoloader.min.js', /javascript/],
      ['/vendor/prism/themes/prism-tomorrow.min.css', /text\/css/],
    ];

    for (const [url, contentType] of assets) {
      const response = await app.inject({ method: 'GET', url });
      assert.equal(response.statusCode, 200, url);
      assert.match(response.headers['content-type'], contentType, url);
    }

    const traversal = await app.inject({
      method: 'GET',
      url: '/vendor/prism/..%2F..%2Fpackage.json',
    });
    assert.notEqual(traversal.statusCode, 200);
  } finally {
    await app.close();
  }
});

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
  // 列顺序：OJ / 题号 必须排在标题前面。
  const headerCells = [...response.body.matchAll(/<th[^>]*>([^<]*)<\/th>/g)].map((m) => m[1].trim());
  assert.deepEqual(headerCells, [
    'OJ',
    '题号',
    '标题',
    '标签',
    '难度',
    '最后更新',
    '解析',
  ]);
  // OJ 单元格要么是本地图标，要么是无图标时的首字徽章。
  assert.match(response.body, /class="oj-icon" src="\/icons\/oj\//);
  assert.match(response.body, /class="index-oj__name"/);
  assert.match(response.body, /href="\/\?oj=/);
  // 「解析」列指向本站题解，「题号」指向原题，两者不能搞反。
  assert.match(response.body, /class="index-analysis-link" href="\/problems\//);
  assert.doesNotMatch(
    response.body,
    /class="index-analysis-link"[^>]*target="_blank"/,
    '解析入口不应该新标签页打开',
  );
  assert.match(
    response.body,
    /class="index-code-link" href="https?:\/\/[^"]+" target="_blank" rel="noopener noreferrer"/,
  );
  assert.match(response.body, /class="analysis-icon"/);
  // 旧的外链「打开」按钮已经不存在了。
  assert.doesNotMatch(response.body, />打开<\/a>/);
  assert.match(response.body, /data-theme-mode/);
  assert.match(response.body, /value="auto"/);
  assert.match(response.body, /value="light"/);
  assert.match(response.body, /value="dark"/);
  assert.match(response.body, /src="\/javascripts\/theme-switcher\.js"/);
  assert.match(response.body, /id="tagFilterModal"/);
  assert.match(response.body, /id="tagFilterSearch"/);
  assert.match(response.body, /src="\/javascripts\/tag-filter-modal\.js"/);
  assert.doesNotMatch(response.body, /<select[^>]+name="tag"/);
  assert.match(response.body, /data-tag-list/);
  assert.match(response.body, /href="\/problem-sets"/);
  assert.doesNotMatch(response.body, /problem-floating-toolbar/);
  assert.match(response.body, /显示第 1-60 条，共 \d+ 题/);
  assert.match(response.body, /name="page"/);
  assert.match(response.body, /aria-current="page"/);
  assert.doesNotMatch(response.body, /href="#"/);
  assert.ok((response.body.match(/class="page-item"/g) || []).length < 15);

  // OJ 下拉框显示好看的名字，而不是 roj / noi_openjudge 这类原始值。
  const ojOptions = [...response.body.matchAll(/<option value="([^"]*)"[^>]*>([^<]*)<\/option>/g)]
    .map((m) => ({ value: m[1], label: m[2].trim() }))
    .filter((option) => option.value !== '');
  assert.ok(ojOptions.length > 0, 'OJ 下拉框应该有选项');
  assert.ok(
    ojOptions.some((option) => option.label === 'RainboyOJ') &&
      ojOptions.some((option) => option.label === '洛谷'),
    'OJ 下拉框应该用展示名',
  );
  assert.doesNotMatch(response.body, /<option value="[^"]*"[^>]*>roj</);
  // codeforces 与 CodeForces 在数据里并存，筛选下拉里必须只出现一项。
  const codeforcesOptions = ojOptions.filter(
    (option) => option.label.toLowerCase() === 'codeforces',
  );
  assert.equal(codeforcesOptions.length, 1, 'Codeforces 不应重复出现');

  await app.close();
});

test('index page normalizes OJ spellings when filtering', async () => {
  const app = await buildApp({ logger: false });

  // 数据里 codeforces(8 道) 与 CodeForces(2 道) 两种写法共存，两者必须命中同一批题。
  const [lower, mixed] = await Promise.all([
    app.inject({ method: 'GET', url: '/?oj=codeforces' }),
    app.inject({ method: 'GET', url: '/?oj=CodeForces' }),
  ]);
  assert.equal(lower.statusCode, 200);
  assert.equal(mixed.statusCode, 200);

  const counts = [lower.body, mixed.body].map((body) => {
    const match = body.match(/共 (\d+) 题/);
    return match ? Number(match[1]) : null;
  });
  assert.deepEqual(counts[0], counts[1], '两种写法应该筛出同样多的题目');
  assert.ok(counts[0] > 0, 'Codeforces 筛选不应为空');

  // 选中态要回填到归并后的那一项。
  for (const body of [lower.body, mixed.body]) {
    assert.match(body, /<option value="codeforces" selected>Codeforces<\/option>/);
  }

  await app.close();
});

test('Fastify app keeps pagination filters and clamps invalid pages', async () => {
  const app = await buildApp({ logger: false });

  try {
    const response = await app.inject({
      method: 'GET',
      url: '/?page=999',
    });

    assert.equal(response.statusCode, 200);
    assert.match(response.body, /aria-current="page"/);
    assert.match(response.body, /name="page"[^>]+value="\d+"/);

    const filtered = await app.inject({
      method: 'GET',
      url: '/?page=999&oj=luogu&tag=dp',
    });

    assert.equal(filtered.statusCode, 200);
    assert.match(filtered.body, /显示第 1-\d+ 条，共 \d+ 题/);
    assert.match(filtered.body, /name="oj" value="luogu"/);
    assert.match(filtered.body, /name="tag" value="dp"/);

    const selected = await app.inject({
      method: 'GET',
      url: '/?tag=dp',
    });
    assert.equal(selected.statusCode, 200);
    assert.match(selected.body, /标签：dp/);
    assert.match(selected.body, /data-tag-name="dp"[^>]+aria-selected="true"/);

    const luoguTotal = new ProblemManager().getAll().filter((problem) => problem.oj === 'luogu').length;
    const scoped = await app.inject({
      method: 'GET',
      url: '/?oj=luogu',
    });
    assert.equal(scoped.statusCode, 200);
    assert.match(
      scoped.body,
      new RegExp(`全部标签</span><span class="tag-filter-option__meta"><span class="tag-filter-option__count">${luoguTotal}</span>`),
    );
  } finally {
    await app.close();
  }
});

test('Fastify app displays and filters favorite problems', async () => {
  const problem = problemManagerInstance.find('OpenJ_Bailian', '1651');
  assert.ok(problem);
  const originalFavorite = problem.favorite;
  const originalReason = problem.favorite_reason;
  problem.favorite = true;
  problem.favorite_reason = '状态建模 <script>alert(1)</script>';

  const app = await buildApp({ logger: false });
  try {
    const list = await app.inject({
      method: 'GET',
      url: `/?favorite=true&q=${encodeURIComponent('状态建模')}`,
    });

    assert.equal(list.statusCode, 200);
    assert.match(list.body, /只看启发题/);
    assert.match(list.body, /共 1 道启发题/);
    assert.match(list.body, /value="true"/);
    assert.match(list.body, /启发题：状态建模 &lt;script&gt;alert\(1\)&lt;\/script&gt;/);
    assert.doesNotMatch(list.body, /<script>alert\(1\)<\/script>/);

    const detail = await app.inject({
      method: 'GET',
      url: '/problems/OpenJ_Bailian/1651/',
    });

    assert.equal(detail.statusCode, 200);
    assert.match(detail.body, /class="problem-favorite-note"/);
    assert.match(detail.body, /启发题/);
    assert.match(detail.body, /启发记录：<\/strong> 状态建模 &lt;script&gt;alert\(1\)&lt;\/script&gt;/);
    assert.doesNotMatch(detail.body, /<script>alert\(1\)<\/script>/);

    const api = await app.inject({
      method: 'GET',
      url: `/api/problems?favorite=true&search=${encodeURIComponent('状态建模')}`,
    });

    assert.equal(api.statusCode, 200);
    const payload = api.json();
    assert.equal(payload.pagination.total, 1);
    assert.equal(payload.data[0].favorite, true);
    assert.equal(payload.data[0].favorite_reason, '状态建模 <script>alert(1)</script>');

    const combined = await app.inject({
      method: 'GET',
      url: '/api/problems?favorite=true&oj=OpenJ_Bailian&tag=区间dp',
    });

    assert.equal(combined.statusCode, 200);
    assert.equal(combined.json().pagination.total, 1);
  } finally {
    await app.close();
    problem.favorite = originalFavorite;
    problem.favorite_reason = originalReason;
  }
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
  assert.match(response.body, /src="\/javascripts\/problem-sets-index\.js"/);
  assert.match(response.body, /data-problem-set-directory/);
  assert.match(response.body, /data-problem-set-search/);
  assert.match(response.body, /index-table-wrap/);
  assert.match(response.body, /index-table problem-set-directory__table/);
  assert.match(response.body, /problem-set-directory__table/);
  assert.match(response.body, /data-problem-set-row/);
  assert.match(response.body, /data-problem-set-task-count="38"/);
  assert.match(response.body, /data-problem-set-task-count="28"/);
  assert.match(response.body, /0 \/ 38/);
  assert.match(response.body, /0 \/ 28/);
  assert.doesNotMatch(response.body, /problem-set-card/);
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
  assert.match(response.body, /src="\/vendor\/prism\/components\/prism-core\.min\.js"/);
  assert.match(response.body, /src="\/javascripts\/code-highlight\.js"/);
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

test('Fastify app connects LeetCode Hot 100 to the local two-sum solution', async () => {
  const app = await buildApp({ logger: false });

  try {
    const problemSet = await app.inject({
      method: 'GET',
      url: '/problem-sets/leetcode-hot-100',
    });
    assert.equal(problemSet.statusCode, 200);
    assert.match(
      problemSet.body,
      /data-problem-key="leetcodecn\/two-sum" data-problem-exists="1"/,
    );
    assert.match(problemSet.body, /href="\/problems\/leetcodecn\/two-sum"/);
    assert.match(problemSet.body, /href="https:\/\/leetcode\.cn\/problems\/two-sum\/"/);

    const problem = await app.inject({
      method: 'GET',
      url: '/problems/leetcodecn/two-sum/',
    });
    assert.equal(problem.statusCode, 200);
    assert.match(problem.body, /两数之和/);
    assert.match(problem.body, /language-python/);
    assert.match(problem.body, /index_by_value/);
  } finally {
    await app.close();
  }
});

test('Fastify app renders the curated basic algorithm problem sets', async () => {
  const app = await buildApp({ logger: false });
  const expected = {
    'search-basic': ['搜索入门题单', 20],
    'cpp-stl-basic': ['C++ STL 竞赛入门题单', 30],
    'data-structure-basic': ['基础数据结构题单', 20],
    'binary-two-pointers-basic': ['二分与双指针入门题单', 19],
    'graph-basic': ['图论入门题单', 27],
    'string-basic': ['字符串基础题单', 33],
    'tree-basic': ['树上基础题单', 16],
  };

  try {
    for (const [slug, [title, count]] of Object.entries(expected)) {
      const response = await app.inject({ method: 'GET', url: `/problem-sets/${slug}` });
      assert.equal(response.statusCode, 200, slug);
      assert.ok(response.body.includes(title), title);
      assert.equal((response.body.match(/data-problem-task/g) || []).length, count, slug);
    }
  } finally {
    await app.close();
  }
});

test('Fastify app renders the Luogu official training problem set', async () => {
  const app = await buildApp({ logger: false });

  const response = await app.inject({
    method: 'GET',
    url: '/problem-sets/luogu-official-basic-training',
  });

  assert.equal(response.statusCode, 200);
  assert.match(response.body, /洛谷官方入门与基础算法题单/);
  assert.equal((response.body.match(/data-problem-task/g) || []).length, 271);
  assert.equal((response.body.match(/data-problem-key="luogu\/P1036"/g) || []).length, 3);
  assert.match(response.body, /href="https:\/\/www\.luogu\.com\.cn\/training\/100"/);
  assert.match(response.body, /href="https:\/\/www\.luogu\.com\.cn\/problem\/B2002"/);
  assert.match(response.body, /src="\/javascripts\/problem-set-progress\.js"/);

  await app.close();
});

test('Fastify app renders the Luogu trial ground problem set', async () => {
  const app = await buildApp({ logger: false });

  const response = await app.inject({
    method: 'GET',
    url: '/problem-sets/luogu-trial-ground',
  });

  assert.equal(response.statusCode, 200);
  assert.match(response.body, /洛谷-试炼场/);
  assert.match(response.body, /原题单作者：@CLCK/);
  assert.equal((response.body.match(/data-problem-task/g) || []).length, 38);
  assert.equal((response.body.match(/data-problem-exists="0"/g) || []).length, 4);
  assert.match(response.body, /href="https:\/\/www\.luogu\.com\.cn\/problem\/P1567"/);

  await app.close();
});

test('Fastify app renders the Luogu popular trial ground problem set', async () => {
  const app = await buildApp({ logger: false });

  const response = await app.inject({
    method: 'GET',
    url: '/problem-sets/luogu-trial-ground-popular',
  });

  assert.equal(response.statusCode, 200);
  assert.match(response.body, /洛谷-试炼场：普及练习场/);
  assert.match(response.body, /href="\/problem-sets\/luogu-trial-ground"/);
  assert.equal((response.body.match(/data-problem-task/g) || []).length, 128);
  assert.equal((response.body.match(/data-problem-key="luogu\/P1031"/g) || []).length, 3);
  assert.match(response.body, /href="https:\/\/www\.luogu\.com\.cn\/problem\/P1031"/);
  assert.match(response.body, /洛谷原题/);

  await app.close();
});

test('Fastify app renders the Luogu advanced trial ground problem set', async () => {
  const app = await buildApp({ logger: false });

  const response = await app.inject({
    method: 'GET',
    url: '/problem-sets/luogu-trial-ground-advanced',
  });

  assert.equal(response.statusCode, 200);
  assert.match(response.body, /洛谷-试炼场：提高历练地/);
  assert.match(response.body, /href="\/problem-sets\/luogu-trial-ground-popular"/);
  assert.equal((response.body.match(/data-problem-task/g) || []).length, 108);
  // P1439 目录在 a87eb79d 统一加大写 P 前缀后就开始被算作“已有题解”，
  // 1aca9517 补齐它的正文后，未解题数由 54 降为 53；
  // 并入 newROJ-PY 的题解后，P1514 也有了解题正文，未解题数再由 53 降为 52。
  // 2026-10-24：P1070/P1220（本批）与 P1273/P1613（t490 批）补齐题解后，未解题数由 52 降为 48。
  assert.equal((response.body.match(/data-problem-exists="0"/g) || []).length, 48);
  assert.match(response.body, /href="https:\/\/www\.luogu\.com\.cn\/problem\/P1378"/);
  assert.match(response.body, /洛谷原题/);

  await app.close();
});

test('Fastify app renders the Luogu provincial trial ground problem set', async () => {
  const app = await buildApp({ logger: false });

  const response = await app.inject({
    method: 'GET',
    url: '/problem-sets/luogu-trial-ground-provincial',
  });

  assert.equal(response.statusCode, 200);
  assert.match(response.body, /洛谷-试炼场：省选斗兽场\/NOI 神殿/);
  assert.match(response.body, /href="\/problem-sets\/luogu-trial-ground-advanced"/);
  assert.equal((response.body.match(/data-problem-task/g) || []).length, 128);
  assert.equal((response.body.match(/data-problem-key="luogu\/P3157"/g) || []).length, 2);
  // 2026-10-24：P1273（t490 批）补齐题解后，未解题数由 98 降为 97。
  assert.equal((response.body.match(/data-problem-exists="0"/g) || []).length, 97);
  assert.match(response.body, /href="https:\/\/www\.luogu\.com\.cn\/problem\/P2393"/);

  await app.close();
});

test('Fastify app renders the Luogu official advanced training problem set', async () => {
  const app = await buildApp({ logger: false });

  const response = await app.inject({
    method: 'GET',
    url: '/problem-sets/luogu-official-advanced-training',
  });

  assert.equal(response.statusCode, 200);
  assert.match(response.body, /洛谷官方深入浅出进阶篇题单/);
  assert.equal((response.body.match(/data-problem-task/g) || []).length, 368);
  assert.equal((response.body.match(/data-problem-key="luogu\/P1115"/g) || []).length, 3);
  assert.match(response.body, /href="https:\/\/www\.luogu\.com\.cn\/training\/200"/);
  assert.match(response.body, /href="https:\/\/www\.luogu\.com\.cn\/problem\/P8218"/);
  assert.match(response.body, /src="\/javascripts\/problem-set-progress\.js"/);

  await app.close();
});

test('Fastify app renders the VJudge advanced programming problem set', async () => {
  const app = await buildApp({ logger: false });

  const response = await app.inject({
    method: 'GET',
    url: '/problem-sets/vjudge-shenru-qianchu-jinjie',
  });

  assert.equal(response.statusCode, 200);
  assert.match(response.body, /VJudge《深入浅出程序设计竞赛 进阶篇》题单/);
  assert.equal((response.body.match(/data-problem-task/g) || []).length, 367);
  assert.match(response.body, /data-problem-key="luogu\/P1102"/);
  assert.match(response.body, /data-problem-key="codeforces\/525E"/);
  assert.match(response.body, /data-problem-key="atcoder\/agc023_e"/);
  assert.match(response.body, /data-problem-key="uva\/11572"/);
  assert.match(response.body, /data-problem-key="vjudge\/Gym-101002H"/);
  assert.match(response.body, /href="https:\/\/vjudge\.net\/article\/3470"/);
  assert.match(response.body, /href="https:\/\/www\.luogu\.com\.cn\/problem\/P1102"/);
  assert.match(response.body, /href="https:\/\/vjudge\.net\/problem\/CodeForces-525E"/);
  assert.doesNotMatch(response.body, /vjudge\.net\/problem\/%E6%B4%9B%E8%B0%B7-/);

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

test('Fastify app keeps inline problem set practice notes', async () => {
  const app = await buildApp({ logger: false });

  const response = await app.inject({
    method: 'GET',
    url: '/problem-sets/haskell-practice',
  });

  assert.equal(response.statusCode, 200);
  assert.match(response.body, /Haskell 语法特性 OJ 入门题单/);
  assert.match(response.body, /problem-set-task-notes/);
  assert.match(response.body, /阶段 2：输入解析、&lt;\$&gt;、函数组合与类型标注/);
  assert.match(response.body, /练习点：<code>getLine<\/code> 读取一行字符串/);
  assert.match(response.body, /练习点：<code>zip \[1\.\.\]<\/code> 保留原始编号/);

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
  assert.match(response.body, /href="\/vendor\/prism\/themes\/prism-tomorrow\.min\.css"/);
  assert.doesNotMatch(response.body, /cdnjs\.cloudflare\.com\/ajax\/libs\/prism/);
  assert.match(response.body, /href="https:\/\/github\.com\/RainboyOJ\/new_problem_solutions\/blob\/master\/problems\/OpenJ_Bailian\/1651\/index\.md"/);
  assert.match(response.body, /class="btn btn-outline-dark btn-sm problem-github-link problem-source-link"/);
  assert.match(response.body, />GitHub</);
  assert.match(
    response.body,
    /problem-github-link problem-source-link[^>]*>GitHub<\/a><button class="btn btn-outline-dark btn-sm problem-source-link problem-md-raw-button"/,
  );
  assert.match(response.body, /data-md-raw-trigger[^>]*data-md-raw-url="\/api\/problems\/OpenJ_Bailian\/1651"[^>]*hidden/);
  assert.match(response.body, /id="mdRawModal"[^>]*data-md-raw-modal/);
  assert.match(response.body, /class="modal-dialog modal-xl modal-dialog-scrollable modal-fullscreen-sm-down"/);
  assert.match(response.body, /id="mdRawModalLabel"[^>]*>Markdown Raw<\/h2>/);
  assert.match(response.body, /data-md-raw-copy[^>]*disabled[^>]*>复制全部<\/button>/);
  assert.match(response.body, /data-bs-dismiss="modal" aria-label="关闭"/);
  assert.match(response.body, /data-md-raw-status[^>]*role="status"[^>]*aria-live="polite"/);
  assert.match(response.body, /data-md-raw-retry[^>]*hidden[^>]*>重试<\/button>/);
  assert.match(response.body, /data-md-raw-line-numbers[^>]*aria-hidden="true"/);
  assert.match(response.body, /<code class="language-markdown" data-md-raw-code><\/code>/);
  assert.doesNotMatch(response.body, /data-md-raw-code>---/);
  assert.match(response.body, /prism-tomorrow\.min\.css/);
  assert.match(response.body, /src="\/javascripts\/code-copy\.js"/);
  assert.match(response.body, /src="\/javascripts\/math-copy\.js"/);
  assert.match(response.body, /src="\/vendor\/prism\/components\/prism-core\.min\.js"/);
  assert.match(response.body, /src="\/vendor\/prism\/plugins\/autoloader\/prism-autoloader\.min\.js"/);
  assert.match(response.body, /src="\/javascripts\/code-highlight\.js"/);
  assert.match(response.body, /src="\/javascripts\/md-raw-modal\.js"/);
  assert.ok(
    response.body.indexOf('/javascripts/code-copy.js')
      < response.body.indexOf('/javascripts/math-copy.js'),
  );
  assert.ok(
    response.body.indexOf('/javascripts/code-highlight.js')
      < response.body.indexOf('/javascripts/md-raw-modal.js'),
  );
  assert.match(response.body, /class="problem-floating-toolbar"/);
  assert.match(response.body, /data-problem-font="increase"/);
  assert.match(response.body, /data-scroll-top/);
  assert.match(response.body, /mermaid@11\/dist\/mermaid\.min\.js/);
  assert.match(response.body, /src="\/javascripts\/problem-toolbar\.js"/);
  assert.match(response.body, /src="\/javascripts\/problem-mermaid\.js"/);
  assert.match(response.body, /src="\/javascripts\/theme-switcher\.js"/);
  assert.match(response.body, /href="\/relations\/3\?oj=OpenJ_Bailian&amp;pid=1651"/);
  assert.match(response.body, /难度:/);
  assert.match(response.body, /problem-difficulty-badge/);
  assert.match(response.body, />无题目</);
  assert.match(response.body, /disabled/);
  assert.doesNotMatch(response.body, /problemStatementModal/);

  const stylesheet = await app.inject({
    method: 'GET',
    url: '/stylesheets/style.css',
  });

  assert.equal(stylesheet.statusCode, 200);
  assert.match(stylesheet.body, /\[data-bs-theme="dark"\] \.problem-github-link/);
  assert.match(stylesheet.body, /\.md-raw-code-viewport/);
  assert.match(stylesheet.body, /white-space: pre/);
  assert.match(
    stylesheet.body,
    /\.md-raw-code-viewport[^{]*\{[^}]*align-items: flex-start;/s,
  );
  assert.match(
    stylesheet.body,
    /\.md-raw-line-numbers,\s*\.md-raw-code-viewport code[^{]*\{[^}]*min-height: 100%;/s,
  );
  assert.match(
    stylesheet.body,
    /pre\.md-raw-code-viewport[^{]*\{[^}]*padding: 0;/s,
  );
  assert.match(
    stylesheet.body,
    /\.md-raw-code-viewport code\[class\*="language-"\][^{]*\{[^}]*color: #f8fafc;/s,
  );
  assert.match(
    stylesheet.body,
    /@media \(max-width: 767\.98px\)[\s\S]*\.md-raw-header-actions \.btn[^}]*min-height: 44px;/,
  );
  assert.match(
    stylesheet.body,
    /@media \(max-width: 767\.98px\)[\s\S]*\.md-raw-header-actions \.btn-close[^}]*min-width: 44px;/,
  );
  assert.match(stylesheet.body, /--bs-btn-color: #f8f9fa/);
  assert.match(stylesheet.body, /--bs-btn-focus-shadow-rgb: 248, 249, 250/);
  assert.match(
    stylesheet.body,
    /\[data-bs-theme="dark"\] \.problem-source-link[^}]*color: #f8f9fa;/s,
  );
  assert.match(
    stylesheet.body,
    /\[data-bs-theme="dark"\] \.problem-source-link[^}]*border-color: #f8f9fa;/s,
  );

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

test('Fastify app renders random data generator modal when gen file exists', async () => {
  const app = await buildApp({ logger: false });

  const pageWithGen = await app.inject({
    method: 'GET',
    url: '/problems/luogu/P1001/',
  });

  assert.equal(pageWithGen.statusCode, 200);
  assert.match(pageWithGen.body, />随机数据</);
  assert.match(pageWithGen.body, /data-gen-file="gen\.py"/);
  assert.match(pageWithGen.body, /title="查看 gen\.py"/);
  assert.match(pageWithGen.body, /id="genModal"/);
  assert.match(pageWithGen.body, /id="genCodeContent"/);
  assert.match(pageWithGen.body, /id="genDownloadBtn"/);
  assert.match(pageWithGen.body, /src="\/javascripts\/gen-modal\.js"/);

  const genFile = await app.inject({
    method: 'GET',
    url: '/problems/luogu/P1001/gen.py',
  });

  assert.equal(genFile.statusCode, 200);
  assert.match(genFile.body, /^#!\/usr\/bin\/env python3/);

  const pageWithoutGen = await app.inject({
    method: 'GET',
    url: '/problems/luogu/P1111/',
  });

  assert.equal(pageWithoutGen.statusCode, 200);
  assert.match(pageWithoutGen.body, />随机数据</);
  assert.match(pageWithoutGen.body, /本题暂无 gen\.py\/gen\.cpp/);
  assert.match(pageWithoutGen.body, /disabled/);
  assert.doesNotMatch(pageWithoutGen.body, /id="genModal"/);

  await app.close();
});

test('Fastify app resolves numeric Luogu aliases to canonical routes and API ids', async () => {
  const app = await buildApp({ logger: false });

  const redirect = await app.inject({
    method: 'GET',
    url: '/problems/luogu/1001',
  });
  assert.equal(redirect.statusCode, 302);
  assert.equal(redirect.headers.location, '/problems/luogu/P1001/');

  const api = await app.inject({
    method: 'GET',
    url: '/api/problems/luogu/1001',
  });
  assert.equal(api.statusCode, 200);
  assert.equal(api.json().problem_id, 'P1001');
  assert.equal(api.json().url, '/problems/luogu/P1001');

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

test('four relation graph versions render their own host pages', async () => {
  const app = await buildApp({ logger: false });
  try {
    for (const page of RELATIONS_PAGES) {
      for (const url of [`/relations/${page.version}`, `/relations/${page.version}/`]) {
        const response = await app.inject({ url });
        assert.equal(response.statusCode, 200, url);
        assert.match(response.headers['content-type'], /text\/html/, url);
        assert.ok(response.body.includes(page.title), url);
        assert.ok(response.body.includes(`id="${page.rootId}"`), url);
        assert.ok(response.body.includes(`href="${page.assetBase}assets/index.css"`), url);
        assert.ok(response.body.includes(`src="${page.assetBase}assets/index.js"`), url);
      }
    }
  } finally { await app.close(); }
});

test('navigation groups every relation graph under one dropdown', async () => {
  const app = await buildApp({ logger: false });
  try {
    const home = await app.inject({ url: '/' });
    assert.equal(home.statusCode, 200);
    assert.ok(home.body.includes('题目关联'));
    assert.match(home.body, /data-bs-toggle="dropdown"/);
    for (const page of RELATIONS_PAGES) {
      assert.ok(home.body.includes(`href="/relations/${page.version}"`), page.label);
      assert.ok(home.body.includes(page.label), page.label);
    }
    assert.doesNotMatch(home.body, /href="\/relations">关系图/);
    assert.doesNotMatch(home.body, /href="\/relations4">关系全景/);
    assert.doesNotMatch(home.body, /href="\/relations3"/);

    const current = await app.inject({ url: '/relations/2' });
    assert.match(
      current.body,
      /<a[^>]*href="\/relations\/2"[^>]*aria-current="page"/,
    );
    assert.match(current.body, /<button[^>]*class="nav-link dropdown-toggle active"/);
  } finally { await app.close(); }
});

test('legacy relation URLs redirect to versioned pages with deep-link state intact', async () => {
  const app = await buildApp({ logger: false });
  try {
    const legacy = [
      ['/relations', '/relations/3'],
      ['/relations/', '/relations/3'],
      ['/relations3', '/relations/3'],
      ['/relations3/', '/relations/3'],
      ['/relations4', '/relations/4'],
      ['/relations4/', '/relations/4'],
    ];
    const queries = ['', '?oj=luogu&pid=P1968&edges=pre,common', '?oj=HDU&pid=A%2FB%20%26%20%E4%B8%AD%E6%96%87&edges=none&isolated=1'];
    for (const [url, target] of legacy) {
      for (const query of queries) {
        const response = await app.inject({ url: `${url}${query}` });
        assert.equal(response.statusCode, 308, url);
        assert.equal(response.headers.location, `${target}${query}`, url);
      }
    }
    for (const target of ['/relations/3?oj=luogu&pid=P1968', '/relations/4?oj=luogu&pid=P1725&view=layers']) {
      const canonical = await app.inject({ url: target });
      assert.equal(canonical.statusCode, 200, target);
    }
  } finally {
    await app.close();
  }
});

test('independent canvas relation page serves its entry, style and layout worker', async () => {
  const app = await buildApp({ logger: false });
  try {
    const response = await app.inject({ url: '/relations/4?oj=luogu&pid=P1725&view=layers' });
    assert.equal(response.statusCode, 200);
    assert.match(response.body, /id="relations4-root"/);
    assert.match(response.body, /href="\/relations4-graph\/assets\/index\.css"/);
    assert.match(response.body, /src="\/relations4-graph\/assets\/index\.js"/);
    for (const [url, type] of [['/relations4-graph/assets/index.js', /javascript/], ['/relations4-graph/assets/index.css', /css/]]) {
      const asset = await app.inject({ url });
      assert.equal(asset.statusCode, 200);
      assert.match(asset.headers['content-type'], type);
      if (url.endsWith('.js')) {
        const workerPath = asset.body.match(/\/relations4-graph\/assets\/layout\.worker-[\w-]+\.js/);
        assert.ok(workerPath, 'bundle must reference its independently served worker');
        const worker = await app.inject({ url: workerPath[0] });
        assert.equal(worker.statusCode, 200);
        assert.match(worker.headers['content-type'], /javascript/);
      }
    }
  } finally { await app.close(); }
});

test('restored v1 and v2 graph bundles are served again', async () => {
  const app = await buildApp({ logger: false });
  try {
    for (const page of RELATIONS_PAGES.slice(0, 2)) {
      for (const [url, type] of [
        [`${page.assetBase}assets/index.js`, /javascript/],
        [`${page.assetBase}assets/index.css`, /css/],
        [`${page.assetBase}index.html`, /text\/html/],
      ]) {
        const asset = await app.inject({ url });
        assert.equal(asset.statusCode, 200, url);
        assert.match(asset.headers['content-type'], type, url);
      }
    }
  } finally { await app.close(); }
});

test('canonical 3D graph serves real assets and links the problem page to it', async () => {
  const app = await buildApp({ logger: false });
  try {
    const response = await app.inject({ url: '/relations/3?oj=luogu&pid=P1968&edges=pre' });
    assert.equal(response.statusCode, 200);
    assert.match(response.body, /id="relations3-root"/);
    assert.match(response.body, /src="\/relations3-graph\/assets\/index\.js"/);
    const problem = await app.inject({ url: '/problems/luogu/P1968/' });
    assert.match(problem.body, /href="\/relations\/3\?oj=luogu&amp;pid=P1968"/);
    for (const [url, type] of [['/relations3-graph/assets/index.js', /javascript/], ['/relations3-graph/assets/index.css', /css/]]) {
      const asset = await app.inject({ url });
      assert.equal(asset.statusCode, 200);
      assert.match(asset.headers['content-type'], type);
      assert.ok(asset.body.length > 100);
    }
  } finally { await app.close(); }
});

test('Fastify app serves the problem-list knowledge graph under one canonical URL', async () => {
  const app = await buildApp({ logger: false });

  try {
    for (const url of ['/problem-list', '/problem-list/']) {
      const response = await app.inject({ url });
      assert.equal(response.statusCode, 200, url);
      assert.match(response.headers['content-type'], /text\/html/, url);
      assert.match(response.body, /信息学奥赛题单 · 知识点图谱/, url);
      assert.match(response.body, /id="sidebar"/, url);
      // 页面自包含：不得引入任何外部脚本或样式。
      assert.doesNotMatch(response.body, /<(?:script|link)[^>]+(?:src|href)="(?:https?:)?\/\//, url);
    }

    for (const url of ['/problem-list-graph', '/problem-list-graph/', '/problem-list-graph/index.html']) {
      const response = await app.inject({ url });
      assert.equal(response.statusCode, 308, url);
      assert.equal(response.headers.location, '/problem-list', url);
    }

    const data = await app.inject({ url: '/problem-list-graph/problems.json' });
    assert.equal(data.statusCode, 200);
    assert.match(data.headers['content-type'], /application\/json/);
    const parsed = JSON.parse(data.body);
    assert.equal(parsed.total, parsed.problems.length);
    assert.ok(parsed.categories.length > 0);
    const hosts = new Set(parsed.problems.map((problem) => new URL(problem.url).host));
    assert.deepEqual([...hosts].sort(), ['atcoder.jp', 'codeforces.com', 'www.luogu.com.cn']);
  } finally {
    await app.close();
  }
});

test('problem-list knowledge graph does not depend on content availability', async () => {
  const app = await buildApp({ logger: false, initializeContent: false, contentService: { state: 'unavailable', acquireRequest() { return null; } } });
  try {
    const response = await app.inject({ url: '/problem-list' });
    assert.equal(response.statusCode, 200);
    assert.match(response.body, /知识点图谱/);
  } finally { await app.close(); }
});

test('every relation graph page respects content availability guard', async () => {
  const app = await buildApp({ logger: false, initializeContent: false, contentService: { state: 'unavailable', acquireRequest() { return null; } } });
  try {
    for (const page of RELATIONS_PAGES) {
      const response = await app.inject({ url: `/relations/${page.version}` });
      assert.equal(response.statusCode, 503, page.label);
      assert.equal(response.headers['retry-after'], '5');
      assert.match(response.body, /内容更新失败/);
    }
    // 旧地址的重定向不读内容快照，内容不可用时也要照常跳转。
    const legacy = await app.inject({ url: '/relations' });
    assert.equal(legacy.statusCode, 308);
    assert.equal(legacy.headers.location, '/relations/3');
  } finally { await app.close(); }
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
  const body = response.json();
  assert.equal(typeof body.description, 'string');
  assert.equal(typeof body.md_content, 'string');
  assert.match(body.md_content, /```cpp/);
  assert.match(body.html_content, /class="language-cpp/);
  assert.match(body.html_content, /#include &lt;iostream&gt;/);
  assert.doesNotMatch(body.html_content, /<span class="token/);

  await app.close();
});

test('Fastify detail API expands included source in raw Markdown', async () => {
  const app = await buildApp({ logger: false });

  const response = await app.inject({
    method: 'GET',
    url: '/api/problems/luogu/P9094',
  });

  assert.equal(response.statusCode, 200);
  const body = response.json();
  assert.match(body.md_content, /```cpp\n#include <bits\/stdc\+\+\.h>/);
  assert.doesNotMatch(body.md_content, /@include-code/);
  assert.match(body.html_content, /class="language-cpp/);
  assert.match(body.html_content, /#include &lt;bits\/stdc\+\+\.h&gt;/);
  assert.doesNotMatch(body.html_content, /<span class="token/);

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

test('Fastify app releases content leases when the client aborts', async () => {
  let inFlight = 0;
  const fakeContentService = {
    state: 'healthy',
    acquireRequest() {
      inFlight += 1;
      return () => {
        inFlight -= 1;
      };
    },
  };

  const app = await buildApp({ logger: false, initializeContent: false });
  const guard = contentGuard(fakeContentService, 'json');
  app.get('/abort-slow', { preHandler: guard }, async () => {
    await new Promise((resolve) => setTimeout(resolve, 600));
    return { ok: true };
  });

  await app.listen({ port: 0, host: '127.0.0.1' });
  const port = app.server.address().port;

  try {
    const req = http.get({ host: '127.0.0.1', port, path: '/abort-slow' }, () => {});
    req.on('error', () => {});

    const acquired = Date.now() + 2000;
    while (inFlight < 1 && Date.now() < acquired) {
      await new Promise((resolve) => setTimeout(resolve, 10));
    }
    assert.equal(inFlight, 1);

    req.destroy();

    const released = Date.now() + 2000;
    while (inFlight > 0 && Date.now() < released) {
      await new Promise((resolve) => setTimeout(resolve, 10));
    }
    assert.equal(inFlight, 0);

    await new Promise((resolve) => setTimeout(resolve, 700));
  } finally {
    await app.close();
  }
});
