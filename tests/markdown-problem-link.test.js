import test from 'node:test';
import assert from 'node:assert/strict';
import MarkdownRenderer from '../lib/markdown.js';
import ProblemManager from '../lib/problem.js';
import ProblemSetManager from '../lib/problem-set.js';

test('ProblemManager find returns problem by oj/id', () => {
  const pm = new ProblemManager();
  const p = pm.find('OpenJ_Bailian', '1651');
  assert.ok(p);
  assert.equal(p.oj, 'OpenJ_Bailian');
  assert.equal(p.problem_id, '1651');
  assert.equal(p.md_path, 'OpenJ_Bailian/1651/index.md');
});

test('ProblemManager scanned catalog resolves secondary problem-set links', () => {
  const pm = new ProblemManager();
  const problem = pm.find('usaco', '1016');

  assert.ok(problem);
  assert.equal(problem.md_path, 'usaco/1016/index.md');

  const problemSets = new ProblemSetManager(pm);
  const page = problemSets.find('2026-cspj-summer-first-prize');

  assert.match(page.content, /href="\/problems\/usaco\/1016"/);
  assert.match(page.content, /usaco-1016 Clock Tree/);
});

test('ProblemManager lists newest problems first', () => {
  const pm = new ProblemManager();
  const problems = pm.getAll();

  for (let i = 1; i < problems.length; i += 1) {
    assert.ok((problems[i - 1].dateA || 0) >= (problems[i].dateA || 0));
  }
});

test('ProblemManager builds GitHub URLs from config.yml', () => {
  const pm = new ProblemManager({ auto_load: false });

  assert.equal(pm.config.github_repository, 'https://github.com/RainboyOJ/new_problem_solutions');
  assert.equal(
    pm.github_url('luogu/5657/index.md'),
    'https://github.com/RainboyOJ/new_problem_solutions/blob/master/problems/luogu/5657/index.md',
  );
});

test('MarkdownRenderer resolves [[oj/id]] to problem link', () => {
  const pm = new ProblemManager();
  const md = new MarkdownRenderer('', pm);
  md.md_content = 'See [[OpenJ_Bailian/1651]] now.';
  const html = md.toHTML();
  assert.match(html, /href="\/problems\/OpenJ_Bailian\/1651"/);
  assert.match(html, /class="problem-link"/);
});

test('MarkdownRenderer resolves [[problem: oj,pid]] to problem link', () => {
  const pm = new ProblemManager();
  const md = new MarkdownRenderer('', pm);
  md.md_content = 'See [[problem: OpenJ_Bailian,1651]] now.';
  const html = md.toHTML();
  assert.match(html, /href="\/problems\/OpenJ_Bailian\/1651"/);
  assert.match(html, /class="problem-link"/);
});

test('ProblemManager scans only formal index.md problem pages', () => {
  const pm = new ProblemManager({ auto_load: false });
  const files = pm.scanProblems();

  assert.ok(files.length > 0);
  assert.ok(files.every((file) => file.endsWith('/index.md')));
  assert.ok(files.every((file) => !file.includes('problem-analysis-workspace/')));
  assert.ok(files.every((file) => !file.includes('duipai-failed/')));
  assert.ok(files.every((file) => !file.includes('__tmp')));
});

test('ProblemManager resolves pre, successor, and common relations', () => {
  const pm = new ProblemManager({ auto_load: false });
  pm.problems = [
    {
      oj: 'luogu',
      problem_id: 'P1',
      title: 'Base',
      url: '/problems/luogu/P1',
      pre: [],
      common: [{ oj: 'HDU', problem_id: '1000', reason: '同一模型。' }],
    },
    {
      oj: 'luogu',
      problem_id: 'P2',
      title: 'Advanced',
      url: '/problems/luogu/P2',
      pre: [{ oj: 'luogu', problem_id: 'P1', reason: '基础题。' }],
      common: [],
    },
    {
      oj: 'HDU',
      problem_id: '1000',
      title: 'Similar',
      url: '/problems/HDU/1000',
      pre: [],
      common: [],
    },
  ];
  pm.buildIndex();

  const relations = pm.getRelations(pm.find('luogu', 'P1'));

  assert.equal(relations.predecessors.length, 0);
  assert.deepEqual(
    relations.successors.map((item) => `${item.oj}/${item.problem_id}`),
    ['luogu/P2'],
  );
  assert.deepEqual(
    relations.common.map((item) => `${item.oj}/${item.problem_id}`),
    ['HDU/1000'],
  );
  assert.equal(relations.hasAny, true);
});

test('ProblemManager normalizes external recommendations', () => {
  const pm = new ProblemManager({ auto_load: false });
  const recommendations = pm.getRecommendations({
    recommend: [
      {
        oj: 'leetcode',
        problem_id: '62',
        title: 'Unique Paths',
        url: 'https://leetcode.com/problems/unique-paths/',
        reason: '同样是基础网格路径计数 DP。',
        relation: 'similar',
      },
      'bad item',
    ],
  });

  assert.deepEqual(recommendations, [
    {
      oj: 'leetcode',
      problem_id: '62',
      title: 'Unique Paths',
      url: 'https://leetcode.com/problems/unique-paths/',
      reason: '同样是基础网格路径计数 DP。',
      relation: 'similar',
    },
  ]);
});

test('ProblemManager builds global relation graph data', () => {
  const pm = new ProblemManager({ auto_load: false });
  pm.problems = [
    {
      oj: 'luogu',
      problem_id: 'P1',
      title: 'Base',
      url: '/problems/luogu/P1',
      tags: ['dp'],
      pre: [],
      common: [{ oj: 'HDU', problem_id: '1000', reason: '同一模型。' }],
    },
    {
      oj: 'luogu',
      problem_id: 'P2',
      title: 'Advanced',
      url: '/problems/luogu/P2',
      tags: ['graph'],
      pre: [{ oj: 'luogu', problem_id: 'P1', reason: '基础题。' }],
      common: [],
    },
    {
      oj: 'HDU',
      problem_id: '1000',
      title: 'Similar',
      url: '/problems/HDU/1000',
      tags: [],
      pre: [],
      common: [],
    },
    {
      oj: 'poj',
      problem_id: '9999',
      title: 'Isolated',
      url: '/problems/poj/9999',
      tags: [],
      pre: [],
      common: [],
    },
  ];
  pm.buildIndex();

  const graph = pm.getRelationGraph();

  assert.equal(graph.nodes.length, 4);
  assert.equal(graph.edges.length, 2);
  assert.equal(graph.summary.relationNodes, 3);
  assert.equal(graph.summary.isolatedNodes, 1);
  assert.ok(graph.edges.some((edge) => edge.id === 'pre:luogu/P1->luogu/P2' && edge.directed));
  assert.ok(graph.edges.some((edge) => edge.type === 'common' && !edge.directed));
  assert.equal(graph.nodes.find((node) => node.id === 'poj/9999').isolated, true);
});

test('ProblemManager search matches problem description', () => {
  const pm = new ProblemManager({ auto_load: false });
  pm.problems = [
    {
      oj: 'luogu',
      problem_id: 'P1',
      title: 'Base',
      description: '用单调队列维护窗口最值。',
      url: '/problems/luogu/P1',
    },
    {
      oj: 'luogu',
      problem_id: 'P2',
      title: 'Other',
      description: '普通枚举。',
      url: '/problems/luogu/P2',
    },
  ];
  pm.buildIndex();

  assert.deepEqual(
    pm.search('单调队列').map((problem) => problem.problem_id),
    ['P1'],
  );
});

test('ProblemManager search matches tags and favorite reason', () => {
  const pm = new ProblemManager({ auto_load: false });
  pm.problems = [
    {
      oj: 'luogu',
      problem_id: 'P1',
      title: 'Base',
      tags: ['单调队列'],
      favorite_reason: '这个状态设计值得复习。',
      url: '/problems/luogu/P1',
    },
    {
      oj: 'luogu',
      problem_id: 'P2',
      title: 'Other',
      tags: ['枚举'],
      favorite_reason: '',
      url: '/problems/luogu/P2',
    },
  ];
  pm.buildIndex();

  assert.deepEqual(pm.search('单调队列').map((problem) => problem.problem_id), ['P1']);
  assert.deepEqual(pm.search('状态设计').map((problem) => problem.problem_id), ['P1']);
});

test('ProblemManager normalizes missing favorite metadata for legacy problems', () => {
  const pm = new ProblemManager({ auto_load: false });

  assert.deepEqual(pm.normalizeProblem({ title: 'Legacy' }), {
    title: 'Legacy',
    favorite: false,
    favorite_reason: '',
  });
});

test('MarkdownRenderer renders TOC and KaTeX math', () => {
  const pm = new ProblemManager();
  const md = new MarkdownRenderer('', pm);
  md.md_content = `[[TOC]]

## 题意

中文标题用于检查目录锚点。

## Section Title

Inline math $a_i + b_i$.

$$
dp[i][j] = a_i + b_j
$$`;

  const html = md.toHTML();
  assert.match(html, /table-of-contents|toc-body/);
  assert.match(html, /<a href="#题意">题意<\/a>/);
  assert.match(html, /<h2 id="题意" tabindex="-1">题意<\/h2>/);
  assert.match(html, /Section Title/);
  assert.match(html, /class="katex"/);
  assert.match(html, /class="katex-display"/);
});

test('MarkdownRenderer TOC href fragments match rendered heading ids after browser decoding', () => {
  const md = new MarkdownRenderer('');
  md.md_content = `[[TOC]]

## 题意

## SPFA 风格

### 样例转移表

## 题意
`;

  const html = md.toHTML();
  const tocLinks = Array.from(html.matchAll(/<a href="([^"]+)">([^<]+)<\/a>/g));
  const headings = Array.from(html.matchAll(/<h[23] id="([^"]+)" tabindex="-1">([^<]+)<\/h[23]>/g));

  assert.ok(tocLinks.length > 0);
  assert.equal(tocLinks.length, headings.length);

  for (let i = 0; i < tocLinks.length; i++) {
    const href = tocLinks[i][1];
    const linkText = tocLinks[i][2];
    const headingId = headings[i][1];
    const headingText = headings[i][2];

    assert.equal(linkText, headingText);
    assert.equal(decodeURIComponent(href.slice(1)), headingId);
  }
});

test('MarkdownRenderer includes code relative to markdown file', () => {
  const md = new MarkdownRenderer('problems/luogu/9094/index.md');
  const html = md.toHTML();

  assert.doesNotMatch(html, /@include-code/);
  assert.match(html, /class="language-cpp line-numbers-mode code-block"/);
  assert.match(html, /class="code-copy-button" type="button" data-code-copy/);
  assert.match(html, /class="line-numbers-wrapper" aria-hidden="true">1\n2\n3/);
  assert.match(html, /<span class="token function">main<\/span>/);
  assert.match(html, /std/);
  assert.match(html, /cin/);
  assert.match(html, /<span class="token operator">>><\/span>/);
});

test('MarkdownRenderer renders plain fences with copy button and line numbers', () => {
  const md = new MarkdownRenderer('');
  md.md_content = [
    '```cpp',
    '#include <bits/stdc++.h>',
    'int main() { return 0; }',
    '```',
  ].join('\n');

  const html = md.toHTML();

  assert.match(html, /class="language-cpp line-numbers-mode code-block"/);
  assert.match(html, /<span class="code-info-label">cpp<\/span>/);
  assert.match(html, /data-code-copy aria-label="复制代码">复制<\/button>/);
  assert.match(html, /class="line-numbers-wrapper" aria-hidden="true">1\n2<\/span>/);
  assert.match(html, /<span class="token macro property">/);
});

test('MarkdownRenderer renders visualization fences for Mermaid and Graphviz', () => {
  const md = new MarkdownRenderer('');
  md.md_content = [
    '```mermaid',
    'flowchart LR',
    '  A --> B',
    '```',
    '',
    '```dot',
    'graph G {',
    '  1 -- 2;',
    '}',
    '```',
  ].join('\n');

  const html = md.toHTML();

  assert.match(html, /<pre class="mermaid">\nflowchart LR/);
  assert.match(html, /A --&gt; B/);
  assert.match(html, /<div class="graphviz" data-viz-engine="dot"><pre class="dot">/);
  assert.match(html, /1 -- 2;/);
  assert.doesNotMatch(html, /data-code-copy/);
});

test('MarkdownRenderer supports migrated rbook markdown extensions', () => {
  const md = new MarkdownRenderer('problems/OpenJ_Bailian/1651/index.md');
  md.md_content = `[[TOC]]

## Section

!!! warning 注意
body
!!!

::: fold
hidden
:::

::: center
centered
:::

- [x] done

:smile:

![alt](a.png =100x200)

[relative](./other.md)

++ins++ ~~del~~ ==mark== H~2~O x^2^
`;

  const html = md.toHTML();
  assert.match(html, /toc-body/);
  assert.match(html, /class="admonition warning"/);
  assert.match(html, /<details><summary>/);
  assert.match(html, /<div class="center">/);
  assert.match(html, /class="task-list"/);
  assert.match(html, /class="emoji"/);
  assert.match(html, /width="100" height="200"/);
  assert.match(html, /href="\/problems\/OpenJ_Bailian\/1651\/other.html"/);
  assert.match(html, /<ins>ins<\/ins>/);
  assert.match(html, /<s>del<\/s>/);
  assert.match(html, /<mark>mark<\/mark>/);
  assert.match(html, /H<sub>2<\/sub>O/);
  assert.match(html, /x<sup>2<\/sup>/);
});
