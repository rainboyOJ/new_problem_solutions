import test from 'node:test';
import assert from 'node:assert/strict';
import MarkdownRenderer from '../lib/markdown.js';
import ProblemManager from '../lib/problem.js';

test('ProblemManager find returns problem by oj/id', () => {
  const pm = new ProblemManager();
  const p = pm.find('poj', '3061');
  assert.ok(p);
  assert.equal(p.oj, 'poj');
  assert.equal(p.problem_id, '3061');
});

test('MarkdownRenderer resolves [[oj/id]] to problem link', () => {
  const pm = new ProblemManager();
  const md = new MarkdownRenderer('', pm);
  md.md_content = 'See [[poj/3061]] now.';
  const html = md.toHTML();
  assert.match(html, /href="\/problems\/poj\/3061"/);
  assert.match(html, /class="problem-link"/);
});

test('MarkdownRenderer renders TOC and KaTeX math', () => {
  const pm = new ProblemManager();
  const md = new MarkdownRenderer('', pm);
  md.md_content = `[[TOC]]

## Section Title

Inline math $a_i + b_i$.

$$
dp[i][j] = a_i + b_j
$$`;

  const html = md.toHTML();
  assert.match(html, /table-of-contents|toc-body/);
  assert.match(html, /Section Title/);
  assert.match(html, /class="katex"/);
  assert.match(html, /class="katex-display"/);
});

test('MarkdownRenderer includes code relative to markdown file', () => {
  const md = new MarkdownRenderer('problems/luogu/9094/index.md');
  const html = md.toHTML();

  assert.doesNotMatch(html, /@include-code/);
  assert.match(html, /<pre><code class="language-cpp">/);
  assert.match(html, /int main/);
  assert.match(html, /std::cin &gt;&gt; n/);
});
