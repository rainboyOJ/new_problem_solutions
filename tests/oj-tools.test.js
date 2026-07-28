import test from 'node:test';
import assert from 'node:assert/strict';
import { execFileSync, spawnSync } from 'node:child_process';
import { mkdirSync, mkdtempSync, readFileSync, rmSync, writeFileSync } from 'node:fs';
import { tmpdir } from 'node:os';
import { join } from 'node:path';
import LUOGU from '../old_scripts/online_judge/luogu.js';

test('Luogu downloader renders problem.md content', () => {
  const luogu = new LUOGU();
  const markdown = luogu.problem_statement_markdown(
    {
      title: 'Test Problem',
      description: 'problem description',
      input: 'input format',
      output: 'output format',
      samples: [{ input: '1 2', output: '3' }],
      hint: 'hint text',
    },
    'P9999',
  );

  assert.match(markdown, /^# P9999 Test Problem/);
  assert.match(markdown, /## 题目描述\n\nproblem description/);
  assert.match(markdown, /## 输入格式\n\ninput format/);
  assert.match(markdown, /## 输出格式\n\noutput format/);
  assert.match(markdown, /## 输入输出样例 #1/);
  assert.match(markdown, /```\n1 2\n```/);
  assert.match(markdown, /```\n3\n```/);
  assert.match(markdown, /## 说明\/提示\n\nhint text/);
});

function runTreeDraw(args, input = '') {
  return execFileSync(
    'python3',
    ['scripts/problem-analysis-tools/tree_draw.py', ...args],
    {
      cwd: process.cwd(),
      input,
      encoding: 'utf8',
    },
  );
}

test('tree_draw renders normal tree SVG from edge list', () => {
  const dir = mkdtempSync(join(tmpdir(), 'tree-draw-'));
  const output = join(dir, 'normal.svg');
  const stdout = runTreeDraw(['--type', 'normal', '-o', output, '--markdown'], [
    '5',
    '1 2',
    '1 3',
    '2 4',
    '2 5',
    '',
  ].join('\n'));
  const svg = readFileSync(output, 'utf8');

  assert.match(stdout, /!\[树形结构示意图\]\(\.\/normal\.svg\)/);
  assert.match(svg, /<svg /);
  assert.match(svg, /data-id="1"/);
  assert.match(svg, /data-id="5"/);
  assert.match(svg, /<line x1=/);
});

test('tree_draw renders binary tree child table with edge labels', () => {
  const dir = mkdtempSync(join(tmpdir(), 'tree-draw-'));
  const input = join(dir, 'binary.txt');
  const output = join(dir, 'binary.svg');
  writeFileSync(input, [
    '5',
    '1 2 3',
    '2 4 5',
    '3 0 0',
    '4 0 0',
    '5 0 0',
    '',
  ].join('\n'));

  runTreeDraw(['--type', 'binary', '--input', input, '--output', output]);
  const svg = readFileSync(output, 'utf8');

  assert.match(svg, />L<\/text>/);
  assert.match(svg, />R<\/text>/);
  assert.match(svg, /data-id="4"/);
});

test('tree_draw renders JSON tree with node style overrides', () => {
  const dir = mkdtempSync(join(tmpdir(), 'tree-draw-'));
  const output = join(dir, 'json.svg');
  const data = JSON.stringify({
    type: 'binary',
    root: 'a',
    nodes: [
      { id: 'a', label: '8', left: 'b', right: 'c', style: { fill: '#fee2e2' } },
      { id: 'b', label: '3' },
      { id: 'c', label: '10' },
    ],
  });

  runTreeDraw(['--type', 'json', '--output', output], data);
  const svg = readFileSync(output, 'utf8');

  assert.match(svg, /data-id="a"/);
  assert.match(svg, />8<\/text>/);
  assert.match(svg, /fill="#fee2e2"/);
});

test('tree_draw renders segment tree preset', () => {
  const dir = mkdtempSync(join(tmpdir(), 'tree-draw-'));
  const output = join(dir, 'segment.svg');

  runTreeDraw(['--type', 'segment', '--size', '4', '--output', output]);
  const svg = readFileSync(output, 'utf8');

  assert.match(svg, />\[1,4\]<\/text>/);
  assert.match(svg, />\[1,2\]<\/text>/);
  assert.match(svg, /<rect /);
});

test('ptool can locate tree_draw help', () => {
  const stdout = execFileSync(
    'scripts/navi/ptool',
    ['tree_draw', '--help'],
    { cwd: process.cwd(), encoding: 'utf8' },
  );

  assert.match(stdout, /使用 Walker 风格布局绘制树结构 SVG/);
});

test('cpp_header can generate and update Haskell style headers', () => {
  const script = `
import datetime as dt
import sys

sys.path.insert(0, "scripts/problem-analysis-tools")
from cpp_header import build_haskell_header, replace_or_insert_header

first = dt.datetime(2026, 7, 9, 18, 0)
second = dt.datetime(2026, 7, 9, 19, 30)
content = "main :: IO ()\\nmain = pure ()\\n"
updated = replace_or_insert_header(content, style="haskell", now=first)
updated_again = replace_or_insert_header(updated, style="haskell", now=second)

assert build_haskell_header(now=first).startswith("{-\\n Author by Rainboy")
assert updated.startswith("{-\\n Author by Rainboy")
assert "create_at: 2026-07-09 18:00" in updated_again
assert "update_at: 2026-07-09 19:30" in updated_again
assert updated_again.count("Author by Rainboy") == 1
assert updated_again.rstrip().endswith("main = pure ()")
print(updated_again)
`;
  const result = spawnSync(
    'python3',
    ['-c', script],
    { cwd: process.cwd(), encoding: 'utf8' },
  );

  assert.equal(result.status, 0, result.stderr || result.stdout);
  assert.match(result.stdout, /^\{-\n Author by Rainboy/);
  assert.match(result.stdout, /create_at: 2026-07-09 18:00/);
  assert.match(result.stdout, /update_at: 2026-07-09 19:30/);
});

function writeProblemFixture(dir, frontmatterLines) {
  mkdirSync(dir, { recursive: true });
  writeFileSync(join(dir, 'main.cpp'), 'int main() { return 0; }\n');
  writeFileSync(join(dir, 'index.md'), [
    '---',
    ...frontmatterLines,
    '---',
    '',
    '[[TOC]]',
    '',
    '### 题意',
    '',
    '### 思路',
    '',
    '### 代码',
    '',
    '@include-code(./main.cpp, cpp)',
    '',
    '### 复杂度',
    '',
    '### 总结',
    '',
  ].join('\n'));
}

test('check_problem requires description and warns when it is empty', () => {
  const fixtureRoot = join(process.cwd(), 'problems', '__tmp_check_description__');
  const problemDir = join(fixtureRoot, 'P1');
  const baseFrontmatter = [
    'oj: "luogu"',
    'problem_id: "P1"',
    'title: "Test"',
    'difficulty: "未知"',
    'date: 2026-06-13 10:00',
    'toc: true',
    'tags: []',
    'categories: []',
    'source:',
  ];

  try {
    rmSync(fixtureRoot, { recursive: true, force: true });
    writeProblemFixture(problemDir, baseFrontmatter);
    const missing = spawnSync(
      'python3',
      ['scripts/problem-analysis-tools/check_problem.py', problemDir],
      { cwd: process.cwd(), encoding: 'utf8' },
    );
    assert.equal(missing.status, 1);
    assert.match(missing.stdout, /frontmatter 缺少字段：description/);

    writeProblemFixture(problemDir, [
      ...baseFrontmatter.slice(0, 3),
      'description: ""',
      ...baseFrontmatter.slice(3),
    ]);
    const empty = spawnSync(
      'python3',
      ['scripts/problem-analysis-tools/check_problem.py', problemDir],
      { cwd: process.cwd(), encoding: 'utf8' },
    );
    assert.equal(empty.status, 0);
    assert.match(empty.stdout, /frontmatter description 为空/);
  } finally {
    rmSync(fixtureRoot, { recursive: true, force: true });
  }
});

test('check_problem accepts non-C++ main include files', () => {
  const fixtureRoot = join(process.cwd(), 'problems', '__tmp_check_multilang__');
  const problemDir = join(fixtureRoot, 'P1');

  try {
    rmSync(fixtureRoot, { recursive: true, force: true });
    mkdirSync(problemDir, { recursive: true });
    writeFileSync(join(problemDir, 'main.rs'), 'main = putStrLn "ok"\n');
    writeFileSync(join(problemDir, 'index.md'), [
      '---',
      'oj: "__tmp_check_multilang__"',
      'problem_id: "P1"',
      'title: "Test"',
      'description: "测试多语言正式代码 include。"',
      'difficulty: "入门"',
      'date: 2026-07-09 18:30',
      'toc: true',
      'tags: ["haskell"]',
      'categories: []',
      'pre: []',
      'common: []',
      'recommend: []',
      'source:',
      '---',
      '',
      '[[TOC]]',
      '',
      '### 题意',
      '',
      '### 思路',
      '',
      '### 代码',
      '',
      '@include-code(./main.rs, haskell)',
      '',
      '### 复杂度',
      '',
      '### 总结',
      '',
    ].join('\n'));

    const ok = spawnSync(
      'python3',
      ['scripts/problem-analysis-tools/check_problem.py', problemDir],
      { cwd: process.cwd(), encoding: 'utf8' },
    );
    assert.equal(ok.status, 0, ok.stdout);
    assert.match(ok.stdout, /通过：题目目录符合当前规范。/);

    writeFileSync(join(problemDir, 'index.md'), readFileSync(join(problemDir, 'index.md'), 'utf8').replace(
      '@include-code(./main.rs, haskell)',
      '@include-code(./main.hs, haskell)',
    ));
    const missing = spawnSync(
      'python3',
      ['scripts/problem-analysis-tools/check_problem.py', problemDir],
      { cwd: process.cwd(), encoding: 'utf8' },
    );
    assert.equal(missing.status, 1);
    assert.match(missing.stdout, /index.md 引用的正式代码文件不存在：\.\/main\.hs/);
  } finally {
    rmSync(fixtureRoot, { recursive: true, force: true });
  }
});

test('check_problem allows fetched problem.md statement file', () => {
  const fixtureRoot = join(process.cwd(), 'problems', '__tmp_check_problem_md__');
  const problemDir = join(fixtureRoot, 'P1');

  try {
    rmSync(fixtureRoot, { recursive: true, force: true });
    writeProblemFixture(problemDir, [
      'oj: "__tmp_check_problem_md__"',
      'problem_id: "P1"',
      'title: "Test"',
      'description: "测试抓题生成的 problem.md 不触发根部文档警告。"',
      'difficulty: "入门"',
      'date: 2026-07-09 18:40',
      'toc: true',
      'tags: []',
      'categories: []',
      'pre: []',
      'common: []',
      'recommend: []',
      'source:',
    ]);
    writeFileSync(join(problemDir, 'problem.md'), '# Statement\n');

    const ok = spawnSync(
      'python3',
      ['scripts/problem-analysis-tools/check_problem.py', problemDir],
      { cwd: process.cwd(), encoding: 'utf8' },
    );
    assert.equal(ok.status, 0, ok.stdout);
    assert.match(ok.stdout, /通过：题目目录符合当前规范。/);
    assert.doesNotMatch(ok.stdout, /题目目录根部存在非 index.md 文档/);
  } finally {
    rmSync(fixtureRoot, { recursive: true, force: true });
  }
});

test('new-problem scaffold includes description and recommend frontmatter fields', () => {
  const fixtureRoot = join(process.cwd(), 'problems', '__tmp_new_problem_description__');
  const problemDir = join(fixtureRoot, 'P1');

  try {
    rmSync(fixtureRoot, { recursive: true, force: true });
    const result = spawnSync(
      'python3',
      [
        'scripts/problem-analysis-tools/new-problem.py',
        '__tmp_new_problem_description__',
        'P1',
        '--title',
        'Test',
      ],
      { cwd: process.cwd(), encoding: 'utf8' },
    );

    assert.equal(result.status, 0);
    const indexMd = readFileSync(join(problemDir, 'index.md'), 'utf8');
    assert.match(indexMd, /title: "Test"\ndescription: ""\ndifficulty: "未知"\ndate:/);
    assert.match(indexMd, /tags: \[\]\nfavorite: false\nfavorite_reason: ""\ncategories: \[\]\npre: \[\]\ncommon: \[\]\nrecommend: \[\]\nsource:/);
  } finally {
    rmSync(fixtureRoot, { recursive: true, force: true });
  }
});

test('check_problem validates optional favorite metadata types', () => {
  const fixtureRoot = join(process.cwd(), 'problems', '__tmp_check_favorite__');
  const problemDir = join(fixtureRoot, 'P1');
  const baseFrontmatter = [
    'oj: "__tmp_check_favorite__"',
    'problem_id: "P1"',
    'title: "Test"',
    'description: "测试 favorite 元数据。"',
    'difficulty: "入门"',
    'date: 2026-07-20 10:00',
    'toc: true',
    'tags: []',
    'favorite: true',
    'favorite_reason: "这道题让我理解了状态压缩。"',
    'categories: []',
    'pre: []',
    'common: []',
    'recommend: []',
    'source:',
  ];

  try {
    rmSync(fixtureRoot, { recursive: true, force: true });
    writeProblemFixture(problemDir, baseFrontmatter);
    const valid = spawnSync(
      'python3',
      ['scripts/problem-analysis-tools/check_problem.py', problemDir],
      { cwd: process.cwd(), encoding: 'utf8' },
    );
    assert.equal(valid.status, 0, valid.stdout);
    assert.match(valid.stdout, /通过：题目目录符合当前规范。/);

    writeProblemFixture(problemDir, [
      ...baseFrontmatter.slice(0, 8),
      'favorite: "true"',
      ...baseFrontmatter.slice(9),
    ]);
    const invalidFavorite = spawnSync(
      'python3',
      ['scripts/problem-analysis-tools/check_problem.py', problemDir],
      { cwd: process.cwd(), encoding: 'utf8' },
    );
    assert.equal(invalidFavorite.status, 1);
    assert.match(invalidFavorite.stdout, /favorite 必须是布尔值 true 或 false/);

    writeProblemFixture(problemDir, [
      ...baseFrontmatter.slice(0, 9),
      'favorite_reason: 123',
      ...baseFrontmatter.slice(10),
    ]);
    const invalidReason = spawnSync(
      'python3',
      ['scripts/problem-analysis-tools/check_problem.py', problemDir],
      { cwd: process.cwd(), encoding: 'utf8' },
    );
    assert.equal(invalidReason.status, 1);
    assert.match(invalidReason.stdout, /favorite_reason 必须是字符串/);
  } finally {
    rmSync(fixtureRoot, { recursive: true, force: true });
  }
});

test('fetch_problem self-test creates index description field', () => {
  const result = spawnSync(
    'python3',
    ['scripts/problem-analysis-tools/fetch_problem.py', '--self-test'],
    { cwd: process.cwd(), encoding: 'utf8' },
  );

  assert.equal(result.status, 0);
  assert.match(result.stdout, /self-test passed/);
});

test('fetch_problem normalizes CRLF in fetched statement and samples', () => {
  const script = `
import argparse
import json
import sys
import tempfile
from pathlib import Path

sys.path.insert(0, "scripts/problem-analysis-tools")
from fetch_problem import write_fetch_outputs
from fetchers import ProblemData, Sample

with tempfile.TemporaryDirectory() as tmp:
    root = Path(tmp)
    problem_dir = root / "problems" / "atcoder" / "crlf"
    data = ProblemData(
        oj="atcoder",
        problem_id="crlf",
        problem_dir_id="crlf",
        source="https://atcoder.jp/contests/test/tasks/crlf",
        title="CRLF",
        statement_md="# CRLF\\r\\n\\r\\nbody\\r\\n",
        samples=[Sample(input="1 2\\r\\n", output="3\\r\\n")],
    )
    args = argparse.Namespace(
        force_statement=False,
        force_samples=False,
        force_index_meta=False,
        dry_run=False,
    )
    write_fetch_outputs(problem_dir, data, args, repo_root=root)
    paths = ["problem.md", "in1", "out1", "in"]
    payload = {
        name: (problem_dir / name).read_text(encoding="utf-8")
        for name in paths
    }
    print(json.dumps(payload))
`;
  const result = spawnSync(
    'python3',
    ['-c', script],
    { cwd: process.cwd(), encoding: 'utf8' },
  );

  assert.equal(result.status, 0, result.stderr || result.stdout);
  const payload = JSON.parse(result.stdout.trim());
  assert.deepEqual(payload, {
    'problem.md': '# CRLF\n\nbody\n',
    in1: '1 2\n',
    out1: '3\n',
    in: '1 2\n',
  });
});

test('AtCoder fetcher parses original-site HTML fixture', () => {
  const script = `
import json
import sys
from pathlib import Path

sys.path.insert(0, "scripts/problem-analysis-tools")
from fetchers.atcoder import AtCoderFetcher

html = Path("scripts/problem-analysis-tools/tests/fixtures/atcoder_practice_1.html").read_text(encoding="utf-8")
data = AtCoderFetcher().parse_html(html, "abs/practice_1")
print(json.dumps({
    "oj": data.oj,
    "problem_id": data.problem_id,
    "problem_dir_id": data.problem_dir_id,
    "title": data.title,
    "sample_count": len(data.samples),
    "first_input": data.samples[0].input,
    "second_output": data.samples[1].output,
    "statement": data.statement_md,
}, ensure_ascii=False))
`;
  const result = spawnSync(
    'python3',
    ['-c', script],
    { cwd: process.cwd(), encoding: 'utf8' },
  );

  assert.equal(result.status, 0, result.stderr || result.stdout);
  const payload = JSON.parse(result.stdout.trim());
  assert.equal(payload.oj, 'atcoder');
  assert.equal(payload.problem_id, 'practice_1');
  assert.equal(payload.problem_dir_id, 'practice_1');
  assert.equal(payload.title, 'PracticeA - Welcome to AtCoder');
  assert.equal(payload.sample_count, 2);
  assert.equal(payload.first_input, '1\n2 3\ntest');
  assert.equal(payload.second_output, '456 myonmyon');
  assert.match(payload.statement, /^# practice_1 PracticeA - Welcome to AtCoder/);
  assert.match(payload.statement, /## 题目描述\n\nYour task is to process some data\./);
  assert.match(payload.statement, /## 输入输出样例 #2/);
  assert.doesNotMatch(payload.statement, /This section should not be copied/);
});

test('LeetCodeCN fetcher resolves ids and parses GraphQL fixture', () => {
  const script = `
import json
import sys
from pathlib import Path

sys.path.insert(0, "scripts/problem-analysis-tools")
from fetchers.leetcodecn import LeetCodeCNFetcher

fixture = json.loads(Path("scripts/problem-analysis-tools/tests/fixtures/leetcodecn_two_sum.json").read_text(encoding="utf-8"))

class FixtureFetcher(LeetCodeCNFetcher):
    def http_get(self, url, timeout=15):
        return json.dumps({
            "stat_status_pairs": [
                {"stat": {"frontend_question_id": "1", "question__title_slug": "two-sum"}}
            ]
        })

fetcher = FixtureFetcher()
data = fetcher.parse_payload(fixture, "two-sum")
print(json.dumps({
    "url": fetcher.parse_url("https://leetcode.cn/problems/two-sum/description/"),
    "problem_url_match": fetcher.match_url("https://leetcode.cn/problems/two-sum/"),
    "study_plan_match": fetcher.match_url("https://leetcode.cn/studyplan/top-100-liked/"),
    "slug_from_id": fetcher.resolve_slug("1"),
    "slug_from_composite": fetcher.resolve_slug("1.two-sum"),
    "oj": data.oj,
    "problem_id": data.problem_id,
    "problem_dir_id": data.problem_dir_id,
    "title": data.title,
    "source": data.source,
    "sample_count": len(data.samples),
    "warnings": data.warnings,
    "statement": data.statement_md,
}, ensure_ascii=False))
`;
  const result = spawnSync(
    'python3',
    ['-c', script],
    { cwd: process.cwd(), encoding: 'utf8' },
  );

  assert.equal(result.status, 0, result.stderr || result.stdout);
  const payload = JSON.parse(result.stdout.trim());
  assert.deepEqual(payload.url, ['leetcodecn', 'two-sum']);
  assert.equal(payload.problem_url_match, true);
  assert.equal(payload.study_plan_match, false);
  assert.equal(payload.slug_from_id, 'two-sum');
  assert.equal(payload.slug_from_composite, 'two-sum');
  assert.equal(payload.oj, 'leetcodecn');
  assert.equal(payload.problem_id, 'two-sum');
  assert.equal(payload.problem_dir_id, 'two-sum');
  assert.equal(payload.title, '两数之和');
  assert.equal(payload.source, 'https://leetcode.cn/problems/two-sum/');
  assert.equal(payload.sample_count, 0);
  assert.match(payload.warnings[0], /函数签名提交/);
  assert.match(payload.statement, /^# 1 两数之和/);
  assert.match(payload.statement, /`nums`/);
  assert.match(payload.statement, /\*\*示例 1：\*\*/);
  assert.match(payload.statement, /```text\n输入：nums = \[2,7,11,15\], target = 9/);
  assert.match(payload.statement, /`2 <= nums.length <= 10\^4`/);
});

test('Codeforces fetcher parses official HTML structure and writes statement samples', () => {
  const script = `
import argparse
import json
import re
import sys
import tempfile
from pathlib import Path

sys.path.insert(0, "scripts/problem-analysis-tools")
from fetch_problem import write_fetch_outputs
from fetchers.codeforces import CodeforcesFetcher

fixture = Path("scripts/problem-analysis-tools/tests/fixtures/codeforces_2183a.html").read_text(encoding="utf-8")
fetcher = CodeforcesFetcher()
data = fetcher.parse_html(fixture, "2183A")

no_samples = fetcher.parse_html(fixture.replace('class="sample-test"', 'class="not-a-sample"'), "2183A")
incomplete_html = fixture.replace(
    '<div class="output"><div class="title">Output</div><pre>Alice<br>Bob</pre></div>',
    '<div class="output"><div class="title">Output</div></div>',
)
incomplete = fetcher.parse_html(incomplete_html, "2183A")

class ApiFallbackFetcher(CodeforcesFetcher):
    def http_get(self, url, timeout=15):
        if "/api/problemset.problems" in url:
            return json.dumps({
                "status": "OK",
                "result": {"problems": [{"contestId": 2183, "index": "A", "name": "Binary Array Game"}]},
            })
        return "<html><title>Just a moment...</title></html>"

fallback = ApiFallbackFetcher().fetch("codeforces", "2183A")

with tempfile.TemporaryDirectory() as tmp:
    root = Path(tmp)
    problem_dir = root / "problems" / "codeforces" / "2183A"
    args = argparse.Namespace(
        force_statement=False,
        force_samples=False,
        force_index_meta=False,
        dry_run=False,
    )
    write_fetch_outputs(problem_dir, data, args, repo_root=root)
    files = {
        name: (problem_dir / name).read_text(encoding="utf-8")
        for name in ["problem.md", "in1", "out1", "in"]
    }

print(json.dumps({
    "contest_url": fetcher.parse_url("https://codeforces.com/contest/2183/problem/A"),
    "problemset_url": fetcher.parse_url("https://codeforces.com/problemset/problem/2183/A/"),
    "title": data.title,
    "sample_count": len(data.samples),
    "sample_input": data.samples[0].input,
    "sample_output": data.samples[0].output,
    "statement": data.statement_md,
    "warnings": data.warnings,
    "no_sample_count": len(no_samples.samples),
    "incomplete_count": len(incomplete.samples),
    "incomplete_warnings": incomplete.warnings,
    "fallback_title": fallback.data.title,
    "fallback_fetched": fallback.fetched,
    "fallback_warnings": fallback.warnings,
    "files": files,
}, ensure_ascii=False))
`;
  const result = spawnSync(
    'python3',
    ['-c', script],
    { cwd: process.cwd(), encoding: 'utf8' },
  );

  assert.equal(result.status, 0, result.stderr || result.stdout);
  const payload = JSON.parse(result.stdout.trim());
  assert.deepEqual(payload.contest_url, ['codeforces', '2183A']);
  assert.deepEqual(payload.problemset_url, ['codeforces', '2183A']);
  assert.equal(payload.title, 'Binary Array Game');
  assert.equal(payload.sample_count, 1);
  assert.equal(payload.sample_input, '2\n3\n1 1 0');
  assert.equal(payload.sample_output, 'Alice\nBob');
  assert.deepEqual(payload.warnings, []);
  assert.equal(payload.no_sample_count, 0);
  assert.equal(payload.incomplete_count, 0);
  assert.match(payload.incomplete_warnings[0], /样例 #1 输入输出不完整/);
  assert.equal(payload.fallback_title, 'Binary Array Game');
  assert.equal(payload.fallback_fetched, false);
  assert.match(payload.fallback_warnings[0], /题面\/样例抓取失败/);
  assert.match(payload.statement, /^# 2183A Binary Array Game/);
  assert.match(payload.statement, /- Time limit: 1 second/);
  assert.match(payload.statement, /- Memory limit: 256 megabytes/);
  assert.match(payload.statement, /Alice plays on \$a\$ where \$1 \\le n \\lt 100\$/);
  assert.match(payload.statement, /- Choose a segment\./);
  assert.match(payload.statement, /https:\/\/codeforces\.com\/blog\/entry\/1/);
  assert.match(payload.statement, /!\[icon\]\(https:\/\/codeforces\.com\/images\/icon\.png\)/);
  assert.match(payload.statement, /## 输入格式\n\nThe first line contains \$t\$\./);
  assert.match(payload.statement, /## 说明\n\nIn the first test case, Alice wins\./);
  assert.doesNotMatch(payload.statement, /This content must not be copied/);
  assert.equal(payload.files.in1, '2\n3\n1 1 0');
  assert.equal(payload.files.out1, 'Alice\nBob');
  assert.equal(payload.files.in, payload.files.in1);
  assert.equal(payload.files['problem.md'], payload.statement);
});

test('Kattis fetcher parses original-site HTML fixtures', () => {
  const script = `
import json
import sys
from pathlib import Path

sys.path.insert(0, "scripts/problem-analysis-tools")
from fetchers.kattis import KattisFetcher

fetcher = KattisFetcher()
hello_html = Path("scripts/problem-analysis-tools/tests/fixtures/kattis_hello.html").read_text(encoding="utf-8")
r2_html = Path("scripts/problem-analysis-tools/tests/fixtures/kattis_r2.html").read_text(encoding="utf-8")
hello = fetcher.parse_html(hello_html, "hello")
r2 = fetcher.parse_html(r2_html, "r2")
print(json.dumps({
    "hello": {
        "oj": hello.oj,
        "problem_id": hello.problem_id,
        "problem_dir_id": hello.problem_dir_id,
        "title": hello.title,
        "sample_count": len(hello.samples),
        "statement": hello.statement_md,
    },
    "r2": {
        "title": r2.title,
        "sample_count": len(r2.samples),
        "first_input": r2.samples[0].input,
        "second_output": r2.samples[1].output,
        "statement": r2.statement_md,
    },
}, ensure_ascii=False))
`;
  const result = spawnSync(
    'python3',
    ['-c', script],
    { cwd: process.cwd(), encoding: 'utf8' },
  );

  assert.equal(result.status, 0, result.stderr || result.stdout);
  const payload = JSON.parse(result.stdout.trim());
  assert.equal(payload.hello.oj, 'kattis');
  assert.equal(payload.hello.problem_id, 'hello');
  assert.equal(payload.hello.problem_dir_id, 'hello');
  assert.equal(payload.hello.title, 'Hello World!');
  assert.equal(payload.hello.sample_count, 0);
  assert.match(payload.hello.statement, /^# hello Hello World!/);
  assert.match(payload.hello.statement, /## 输入格式\n\nThere is no input for this problem\./);
  assert.equal(payload.r2.title, 'R2');
  assert.equal(payload.r2.sample_count, 2);
  assert.equal(payload.r2.first_input, '11 15');
  assert.equal(payload.r2.second_output, '2');
  assert.match(payload.r2.statement, /## 题目描述\n\nThe number \$S\$ is called/);
  assert.match(payload.r2.statement, /## 输入输出样例 #2/);
});

test('new-problem URL mode delegates to fetch flow', () => {
  const script = `
import argparse
import importlib.util
import json
from pathlib import Path

url = "https://atcoder.jp/contests/abs/tasks/practice_1"
spec = importlib.util.spec_from_file_location(
    "new_problem_cli",
    Path("scripts/problem-analysis-tools/new-problem.py"),
)
module = importlib.util.module_from_spec(spec)
spec.loader.exec_module(module)

calls = []

def fake_run_fetch(args):
    calls.append({
        "target": args.target,
        "dry_run": args.dry_run,
        "force_statement": args.force_statement,
        "force_samples": args.force_samples,
        "force_index_meta": args.force_index_meta,
    })
    return {
        "oj": "atcoder",
        "problem_id": "practice_1",
        "problem_dir": "problems/atcoder/practice_1",
        "fetched": True,
        "title": "PracticeA - Welcome to AtCoder",
        "source": url,
        "created": [],
        "written": [],
        "skipped": [],
        "warnings": [],
    }

module.run_fetch = fake_run_fetch
status = module.create_problem(argparse.Namespace(
    oj=url,
    problem_id=None,
    title="",
    source="",
    with_brute=True,
    with_gen=True,
    with_workspace=True,
))
print(json.dumps({"status": status, "calls": calls}, ensure_ascii=False))
`;
  const result = spawnSync(
    'python3',
    ['-c', script],
    { cwd: process.cwd(), encoding: 'utf8' },
  );

  assert.equal(result.status, 0, result.stderr || result.stdout);
  const lines = result.stdout.trim().split('\n');
  const payload = JSON.parse(lines.at(-1));
  assert.equal(payload.status, 0);
  assert.deepEqual(payload.calls, [
    {
      target: ['https://atcoder.jp/contests/abs/tasks/practice_1'],
      dry_run: false,
      force_statement: false,
      force_samples: false,
      force_index_meta: false,
    },
  ]);
});

test('check_relations validates external recommend items', () => {
  const fixtureRoot = join(process.cwd(), 'problems', '__tmp_check_recommend__');
  const problemDir = join(fixtureRoot, 'P1');

  try {
    rmSync(fixtureRoot, { recursive: true, force: true });
    writeProblemFixture(problemDir, [
      'oj: "__tmp_check_recommend__"',
      'problem_id: "P1"',
      'title: "Test"',
      'description: "测试推荐练习字段。"',
      'difficulty: "未知"',
      'date: 2026-06-13 10:00',
      'toc: true',
      'tags: []',
      'categories: []',
      'pre: []',
      'common: []',
      'recommend:',
      '  - oj: "leetcode"',
      '    problem_id: "62"',
      '    title: "Unique Paths"',
      '    url: "https://leetcode.com/problems/unique-paths/"',
      '    reason: "同样是基础网格路径计数 DP。"',
      '    relation: "similar"',
      'source:',
    ]);

    const ok = spawnSync(
      'python3',
      ['scripts/problem-analysis-tools/check_relations.py', problemDir],
      { cwd: process.cwd(), encoding: 'utf8' },
    );
    assert.equal(ok.status, 0);
    assert.match(ok.stdout, /通过：关系字段符合当前规范。/);

    writeProblemFixture(problemDir, [
      'oj: "__tmp_check_recommend__"',
      'problem_id: "P1"',
      'title: "Test"',
      'description: "测试推荐练习字段。"',
      'difficulty: "未知"',
      'date: 2026-06-13 10:00',
      'toc: true',
      'tags: []',
      'categories: []',
      'pre: []',
      'common: []',
      'recommend:',
      '  - oj: "leetcode"',
      '    problem_id: "62"',
      '    reason: "同样是基础网格路径计数 DP。"',
      '    relation: "unknown"',
      'source:',
    ]);

    const bad = spawnSync(
      'python3',
      ['scripts/problem-analysis-tools/check_relations.py', problemDir],
      { cwd: process.cwd(), encoding: 'utf8' },
    );
    assert.equal(bad.status, 1);
    assert.match(bad.stdout, /relation=`unknown` 不合法/);
    assert.match(bad.stdout, /缺少 `url`/);
  } finally {
    rmSync(fixtureRoot, { recursive: true, force: true });
  }
});

test('navi fetch-url prompts for URL instead of using a fixed default', () => {
  const cheat = readFileSync('scripts/navi/problem-tools.cheat', 'utf8');
  const lines = cheat.split('\n');
  const start = lines.findIndex((line) => line === '% fetch-url');
  const end = lines.findIndex((line, index) => index > start && line.startsWith('% '));
  const block = lines.slice(start, end === -1 ? undefined : end).join('\n');

  assert.notEqual(start, -1);
  assert.match(block, /fetch_problem <problem_url>/);
  assert.doesNotMatch(block, /^\$ problem_url:/m);
});
