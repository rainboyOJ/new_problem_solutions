import test from 'node:test';
import assert from 'node:assert/strict';
import { existsSync, readFileSync } from 'node:fs';
import { join } from 'node:path';

const root = process.cwd();
const writer = join(root, '.agents/skills/oj-problem-analysis-writer');
const format = join(root, '.agents/skills/oj-problem-format-spec');

function read(path) {
  return readFileSync(path, 'utf8');
}

test('OJ analysis skills expose routed references', () => {
  const writerMain = read(join(writer, 'SKILL.md'));
  const formatMain = read(join(format, 'SKILL.md'));
  const writerRefs = [
    'process-documents.md',
    'brute-force.md',
    'verification.md',
    'visualization.md',
    'language-learning.md',
  ];
  const formatRefs = ['frontmatter.md', 'layouts.md', 'migration.md'];

  for (const file of writerRefs) {
    assert.ok(existsSync(join(writer, 'references', file)), `missing writer reference: ${file}`);
    assert.match(writerMain, new RegExp(file.replace('.', '\\.') ));
  }
  for (const file of formatRefs) {
    assert.ok(existsSync(join(format, 'references', file)), `missing format reference: ${file}`);
    assert.match(formatMain, new RegExp(file.replace('.', '\\.') ));
  }
});

test('layout and workflow capabilities remain discoverable', () => {
  const all = [
    read(join(writer, 'SKILL.md')),
    read(join(format, 'SKILL.md')),
    ...[
      'process-documents.md',
      'brute-force.md',
      'verification.md',
      'visualization.md',
      'language-learning.md',
    ].map((file) => read(join(writer, 'references', file))),
    ...['frontmatter.md', 'layouts.md', 'migration.md'].map((file) =>
      read(join(format, 'references', file)),
    ),
  ].join('\n');

  for (const phrase of [
    '直接正解型',
    '暴力到正解型',
    '并列多解法型',
    '子任务递进型',
    'problem-analysis-workspace',
    'brute.cpp',
    '对拍',
    '可视化评估',
    '语言/语法学习',
    '旧文章默认不迁移',
    'new-problem.py',
  ]) {
    assert.match(all, new RegExp(phrase.replace(/[.*+?^${}()|[\]\\]/g, '\\$&')));
  }
});

test('old fixed-layout and misplaced-brute instructions are absent', () => {
  const files = [
    join(writer, 'SKILL.md'),
    join(format, 'SKILL.md'),
    ...['frontmatter.md', 'layouts.md', 'migration.md'].map((file) => join(format, 'references', file)),
    ...[
      'process-documents.md',
      'brute-force.md',
      'verification.md',
      'visualization.md',
      'language-learning.md',
    ].map((file) => join(writer, 'references', file)),
  ];
  const all = files.map(read).join('\n');
  assert.doesNotMatch(all, /brute\.cpp[^\n]*## 思路/);
  assert.doesNotMatch(all, /固定章节[^\n]*## 思路/);
  assert.doesNotMatch(all, /全局[^\n]*## 代码/);
});

test('entrypoints are materially smaller while references hold detail', () => {
  const writerLines = read(join(writer, 'SKILL.md')).split('\n').length;
  const formatLines = read(join(format, 'SKILL.md')).split('\n').length;
  assert.ok(writerLines < 400, `writer entrypoint is ${writerLines} lines`);
  assert.ok(formatLines < 300, `format entrypoint is ${formatLines} lines`);
});

test('workflow execution discipline and judge time policy stay wired', () => {
  const workflowDir = join(root, '.agents/skills/oj-problem-workflow');
  const judge = join(root, '.agents/skills/oj-judge-and-stress/SKILL.md');
  const discipline = join(workflowDir, 'references/execution-discipline.md');

  assert.ok(existsSync(discipline), 'missing workflow reference: execution-discipline.md');
  assert.match(read(join(workflowDir, 'SKILL.md')), /execution-discipline\.md/);

  const disciplineText = read(discipline);
  for (const phrase of ['临时目录', '一次只改一个变量', '穷举', '实测定阶', '验证分级', '定位真实进度']) {
    assert.match(disciplineText, new RegExp(phrase));
  }

  // Python 时限放宽口径必须同时出现在 judge skill 与仓库 AGENTS.md。
  const judgeText = read(judge);
  assert.match(judgeText, /3 倍/);
  assert.match(judgeText, /--time 9000/);
  assert.match(read(join(root, 'AGENTS.md')), /3 倍/);

  // 文件命名约定必须写在布局 reference 里。
  assert.match(
    read(join(root, '.agents/skills/oj-problem-format-spec/references/layouts.md')),
    /main2\.<ext>/,
  );
});
