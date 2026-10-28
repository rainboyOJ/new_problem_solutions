import test from 'node:test';
import assert from 'node:assert/strict';
import { execFileSync, spawnSync } from 'node:child_process';
import { existsSync, mkdirSync, mkdtempSync, readFileSync, rmSync, writeFileSync } from 'node:fs';
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
    'updated: 2026-06-13 10:00',
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
      'updated: 2026-07-09 18:30',
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
      'updated: 2026-07-09 18:40',
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
    assert.equal(existsSync(join(problemDir, 'talking_with_ai')), true);
    assert.match(result.stdout, /talking_with_ai/);
    const indexMd = readFileSync(join(problemDir, 'index.md'), 'utf8');
    assert.match(indexMd, /title: "Test"\ndescription: ""\ndifficulty: "未知"\ndate: \d{4}-\d{2}-\d{2} \d{2}:\d{2}\nupdated: \d{4}-\d{2}-\d{2} \d{2}:\d{2}\n/);
    assert.match(indexMd, /tags: \[\]\nfavorite: false\nfavorite_reason: ""\ncategories: \[\]\nshowAtRbook: \[\]\npre: \[\]\ncommon: \[\]\nrecommend: \[\]\nsource:/);
    assert.match(indexMd, /正文布局尚未确定/);
    assert.match(indexMd, /直接正解型、暴力到正解型、并列多解法型、子任务递进型/);
    assert.doesNotMatch(indexMd, /^## 思路$/m);
    assert.doesNotMatch(indexMd, /^## 代码$/m);
    assert.match(result.stdout, /index\.md 只是布局待判定的临时骨架/);
  } finally {
    rmSync(fixtureRoot, { recursive: true, force: true });
  }
});


test('fetch_problem --force-index-meta only touches top-level scalars', () => {
  const script = `
import json
import sys
import tempfile
import textwrap
from pathlib import Path

sys.path.insert(0, "scripts/problem-analysis-tools")
import fetch_problem
from fetchers.base import ProblemData

original = textwrap.dedent('''\\
---
oj: "codeforces"
problem_id: "19D"
title: "Points"
description: "旧描述"
difficulty: "提高+"
date: 2026-07-14 23:50
updated: 2026-10-07 10:45
toc: true
tags: ["线段树"]
categories: []
pre:
  - oj: "roj"
    problem_id: "3119"
    reason: "复用 bit_kth"
common: []
recommend: []
source: https://codeforces.com/problemset/problem/19/D
---

[[TOC]]

正文不该被改。
''')

data = ProblemData(
    oj="codeforces",
    problem_id="19D",
    problem_dir_id="19D",
    source="https://vjudge.net/problem/CodeForces-19D#author=translator:1281311:zh",
    title="Points",
    difficulty="提高+",
)

with tempfile.TemporaryDirectory() as tmp:
    index = Path(tmp) / "index.md"
    index.write_text(original, encoding="utf-8")
    changed = fetch_problem.update_index_meta(index, data, dry_run=False)
    updated = index.read_text(encoding="utf-8")
    # 第二次跑：值已经一致，不应再算改动
    again = fetch_problem.update_index_meta(index, data, dry_run=False)
    unchanged_text = index.read_text(encoding="utf-8")

print(json.dumps({
    "changed": changed,
    "again": again,
    "updated": updated,
    "same_after_second_run": unchanged_text == updated,
}, ensure_ascii=False))
`;
  const result = spawnSync('python3', ['-c', script], {
    cwd: process.cwd(),
    encoding: 'utf8',
  });

  assert.equal(result.status, 0, result.stderr || result.stdout);
  const payload = JSON.parse(result.stdout.trim());
  const text = payload.updated;

  assert.equal(payload.changed, true);
  assert.equal(payload.again, false);
  assert.equal(payload.same_after_second_run, true);
  // 嵌套列表和顶层 problem_id 都不能被碰
  assert.match(text, /^problem_id: "19D"$/m);
  assert.match(text, /^pre:\n  - oj: "roj"\n    problem_id: "3119"\n    reason: "复用 bit_kth"$/m);
  assert.match(text, /^source: "https:\/\/vjudge\.net\/problem\/CodeForces-19D#author=translator:1281311:zh"$/m);
  assert.match(text, /^difficulty: "提高\+"$/m);
  assert.match(text, /正文不该被改。/);
  // 顶层 problem_id 不能被列表里的同名字段顶掉
  assert.equal((text.match(/^problem_id:/gm) || []).length, 1);
});

test('fetch_problem always quotes fetched string metadata in frontmatter', () => {
  const script = `
import tempfile
from pathlib import Path
import sys

sys.path.insert(0, "scripts/problem-analysis-tools")
from fetch_problem import update_index_meta
from fetchers.base import ProblemData

with tempfile.TemporaryDirectory() as tmp:
    index_path = Path(tmp) / "index.md"
    index_path.write_text("---\\ntitle: \\\"\\\"\\ndifficulty: \\\"未知\\\"\\ndate: 2026-07-15 17:50\\nupdated: 2026-08-14 16:33\\nsource: \\\"\\\"\\n---\\n\\n正文\\n", encoding="utf-8")
    data = ProblemData(
        oj="luogu",
        problem_id="P4036",
        problem_dir_id="P4036",
        title="[JSOI2008] 火星人",
        difficulty="省选/NOI-",
        source="https://www.luogu.com.cn/problem/P4036",
    )
    first_changed = update_index_meta(index_path, data, dry_run=False)
    second_changed = update_index_meta(index_path, data, dry_run=False)
    print(first_changed, second_changed)
    print(index_path.read_text(encoding="utf-8"), end="")
`;
  const result = spawnSync('python3', ['-c', script], {
    cwd: process.cwd(), encoding: 'utf8',
  });

  assert.equal(result.status, 0, result.stderr || result.stdout);
  assert.match(result.stdout, /^True False$/m);
  assert.match(result.stdout, /^title: "\[JSOI2008\] 火星人"$/m);
  assert.match(result.stdout, /^difficulty: "省选\/NOI-"$/m);
  assert.match(result.stdout, /^date: 2026-07-15 17:50$\n^updated: 2026-08-14 16:33$/m);
  assert.match(result.stdout, /^source: "https:\/\/www\.luogu\.com\.cn\/problem\/P4036"$/m);
});

function writeLayoutFixture(problemDir, body, extraFiles = {}) {
  mkdirSync(problemDir, { recursive: true });
  writeFileSync(join(problemDir, 'main.cpp'), 'int main() { return 0; }\n');
  for (const [name, content] of Object.entries(extraFiles)) {
    writeFileSync(join(problemDir, name), content);
  }
  writeFileSync(join(problemDir, 'index.md'), [
    '---',
    'oj: "__tmp_check_layouts__"',
    'problem_id: "P1"',
    'title: "Test"',
    'description: "测试题解正文布局。"',
    'difficulty: "普及-"',
    'date: 2026-09-07 10:00',
    'updated: 2026-09-07 10:00',
    'toc: true',
    'tags: []',
    'categories: []',
    'source:',
    '---',
    '',
    '[[TOC]]',
    '',
    body,
    '',
  ].join('\n'));
}

test('check_problem accepts all four structured article layouts', () => {
  const fixtureRoot = join(process.cwd(), 'problems', '__tmp_check_layouts__');
  const problemDir = join(fixtureRoot, 'P1');
  const layouts = [
    [
      'direct',
      [
        '## 形式化题目',
        '',
        '## 正解',
        '',
        '### 思路',
        '',
        '### 代码',
        '',
        '@include-code(./main.cpp, cpp)',
        '',
        '### 复杂度',
        '',
        '## 总结',
      ].join('\n'),
      {},
    ],
    [
      'brute-final',
      [
        '## 形式化题目',
        '',
        '## 暴力解法',
        '',
        '### 思路',
        '',
        '### 代码',
        '',
        '@include-code(./brute.cpp, cpp)',
        '',
        '### 复杂度',
        '',
        '### 瓶颈',
        '',
        '## 正解',
        '',
        '### 思路',
        '',
        '### 代码',
        '',
        '@include-code(./main.cpp, cpp)',
        '',
        '### 复杂度',
        '',
        '## 总结',
      ].join('\n'),
      { 'brute.cpp': 'int main() { return 0; }\n' },
    ],
    [
      'parallel',
      [
        '## 形式化题目',
        '',
        '## 解法总览',
        '',
        '正式主解是解法二，对应 main.cpp。',
        '',
        '## 解法一：枚举',
        '',
        '### 思路',
        '',
        '### 代码',
        '',
        '不单独给出，重点是对比思路。',
        '',
        '### 复杂度',
        '',
        '## 解法二：优化',
        '',
        '### 思路',
        '',
        '### 代码',
        '',
        '@include-code(./main.cpp, cpp)',
        '',
        '### 复杂度',
        '',
        '## 总结',
      ].join('\n'),
      {},
    ],
    [
      'subtask',
      [
        '## 形式化题目',
        '',
        '## 解法路线',
        '',
        '从小范围枚举推进到正式主解 main.cpp。',
        '',
        '## 暴力解法',
        '',
        '### 适用范围',
        '',
        '### 思路',
        '',
        '### 代码',
        '',
        '@include-code(./brute.cpp, cpp)',
        '',
        '### 复杂度与瓶颈',
        '',
        '## 子任务解法：$k \leqslant 4$',
        '',
        '### 适用范围',
        '',
        '### 思路',
        '',
        '### 代码',
        '',
        '不单独给出，和暴力解法共用实现。',
        '',
        '### 复杂度与瓶颈',
        '',
        '## 正解',
        '',
        '### 关键观察',
        '',
        '### 思路',
        '',
        '### 代码',
        '',
        '@include-code(./main.cpp, cpp)',
        '',
        '### 复杂度',
        '',
        '## 总结',
      ].join('\n'),
      { 'brute.cpp': 'int main() { return 0; }\n' },
    ],
  ];

  try {
    for (const [name, body, extraFiles] of layouts) {
      rmSync(fixtureRoot, { recursive: true, force: true });
      writeLayoutFixture(problemDir, body, extraFiles);
      const result = spawnSync(
        'python3',
        ['scripts/problem-analysis-tools/check_problem.py', problemDir],
        { cwd: process.cwd(), encoding: 'utf8' },
      );
      assert.equal(result.status, 0, `${name}:\n${result.stdout}\n${result.stderr}`);
    }
  } finally {
    rmSync(fixtureRoot, { recursive: true, force: true });
  }
});

test('check_problem rejects malformed progressive layout', () => {
  const fixtureRoot = join(process.cwd(), 'problems', '__tmp_check_layouts__');
  const problemDir = join(fixtureRoot, 'P1');
  const body = [
    '## 形式化题目',
    '',
    '## 子任务解法：$k \leqslant 4$',
    '',
    '### 思路',
    '',
    '## 正解',
    '',
    '### 思路',
    '',
    '### 代码',
    '',
    '@include-code(./main.cpp, cpp)',
    '',
    '### 复杂度',
    '',
    '## 总结',
  ].join('\n');

  try {
    rmSync(fixtureRoot, { recursive: true, force: true });
    writeLayoutFixture(problemDir, body);
    const result = spawnSync(
      'python3',
      ['scripts/problem-analysis-tools/check_problem.py', problemDir],
      { cwd: process.cwd(), encoding: 'utf8' },
    );
    assert.equal(result.status, 1, result.stdout);
    assert.match(result.stdout, /子任务递进布局缺少 ## 解法路线/);
    assert.match(result.stdout, /子任务解法：\$k \leqslant 4\$ 缺少 ### 代码 小节/);
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
    'updated: 2026-07-20 10:00',
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
      ...baseFrontmatter.slice(0, 9),
      'favorite: "true"',
      ...baseFrontmatter.slice(10),
    ]);
    const invalidFavorite = spawnSync(
      'python3',
      ['scripts/problem-analysis-tools/check_problem.py', problemDir],
      { cwd: process.cwd(), encoding: 'utf8' },
    );
    assert.equal(invalidFavorite.status, 1);
    assert.match(invalidFavorite.stdout, /favorite 必须是布尔值 true 或 false/);

    writeProblemFixture(problemDir, [
      ...baseFrontmatter.slice(0, 10),
      'favorite_reason: 123',
      ...baseFrontmatter.slice(11),
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

test('check_problem requires updated and validates its timestamp format', () => {
  const fixtureRoot = join(process.cwd(), 'problems', '__tmp_check_updated__');
  const problemDir = join(fixtureRoot, 'P1');
  const baseFrontmatter = [
    'oj: "__tmp_check_updated__"',
    'problem_id: "P1"',
    'title: "Test"',
    'description: "测试 updated 字段的必填与格式。"',
    'difficulty: "入门"',
    'date: 2026-08-14 16:33',
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
    assert.match(missing.stdout, /frontmatter 缺少字段：updated/);

    writeProblemFixture(problemDir, [
      ...baseFrontmatter.slice(0, 6),
      'updated: 2026/08/14',
      ...baseFrontmatter.slice(6),
    ]);
    const malformed = spawnSync(
      'python3',
      ['scripts/problem-analysis-tools/check_problem.py', problemDir],
      { cwd: process.cwd(), encoding: 'utf8' },
    );
    assert.equal(malformed.status, 1);
    assert.match(malformed.stdout, /updated 格式应为 YYYY-MM-DD HH:MM/);
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
    "slug_from_digit_slug": fetcher.resolve_slug("3sum"),
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
  assert.equal(payload.slug_from_digit_slug, '3sum');
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
from fetchers.base import FetchError
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

class UnreachableVJudgeClient:
    """离线假客户端：VJudge 上确认不到该题，走原站回退。"""

    def problem_info(self, oj, prob_num):
        raise FetchError("VJudge 请求失败")

    def desc_briefs(self, oj, prob_num):
        raise FetchError("VJudge 请求失败")

    def description(self, key):
        raise FetchError("VJudge 请求失败")


class ApiFallbackFetcher(CodeforcesFetcher):
    def http_get(self, url, timeout=15):
        if "/api/problemset.problems" in url:
            return json.dumps({
                "status": "OK",
                "result": {"problems": [{"contestId": 2183, "index": "A", "name": "Binary Array Game"}]},
            })
        return "<html><title>Just a moment...</title></html>"

fallback = ApiFallbackFetcher(client=UnreachableVJudgeClient()).fetch("codeforces", "2183A")

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
    "fallback_source": fallback.data.source,
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
  assert.equal(payload.fallback_source, 'https://codeforces.com/contest/2183/problem/A');
  assert.ok(payload.fallback_warnings.some(msg => /VJudge 未确认到该题/.test(msg)));
  assert.ok(payload.fallback_warnings.some(msg => /题面\/样例抓取失败/.test(msg)));
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

test('Codeforces fetcher prefers VJudge Chinese statement and keeps the VJudge link', () => {
  const script = `
import json
import sys
from pathlib import Path

sys.path.insert(0, "scripts/problem-analysis-tools")
from fetchers.base import FetchError
from fetchers.codeforces import CodeforcesFetcher
from fetchers.vjudge_client import DescBrief, Description

fixture = Path("scripts/problem-analysis-tools/tests/fixtures/codeforces_2183a.html").read_text(encoding="utf-8")


class FakeVJudgeClient:
    """离线假客户端：模拟 VJudge 的 info / descBriefs / description 三层。"""

    def __init__(self):
        self.requested = []

    def problem_info(self, oj, prob_num):
        return "4164979", "Binary Array Game"

    def desc_briefs(self, oj, prob_num):
        return [
            DescBrief("enkey", "en", "System", "2026-01-08", True, True, "Initialization.", "main"),
            DescBrief("zhkey", "zh", "GPT", "2026-01-07", False, False, "translated", "translator:1281309:zh"),
        ]

    def description(self, key):
        self.requested.append(key)
        if key == "zhkey":
            # VJudge 上的 Codeforces 题面：第一条小节标题为空，公式是 $$$..$$$，
            # 样例输出每行一个 div（换行只在标签结构里）。
            return Description("zhkey", "zh", True, [
                ("", "<p>中文题面，数组 $$$a$$$ 长度 $$$1 \\\\le n \\\\le 100$$$。</p>"),
                ("输入格式", "<p>第一行 $$$t$$$。</p>"),
                ("输出格式", "<p>输出 Alice 或 Bob。</p>"),
                ("样例", "<table class='vjudge_sample'><thead><tr><th>Input</th><th>Output</th></tr></thead>"
                         "<tbody><tr><td><pre>3\\n1 1 0</pre></td><td><pre>"
                         "<div class=\\"test-example-line test-example-line-odd test-example-line-1\\">Alice</div>"
                         "<div class=\\"test-example-line test-example-line-even test-example-line-2\\">Bob</div>"
                         "</pre></td></tr></tbody></table>"),
            ])
        return Description("enkey", "en", True, [
            ("Problem Statement", "<p>English statement.</p>"),
            ("Examples", "<table class='vjudge_sample'><thead><tr><th>Input</th><th>Output</th></tr></thead>"
                        "<tbody><tr><td><pre>9</pre></td><td><pre>9</pre></td></tr></tbody></table>"),
        ])


class LoginBrokenClient(FakeVJudgeClient):
    """题目在 VJudge 上，但题面需要登录且登录态失效。"""

    def desc_briefs(self, oj, prob_num):
        raise FetchError("VJudge 需要登录：https://vjudge.net/?login=1")


class MissingClient(FakeVJudgeClient):
    """VJudge 上没有这道题。"""

    def problem_info(self, oj, prob_num):
        raise FetchError("VJudge 上找不到题目")


class SiteFetcher(CodeforcesFetcher):
    def __init__(self, client):
        super().__init__(client=client)
        self.requested_urls = []

    def http_get(self, url, timeout=15):
        self.requested_urls.append(url)
        return fixture


vjudge_result = CodeforcesFetcher(client=FakeVJudgeClient()).fetch("codeforces", "2183A")
vjudge_data = vjudge_result.data

login_broken_fetcher = SiteFetcher(LoginBrokenClient())
login_broken = login_broken_fetcher.fetch("codeforces", "2183A")

missing_fetcher = SiteFetcher(MissingClient())
missing = missing_fetcher.fetch("codeforces", "2183A")

print(json.dumps({
    "fetched": vjudge_result.fetched,
    "title": vjudge_data.title,
    "source": vjudge_data.source,
    "problem_id": vjudge_data.problem_id,
    "problem_dir_id": vjudge_data.problem_dir_id,
    "sample_count": len(vjudge_data.samples),
    "sample_input": vjudge_data.samples[0].input,
    "sample_output": vjudge_data.samples[0].output,
    "statement": vjudge_data.statement_md,
    "warnings": vjudge_data.warnings,
    "vjudge_link": CodeforcesFetcher().problem_link("2183A"),
    "official_link": CodeforcesFetcher().official_link("2183A"),
    "vjudge_url_parse": CodeforcesFetcher().parse_url("https://vjudge.net/problem/CodeForces-2183A"),
    "oj_other_url_match": [
        candidate.match_url("https://vjudge.net/problem/POJ-1000")
        for candidate in __import__("fetchers").FETCHERS
        if isinstance(candidate, CodeforcesFetcher)
    ][0],
    "codeforces_url_parse": CodeforcesFetcher().parse_url("https://codeforces.com/contest/2183/problem/A"),
    "login_broken_fetched": login_broken.fetched,
    "login_broken_source": login_broken.data.source,
    "login_broken_title": login_broken.data.title,
    "login_broken_warnings": login_broken.warnings,
    "login_broken_urls": login_broken_fetcher.requested_urls,
    "missing_source": missing.data.source,
    "missing_fetched": missing.fetched,
    "missing_warnings": missing.warnings,
    "missing_urls": missing_fetcher.requested_urls,
}, ensure_ascii=False))
`;
  const result = spawnSync('python3', ['-c', script], {
    cwd: process.cwd(),
    encoding: 'utf8',
  });

  assert.equal(result.status, 0, result.stderr || result.stdout);
  const payload = JSON.parse(result.stdout.trim());

  // VJudge 命中：中文题面 + 跳转链接指向 VJudge
  assert.equal(payload.fetched, true);
  assert.equal(payload.title, 'Binary Array Game');
  assert.equal(payload.source, 'https://vjudge.net/problem/CodeForces-2183A#author=translator:1281309:zh');
  assert.equal(payload.problem_id, '2183A');
  assert.equal(payload.problem_dir_id, '2183A');
  assert.match(payload.warnings[0], /中文题面/);
  assert.match(payload.warnings[0], /trustable/);

  // $$$ 公式与 test-example-line 样例
  assert.match(payload.statement, /^# 2183A Binary Array Game/);
  assert.match(payload.statement, /## 题目描述\n\n中文题面，数组 \$a\$ 长度 \$1 \\le n \\le 100\$/);
  assert.doesNotMatch(payload.statement, /\$\$\$/);
  assert.equal(payload.sample_count, 1);
  assert.equal(payload.sample_input, '3\n1 1 0');
  assert.equal(payload.sample_output, 'Alice\nBob');

  // 链接工具
  assert.equal(payload.vjudge_link, 'https://vjudge.net/problem/CodeForces-2183A');
  assert.equal(payload.official_link, 'https://codeforces.com/contest/2183/problem/A');
  assert.deepEqual(payload.vjudge_url_parse, ['codeforces', '2183A']);
  assert.deepEqual(payload.codeforces_url_parse, ['codeforces', '2183A']);
  // 不能抢走 VJudge 上其它 OJ 的 URL
  assert.equal(payload.oj_other_url_match, false);

  // 登录态失效：仍指向 VJudge，但题面回退原站
  assert.equal(payload.login_broken_fetched, true);
  assert.equal(payload.login_broken_title, 'Binary Array Game');
  assert.equal(payload.login_broken_source, 'https://vjudge.net/problem/CodeForces-2183A');
  assert.deepEqual(payload.login_broken_urls, ['https://codeforces.com/contest/2183/problem/A']);
  assert.ok(payload.login_broken_warnings.some(msg => /回退 Codeforces 原站/.test(msg)));
  assert.match(payload.login_broken_warnings.join('\n'), /需要登录/);

  // VJudge 未收录：跳转链接退回原站
  assert.equal(payload.missing_fetched, true);
  assert.equal(payload.missing_source, 'https://codeforces.com/contest/2183/problem/A');
  assert.ok(payload.missing_warnings.some(msg => /未确认到该题/.test(msg)));
});


test('VJudge client falls back to browser login and saves the refreshed cookie', () => {
  const script = `
import json
import sys
import tempfile
from pathlib import Path

sys.path.insert(0, "scripts/problem-analysis-tools")
import fetchers.vjudge_client as vjc
from fetchers.base import FetchError

tmp = Path(tempfile.mkdtemp())
# 别碰真实凭据文件：save_cookie 读的是模块级 CONFIG_PATH。
vjc.CONFIG_PATH = tmp / "vjudge.json"

calls = []
creds = []

def fake_browser_login(reason="", username="", password=""):
    calls.append(reason)
    creds.append((username, password))
    return "JSESSIONID=abc123; JSESSlONID=def456"


# 1) 没有账号密码 → 账号密码登录不可用 → 走浏览器登录
class BlockedClient(vjc.VJudgeClient):
    def _password_login(self):
        raise vjc.LoginBlocked("VJudge 登录要求人机验证（Cloudflare Turnstile），账号密码登录走不通")


client = vjc.VJudgeClient(config={}, browser_login=fake_browser_login)
client._login()

# 有账号密码时，凭据要传给浏览器登录（Camoufox 自动填表要用）
with_creds = BlockedClient(
    config={"username": "rainboy", "password": "s3cret"}, browser_login=fake_browser_login
)
with_creds._login()

# 2) 密码登录被人机验证拦住 → 同样走浏览器登录
blocked = BlockedClient(config={"username": "u", "password": "p"}, browser_login=fake_browser_login)
blocked._login()

# 3) 不允许浏览器登录时必须报错，并且提示 --vjudge-login
class DeniedClient(vjc.VJudgeClient):
    def _password_login(self):
        raise vjc.LoginBlocked("VJudge 登录要求人机验证")


denied = DeniedClient(config={})
try:
    denied._login()
    denied_outcome = "no_error"
except FetchError as exc:
    denied_outcome = "error"
    denied_message = str(exc)

print(json.dumps({
    "logged_in": client._logged_in,
    "exported": client._export_cookie(),
    "saved": (tmp / "vjudge.json").read_text(encoding="utf-8"),
    "blocked_logged_in": blocked._logged_in,
    "blocked_exported": blocked._export_cookie(),
    "calls": calls,
    "creds": creds,
    "with_creds_logged_in": with_creds._logged_in,
    "denied_outcome": denied_outcome,
    "denied_message": denied_message,
}, ensure_ascii=False))
`;
  const result = spawnSync('python3', ['-c', script], {
    cwd: process.cwd(),
    encoding: 'utf8',
    env: { ...process.env, VJUDGE_BROWSER_LOGIN: '' },
  });

  assert.equal(result.status, 0, result.stderr || result.stdout);
  const payload = JSON.parse(result.stdout.trim());

  assert.equal(payload.logged_in, true);
  assert.match(payload.exported, /JSESSIONID=abc123/);
  assert.match(payload.exported, /JSESSlONID=def456/);
  assert.match(payload.saved, /JSESSIONID=abc123/);
  assert.equal(payload.blocked_logged_in, true);
  assert.match(payload.blocked_exported, /JSESSIONID=abc123/);
  assert.equal(payload.calls.length, 3);
  // reason 要说清为什么需要人工登录
  assert.match(payload.calls[0], /没有账号密码|登录态已失效/);
  assert.match(payload.calls[1], /人机验证/);
  assert.equal(payload.with_creds_logged_in, true);
  assert.deepEqual(payload.creds[1], ['rainboy', 's3cret']);
  assert.equal(payload.denied_outcome, 'error');
  assert.match(payload.denied_message, /--vjudge-login/);
  assert.match(payload.denied_message, /vjudge\.json/);
});


test('VJudge browser login picks the Camoufox backend and falls back to Chromium', () => {
  const script = `
import json
import sys

sys.path.insert(0, "scripts/problem-analysis-tools")
import fetchers.vjudge_browser_login as vbl


class Recorder:
    def __init__(self, boom=None):
        self.calls = []
        self.boom = boom

    def __call__(self, **kwargs):
        self.calls.append(kwargs)
        if self.boom:
            raise self.boom
        return "JSESSIONID=camo; JSESSlONID=camo2"


camo = Recorder()
chrome = Recorder()

saved_camoufox = vbl.camoufox_login
saved_chromium = vbl.chromium_login
vbl.camoufox_login = camo
vbl.chromium_login = chrome

out = {}

# 1) 默认 auto：有账号密码时先走 Camoufox，成功就不再开窗口
out["auto_cookie"] = vbl.browser_login(reason="需要中文题面", username="u", password="p")
out["auto_camo_calls"] = len(camo.calls)
out["auto_chrome_calls"] = len(chrome.calls)
out["auto_username"] = camo.calls[0]["username"]

# 2) Camoufox 失败 → 回退 Chromium（并把凭据带过去预填）
camo.boom = vbl.FetchError("没有找到带 camoufox 的 Python 解释器")
chrome.calls.clear(); camo.calls.clear()
out["fallback_cookie"] = vbl.browser_login(username="u", password="p")
out["fallback_camo_calls"] = len(camo.calls)
out["fallback_chrome_calls"] = len(chrome.calls)
out["fallback_chrome_username"] = chrome.calls[0]["username"]

# 3) 没有账号密码 → 直接人工登录
chrome.calls.clear(); camo.calls.clear()
out["no_creds_cookie"] = vbl.browser_login()
out["no_creds_camo_calls"] = len(camo.calls)

# 4) 显式 VJUDGE_BROWSER=chromium
import os
os.environ["VJUDGE_BROWSER"] = "chromium"
chrome.calls.clear(); camo.calls.clear()
out["chromium_cookie"] = vbl.browser_login(username="u", password="p")
out["chromium_camo_calls"] = len(camo.calls)
del os.environ["VJUDGE_BROWSER"]

vbl.camoufox_login = saved_camoufox
vbl.chromium_login = saved_chromium

# 5) 没有 camoufox 解释器时给出安装提示（离线，不启动浏览器）
out["camoufox_python_when_missing"] = None
if vbl.camoufox_python() is None:
    try:
        vbl.camoufox_login(username="u", password="p", timeout=1, log=lambda m: None)
        out["missing_message"] = ""
    except vbl.FetchError as exc:
        out["missing_message"] = str(exc)
else:
    out["missing_message"] = "(本机装了 camoufox，跳过这项)"

print(json.dumps(out, ensure_ascii=False))
`;
  const result = spawnSync('python3', ['-c', script], {
    cwd: process.cwd(),
    encoding: 'utf8',
  });

  assert.equal(result.status, 0, result.stderr || result.stdout);
  const payload = JSON.parse(result.stdout.trim());

  assert.equal(payload.auto_cookie, 'JSESSIONID=camo; JSESSlONID=camo2');
  assert.equal(payload.auto_camo_calls, 1);
  assert.equal(payload.auto_chrome_calls, 0);
  assert.equal(payload.auto_username, 'u');

  assert.equal(payload.fallback_cookie, 'JSESSIONID=camo; JSESSlONID=camo2');
  assert.equal(payload.fallback_camo_calls, 1);
  assert.equal(payload.fallback_chrome_calls, 1);
  assert.equal(payload.fallback_chrome_username, 'u');

  assert.equal(payload.no_creds_camo_calls, 0);
  assert.equal(payload.chromium_camo_calls, 0);
  assert.equal(payload.chromium_cookie, 'JSESSIONID=camo; JSESSlONID=camo2');
  assert.ok(
    payload.missing_message === '' || /camoufox/.test(payload.missing_message),
    payload.missing_message,
  );
});

test('fetch_problem --vjudge-login refreshes the cookie before fetching', () => {
  const script = `
import json
import sys
import tempfile
from pathlib import Path
from types import SimpleNamespace

sys.path.insert(0, "scripts/problem-analysis-tools")
import fetch_problem
import fetchers
from fetchers.codeforces import CodeforcesFetcher
from fetchers.vjudge_client import DescBrief, Description

fixture = Path("scripts/problem-analysis-tools/tests/fixtures/codeforces_2183a.html").read_text(encoding="utf-8")
login_calls = []


def fake_login_with_browser(reason=""):
    login_calls.append(reason)
    return "JSESSIONID=fake; JSESSlONID=fake2"


class FakeClient:
    def problem_info(self, oj, prob_num):
        return "4164979", "Binary Array Game"

    def desc_briefs(self, oj, prob_num):
        return [DescBrief("zhkey", "zh", "GPT", "2026-01-07", False, False, "", "translator:1281309:zh")]

    def description(self, key):
        return Description(key, "zh", True, [
            ("", "<p>中文题面 $$$n$$$。</p>"),
            ("样例", "<table class='vjudge_sample'><thead><tr><th>I</th><th>O</th></tr></thead>"
                    "<tbody><tr><td><pre>1 2</pre></td><td><pre>3</pre></td></tr></tbody></table>"),
        ])


fetch_problem.login_with_browser = fake_login_with_browser

for candidate in fetchers.FETCHERS:
    if isinstance(candidate, CodeforcesFetcher):
        candidate._client = FakeClient()

args = SimpleNamespace(
    target=["codeforces", "2183A"],
    dry_run=True,
    vjudge_login=True,
    force_statement=False,
    force_samples=False,
    force_index_meta=False,
)
with tempfile.TemporaryDirectory() as tmp:
    root = Path(tmp)
    payload = fetch_problem.run_fetch(args, repo_root=root, problems_root=root / "problems")

no_login_args = SimpleNamespace(
    target=["codeforces", "2183A"],
    dry_run=True,
    vjudge_login=False,
    force_statement=False,
    force_samples=False,
    force_index_meta=False,
)
with tempfile.TemporaryDirectory() as tmp2:
    root2 = Path(tmp2)
    no_login = fetch_problem.run_fetch(no_login_args, repo_root=root2, problems_root=root2 / "problems")

print(json.dumps({
    "login_calls": login_calls,
    "warnings": payload["warnings"],
    "source": payload["source"],
    "fetched": payload["fetched"],
    "no_login_warnings": no_login["warnings"],
    "no_login_source": no_login["source"],
}, ensure_ascii=False))
`;
  const result = spawnSync('python3', ['-c', script], {
    cwd: process.cwd(),
    encoding: 'utf8',
  });

  assert.equal(result.status, 0, result.stderr || result.stdout);
  const payload = JSON.parse(result.stdout.trim());

  assert.equal(payload.login_calls.length, 1);
  assert.match(payload.login_calls[0], /--vjudge-login/);
  assert.match(payload.warnings[0], /已通过浏览器登录 VJudge/);
  assert.equal(payload.fetched, true);
  assert.equal(payload.source, 'https://vjudge.net/problem/CodeForces-2183A#author=translator:1281309:zh');
  // 不带 flag 时不触发浏览器登录
  assert.ok(!payload.no_login_warnings.some(msg => /浏览器登录/.test(msg)));
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
      'updated: 2026-06-13 10:00',
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
      'updated: 2026-06-13 10:00',
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

test('AtCoder fetcher routes through VJudge and prefers Chinese statements', () => {
  const script = `
import json
import sys

sys.path.insert(0, "scripts/problem-analysis-tools")
from fetchers.atcoder import AtCoderFetcher
from fetchers.vjudge_client import DescBrief, Description
from fetchers.vjudge_statement import build_statement


class FakeClient:
    """离线假客户端：模拟 VJudge 的 info / descBriefs / description 三层。"""

    def __init__(self):
        self.requested = []

    def problem_info(self, oj, prob_num):
        return "4192630", "Binary Search on a Segment Tree"

    def desc_briefs(self, oj, prob_num):
        return [
            DescBrief("111", "en", "System", "2026-10-13", True, True, "Initialization."),
            DescBrief("222", "ja", "System", "2026-10-13", True, False, "Initialization."),
            DescBrief("333", "zh", "GPT", "2026-10-14", False, False, "translated"),
            DescBrief.from_payload({"key": "444", "lang": "zh", "author": "DeepSeek", "authorKey": "translator:1281309:zh"}),
        ]

    def description(self, key):
        if key not in self.requested:
            self.requested.append(key)
        if key == "333":
            # 没有 trustable 的中文版
            return Description("333", "zh", False, [
                ("题目描述", "<p>中文题面 <var>\\\\(N\\\\)</var>。</p>"),
                ("样例 1", "<table class='vjudge_sample'><thead><tr><th>Input</th>"
                          "<th>Output</th></tr></thead><tbody><tr><td><pre>3</pre></td>"
                          "<td><pre>6</pre></td></tr></tbody></table>"),
            ])
        if key == "444":
            # trustable 的中文版，且带样例与样例说明
            return Description("444", "zh", True, [
                ("题目描述", "<p>信任的中文题面 <var>\\\\(N\\\\)</var>。</p>"),
                ("约束条件", "<ul><li><var>\\\\(1 \\\\le N\\\\)</var></li></ul>"),
                ("输入格式", "<pre><var>\\\\(N\\\\)</var></pre>"),
                ("输出格式", "<p>输出答案。</p>"),
                ("样例 1", "<table class='vjudge_sample'><thead><tr><th>Input</th>"
                          "<th>Output</th></tr></thead><tbody><tr><td><pre>3\\n1 2 3</pre></td>"
                          "<td><pre>6</pre></td></tr></tbody></table>"
                          "<section></section><section><p>样例说明段落 <var>\\\\(A_1\\\\)</var>。</p></section>"),
            ])
        if key == "111":
            return Description("111", "en", True, [
                ("Problem Statement", "<p>English statement.</p>"),
                ("Sample 1", "<table class='vjudge_sample'><thead><tr><th>Input</th>"
                            "<th>Output</th></tr></thead><tbody><tr><td><pre>9</pre></td>"
                            "<td><pre>9</pre></td></tr></tbody></table>"),
            ])
        raise AssertionError("unexpected key " + key)


client = FakeClient()
fetcher = AtCoderFetcher(client=client)
result = fetcher.fetch("atcoder", "aalc001_c")
data = result.data

single = AtCoderFetcher(client=FakeClient()).fetch("atcoder", "aalc001_c").data
dashed = AtCoderFetcher(client=FakeClient()).fetch("atcoder", "aalc001/aalc001_c").data

class MissingAuthorKeyClient(FakeClient):
    def desc_briefs(self, oj, prob_num):
        from dataclasses import replace
        return [replace(b, author_key="") for b in super().desc_briefs(oj, prob_num)]

missing_key = AtCoderFetcher(client=MissingAuthorKeyClient()).fetch("atcoder", "aalc001_c").data

print(json.dumps({
    "fetched": result.fetched,
    "title": data.title,
    "problem_id": data.problem_id,
    "problem_dir_id": data.problem_dir_id,
    "source": data.source,
    "sample_count": len(data.samples),
    "sample_input": data.samples[0].input,
    "sample_output": data.samples[0].output,
    "statement": data.statement_md,
    "warnings": data.warnings,
    "requested": client.requested,
    "single_dir": single.problem_dir_id,
    "dashed_dir": dashed.problem_dir_id,
    "same_source": single.source == dashed.source,
    "missing_key_source": missing_key.source,
    "missing_key_warnings": missing_key.warnings,
}, ensure_ascii=False))
`;
  const result = spawnSync('python3', ['-c', script], {
    cwd: process.cwd(),
    encoding: 'utf8',
  });

  assert.equal(result.status, 0, result.stderr || result.stdout);
  const payload = JSON.parse(result.stdout.trim());

  // 选版：跳过非 trustable 的中文版，取 trustable 的那个
  assert.deepEqual(payload.requested, ['333', '444']);
  assert.equal(payload.fetched, true);
  assert.equal(payload.title, 'Binary Search on a Segment Tree');
  assert.equal(payload.problem_id, 'aalc001_c');
  assert.equal(payload.problem_dir_id, 'aalc001_c');
  assert.equal(payload.source, 'https://vjudge.net/problem/AtCoder-aalc001_c#author=translator:1281309:zh');
  assert.match(payload.warnings[0], /中文题面/);
  assert.match(payload.warnings[0], /trustable/);

  assert.equal(payload.missing_key_source, 'https://vjudge.net/problem/AtCoder-aalc001_c');
  assert.ok(payload.missing_key_warnings.some(message => message.includes('authorKey')));

  // 样例
  assert.equal(payload.sample_count, 1);
  assert.equal(payload.sample_input, '3\n1 2 3');
  assert.equal(payload.sample_output, '6');

  // 数学定界符必须转成 $...$，且 <pre> 里的 <var> 也要转
  assert.match(payload.statement, /信任的中文题面 \$N\$。/);
  assert.match(payload.statement, /- \$1 \\le N\$/);
  assert.match(payload.statement, /\$N\$/);
  assert.doesNotMatch(payload.statement, /\\\(/);
  assert.doesNotMatch(payload.statement, /<var>/);

  // 章节名本地化 + 样例说明单独成节
  assert.match(payload.statement, /## 题目描述/);
  assert.match(payload.statement, /## 约束/);
  assert.match(payload.statement, /## 输入格式/);
  assert.match(payload.statement, /## 输入输出样例 #1/);
  assert.match(payload.statement, /## 样例说明\n\n样例说明段落 \$A_1\$。/);
  assert.match(payload.statement, /^# Binary Search on a Segment Tree/);

  // 单段与 contest/task 都落到同一目录
  assert.equal(payload.single_dir, 'aalc001_c');
  assert.equal(payload.dashed_dir, 'aalc001_c');
  assert.equal(payload.same_source, true);
});

test('AtCoder fetcher falls back to English when no Chinese statement exists', () => {
  const script = `
import json
import sys

sys.path.insert(0, "scripts/problem-analysis-tools")
from fetchers.atcoder import AtCoderFetcher
from fetchers.vjudge_client import DescBrief, Description


class EnglishOnlyClient:
    def problem_info(self, oj, prob_num):
        return "1", "English Only Problem"

    def desc_briefs(self, oj, prob_num):
        return [
            DescBrief("111", "en", "System", "2026-01-01", True, True, "", "main:en"),
            DescBrief("222", "ja", "System", "2026-01-01", True, False, ""),
        ]

    def description(self, key):
        if key == "111":
            return Description("111", "en", True, [
                ("Problem Statement", "<p>English only.</p>"),
                ("Sample 1", "<table class='vjudge_sample'><thead><tr><th>Input</th>"
                            "<th>Output</th></tr></thead><tbody><tr><td><pre>1</pre></td>"
                            "<td><pre>2</pre></td></tr></tbody></table>"),
            ])
        return Description("222", "ja", True, [("問題文", "<p>日本語。</p>")])


data = AtCoderFetcher(client=EnglishOnlyClient()).fetch("atcoder", "abc999_x").data
print(json.dumps({
    "source": data.source,
    "warnings": data.warnings,
    "sample_count": len(data.samples),
    "statement": data.statement_md,
}, ensure_ascii=False))
`;
  const result = spawnSync('python3', ['-c', script], {
    cwd: process.cwd(),
    encoding: 'utf8',
  });

  assert.equal(result.status, 0, result.stderr || result.stdout);
  const payload = JSON.parse(result.stdout.trim());
  assert.equal(payload.source, 'https://vjudge.net/problem/AtCoder-abc999_x#author=main:en');
  assert.match(payload.warnings[0], /没有中文题面/);
  assert.match(payload.warnings[0], /en/);
  assert.equal(payload.sample_count, 1);
  assert.match(payload.statement, /## 题目描述\n\nEnglish only\./);
});

test('AtCoder fetcher borrows samples from another version when chosen one lacks them', () => {
  const script = `
import json
import sys

sys.path.insert(0, "scripts/problem-analysis-tools")
from fetchers.atcoder import AtCoderFetcher
from fetchers.vjudge_client import DescBrief, Description


class NoSampleChineseClient:
    def problem_info(self, oj, prob_num):
        return "1", "T"

    def desc_briefs(self, oj, prob_num):
        return [
            DescBrief("zhkey", "zh", "GPT", "2026-01-01", False, False, "", "translator:1281309:zh"),
            DescBrief("enkey", "en", "System", "2026-01-01", True, True, ""),
        ]

    def description(self, key):
        if key == "zhkey":
            # 中文版 trustable 且有正文，但没有样例表
            return Description("zhkey", "zh", True, [
                ("题目描述", "<p>中文正文。</p>"),
                ("样例 1", "<h3></h3><pre>1 2</pre>"),
            ])
        return Description("enkey", "en", True, [
            ("Problem Statement", "<p>English.</p>"),
            ("Sample 1", "<table class='vjudge_sample'><thead><tr><th>Input</th>"
                        "<th>Output</th></tr></thead><tbody><tr><td><pre>7 8</pre></td>"
                        "<td><pre>15</pre></td></tr></tbody></table>"),
        ])


data = AtCoderFetcher(client=NoSampleChineseClient()).fetch("atcoder", "abc999_y").data
print(json.dumps({
    "source": data.source,
    "warnings": data.warnings,
    "sample_count": len(data.samples),
    "sample_input": data.samples[0].input if data.samples else "",
    "statement": data.statement_md,
}, ensure_ascii=False))
`;
  const result = spawnSync('python3', ['-c', script], {
    cwd: process.cwd(),
    encoding: 'utf8',
  });

  assert.equal(result.status, 0, result.stderr || result.stdout);
  const payload = JSON.parse(result.stdout.trim());
  assert.equal(payload.source, 'https://vjudge.net/problem/AtCoder-abc999_y#author=translator:1281309:zh');
  assert.equal(payload.sample_count, 1);
  assert.equal(payload.sample_input, '7 8');
  assert.ok(payload.warnings.some((w) => /样例取自/.test(w)));
  assert.match(payload.statement, /中文正文/);
});

test('AtCoder fetcher is strict: fetch failures raise instead of building a skeleton', () => {
  const script = `
import json
import sys
import tempfile
from pathlib import Path
from types import SimpleNamespace

sys.path.insert(0, "scripts/problem-analysis-tools")
import fetch_problem
from fetchers.base import FetchError
from fetchers.atcoder import AtCoderFetcher


class FailingClient:
    def problem_info(self, oj, prob_num):
        raise FetchError("VJudge 上找不到题目 AtCoder-abc999_z。")

    def desc_briefs(self, oj, prob_num):
        raise FetchError("unreachable")

    def description(self, key):
        raise FetchError("unreachable")


# 把真实 fetcher 的 client 换成离线假客户端，避免测试依赖网络。
import fetchers as fetchers_pkg
for candidate in fetchers_pkg.FETCHERS:
    if isinstance(candidate, AtCoderFetcher):
        candidate._client = FailingClient()

args = SimpleNamespace(target=["atcoder", "abc999_z"], dry_run=True)
with tempfile.TemporaryDirectory() as tmp:
    tmp_root = Path(tmp)
    try:
        fetch_problem.run_fetch(
            args,
            repo_root=tmp_root,
            problems_root=tmp_root / "problems",
        )
        outcome = "no_error"
    except fetch_problem.FetchProblemError as exc:
        outcome = "error"
        message = str(exc)
    created = sorted(p.name for p in (tmp_root / "problems").rglob("*")) if (tmp_root / "problems").exists() else []

assert AtCoderFetcher.strict_fetch is True
print(json.dumps({"outcome": outcome, "message": message, "created": created}, ensure_ascii=False))
`;
  const result = spawnSync('python3', ['-c', script], {
    cwd: process.cwd(),
    encoding: 'utf8',
    env: { ...process.env, VJUDGE_COOKIE: '', VJUDGE_USERNAME: '', VJUDGE_PASSWORD: '' },
  });

  assert.equal(result.status, 0, result.stderr || result.stdout);
  const payload = JSON.parse(result.stdout.trim());
  assert.equal(payload.outcome, 'error');
  assert.match(payload.message, /找不到题目/);
  assert.deepEqual(payload.created, []);
});
