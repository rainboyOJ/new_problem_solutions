import test from 'node:test';
import assert from 'node:assert/strict';
import fs from 'fs';
import os from 'os';
import path from 'path';

import {
  buildPreviewApp,
  resolvePreviewProblem,
  resolvePreviewProblemOrThrow,
} from '../lib/preview-app.js';

function makeTempRepo() {
  return fs.mkdtempSync(path.join(os.tmpdir(), 'rbook-preview-'));
}

function writeProblem(root, dirName = 'P1010') {
  const problemDir = path.join(root, 'problems', 'luogu', dirName);
  fs.mkdirSync(problemDir, { recursive: true });
  fs.writeFileSync(path.join(problemDir, 'main.cpp'), '#include <bits/stdc++.h>\nint main() { return 0; }\n');
  fs.writeFileSync(path.join(problemDir, 'diagram.png'), 'fake image data\n');
  fs.writeFileSync(path.join(problemDir, 'problem.md'), '# 原题面\n\n这是题面。\n');
  fs.writeFileSync(path.join(problemDir, 'index.md'), [
    '---',
    'title: 测试题',
    'oj: luogu',
    'problem_id: P1010',
    'source: https://www.luogu.com.cn/problem/P1010',
    'tags:',
    '  - 测试',
    '---',
    '',
    '# 题解',
    '',
    '![图](./diagram.png)',
    '',
    '```mermaid',
    'flowchart LR',
    '  A --> B',
    '```',
    '',
    '```dot',
    'digraph G {',
    '  A -> B;',
    '}',
    '```',
    '',
    '@include-code(./main.cpp, cpp)',
    '',
  ].join('\n'));

  return problemDir;
}

test('resolvePreviewProblem supports luogu numeric id fallback to P-prefixed directory', () => {
  const root = makeTempRepo();
  writeProblem(root, 'P1010');

  const preview = resolvePreviewProblem('luogu', '1010', { projectRoot: root });

  assert.ok(preview);
  assert.equal(preview.problem.problem_id, 'P1010');
  assert.equal(preview.problem.oj, 'luogu');
  assert.ok(preview.aliases.includes('1010'));
  assert.ok(preview.aliases.includes('P1010'));
  assert.equal(preview.problem.md_path, 'luogu/P1010/index.md');
});

test('resolvePreviewProblem prefers the exact luogu directory when it exists', () => {
  const root = makeTempRepo();
  writeProblem(root, '1010');
  writeProblem(root, 'P1010');

  const preview = resolvePreviewProblem('luogu', '1010', { projectRoot: root });

  assert.ok(preview);
  assert.equal(preview.problemDir, path.join(root, 'problems', 'luogu', '1010'));
});

test('preview app renders the problem page, API, and relative assets', async () => {
  const root = makeTempRepo();
  writeProblem(root, 'P1010');
  const preview = resolvePreviewProblem('luogu', '1010', { projectRoot: root });
  const app = await buildPreviewApp(preview, { logger: false });

  const redirect = await app.inject({
    method: 'GET',
    url: '/problems/luogu/1010',
  });
  assert.equal(redirect.statusCode, 302);
  assert.equal(redirect.headers.location, '/problems/luogu/P1010/');

  const page = await app.inject({
    method: 'GET',
    url: '/problems/luogu/P1010/',
  });
  assert.equal(page.statusCode, 200);
  assert.match(page.headers['content-type'], /text\/html/);
  assert.match(page.body, /测试题/);
  assert.match(page.body, /src="\.\/diagram\.png"/);
  assert.match(page.body, /class="mermaid"/);
  assert.match(page.body, /class="graphviz"/);
  assert.match(page.body, /data-viz-engine="dot"/);
  assert.match(page.body, /language-cpp/);
  assert.match(page.body, /&lt;bits\/stdc\+\+\.h&gt;/);
  assert.doesNotMatch(page.body, /<span class="token/);
  assert.match(page.body, />跳转原题</);
  assert.match(page.body, /href="https:\/\/www\.luogu\.com\.cn\/problem\/P1010"/);
  assert.match(page.body, /显示题目/);
  assert.match(page.body, /href="\/vendor\/prism\/themes\/prism-tomorrow\.min\.css"/);
  assert.doesNotMatch(page.body, /cdnjs\.cloudflare\.com\/ajax\/libs\/prism/);
  assert.match(page.body, /src="\/vendor\/prism\/components\/prism-core\.min\.js"/);
  assert.match(page.body, /src="\/vendor\/prism\/plugins\/autoloader\/prism-autoloader\.min\.js"/);
  assert.match(page.body, /src="\/javascripts\/code-highlight\.js"/);
  assert.match(page.body, /src="\/javascripts\/md-raw-modal\.js"/);
  assert.ok(
    page.body.indexOf('/javascripts/code-highlight.js')
      < page.body.indexOf('/javascripts/md-raw-modal.js'),
  );
  assert.match(
    page.body,
    /<div class="d-flex gap-2 problem-page-actions"><button class="btn btn-outline-dark btn-sm problem-source-link problem-md-raw-button"/,
  );
  assert.match(page.body, /data-md-raw-trigger[^>]*data-md-raw-url="\/api\/problems\/luogu\/P1010"[^>]*hidden/);
  assert.match(page.body, /id="mdRawModal"[^>]*data-md-raw-modal/);
  assert.match(page.body, /class="modal-dialog modal-xl modal-dialog-scrollable modal-fullscreen-sm-down"/);
  assert.match(page.body, /id="mdRawModalLabel"[^>]*>Markdown Raw<\/h2>/);
  assert.match(page.body, /data-md-raw-copy[^>]*disabled[^>]*>复制全部<\/button>/);
  assert.match(page.body, /data-md-raw-retry[^>]*hidden[^>]*>重试<\/button>/);
  assert.match(page.body, /data-md-raw-line-numbers[^>]*aria-hidden="true"/);
  assert.match(page.body, /<code class="language-markdown" data-md-raw-code><\/code>/);
  assert.doesNotMatch(page.body, /data-md-raw-code>---/);

  const prismCore = await app.inject({
    method: 'GET',
    url: '/vendor/prism/components/prism-core.min.js',
  });
  assert.equal(prismCore.statusCode, 200);
  assert.match(prismCore.headers['content-type'], /javascript/);

  const prismTraversal = await app.inject({
    method: 'GET',
    url: '/vendor/prism/..%2F..%2Fpackage.json',
  });
  assert.notEqual(prismTraversal.statusCode, 200);

  const vizRuntime = await app.inject({
    method: 'GET',
    url: '/vendor/viz-global.js',
  });
  assert.equal(vizRuntime.statusCode, 200);
  assert.match(vizRuntime.body, /Viz\.js/);

  const asset = await app.inject({
    method: 'GET',
    url: '/problems/luogu/P1010/diagram.png',
  });
  assert.equal(asset.statusCode, 200);
  assert.equal(asset.body, 'fake image data\n');

  const api = await app.inject({
    method: 'GET',
    url: '/api/problems/luogu/P1010',
  });
  assert.equal(api.statusCode, 200);
  assert.equal(api.json().problem_id, 'P1010');
  assert.match(api.json().html_content, /language-cpp/);
  assert.match(api.json().html_content, /&lt;bits\/stdc\+\+\.h&gt;/);
  assert.doesNotMatch(api.json().html_content, /<span class="token/);
  assert.match(
    api.json().md_content,
    /```cpp\n#include <bits\/stdc\+\+\.h>\nint main\(\) \{ return 0; \}\n```/,
  );
  assert.doesNotMatch(api.json().md_content, /@include-code/);

  await app.close();
});

test('resolvePreviewProblemOrThrow reports candidate paths for missing problem', () => {
  const root = makeTempRepo();

  assert.throws(
    () => resolvePreviewProblemOrThrow('luogu', '1010', { projectRoot: root }),
    (error) => {
      assert.equal(error.code, 'PREVIEW_PROBLEM_NOT_FOUND');
      assert.deepEqual(error.tried, [
        'problems/luogu/1010/index.md',
        'problems/luogu/P1010/index.md',
      ]);
      return true;
    },
  );
});
