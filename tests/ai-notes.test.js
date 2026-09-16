import test from 'node:test';
import assert from 'node:assert/strict';
import fs from 'node:fs';
import os from 'node:os';
import path from 'node:path';
import { buildApp } from '../app.js';
import ProblemManager from '../lib/problem.js';
import {
  readAiNoteMarkdown,
  renderAiNoteMarkdown,
  resolveAiNoteAssetPath,
  scanAiNotes,
} from '../lib/ai-notes.js';

function makeTempProblem() {
  const root = fs.mkdtempSync(path.join(os.tmpdir(), 'rbook-ai-notes-'));
  const problemDir = path.join(root, 'test', 'one');
  fs.mkdirSync(path.join(problemDir, 'talking_with_ai', 'assets'), { recursive: true });
  return { root, problemDir };
}

function writeNote(problemDir, name, frontmatter, content = '# 标题\n\n正文\n') {
  const fields = Object.entries(frontmatter).map(([key, value]) => `${key}: ${value}`);
  fs.writeFileSync(path.join(problemDir, 'talking_with_ai', name), [
    '---',
    ...fields,
    '---',
    '',
    content,
  ].join('\n'));
}

test('AI 对话扫描只公开合法非草稿文档，并报告不合规 frontmatter', () => {
  const { root, problemDir } = makeTempProblem();
  try {
    writeNote(problemDir, 'visible.md', {
      title: '公开记录',
      description: '一份公开的讨论记录',
      date: '2026-09-15',
      slug: 'visible-note',
      draft: 'false',
    });
    writeNote(problemDir, 'draft.md', {
      title: '草稿',
      description: '不会公开',
      date: '2026-09-14',
      slug: 'draft-note',
      draft: 'true',
    });
    writeNote(problemDir, 'invalid.md', {
      title: '错误文档',
      date: '2026-09-15T12:00:00Z',
      slug: 'Bad Slug',
    });

    const result = scanAiNotes(problemDir);
    assert.deepEqual(result.notes.map((note) => note.slug), ['visible-note']);
    assert.equal(result.errors.length, 3);
    assert.match(result.errors.map((item) => item.message).join('\n'), /description/);
    assert.match(result.errors.map((item) => item.message).join('\n'), /YYYY-MM-DD/);
    assert.match(result.errors.map((item) => item.message).join('\n'), /小写字母/);
  } finally {
    fs.rmSync(root, { recursive: true, force: true });
  }
});

test('AI 对话的受限渲染不会展开 HTML 或文件包含，并重写本地图片路径', () => {
  const { root, problemDir } = makeTempProblem();
  try {
    fs.writeFileSync(path.join(problemDir, 'private.cpp'), 'PRIVATE_CONTENT\n');
    writeNote(problemDir, 'safe.md', {
      title: '安全文档',
      description: '验证受限渲染',
      date: '2026-09-15',
      slug: 'safe-note',
      draft: 'false',
    }, [
      '# 安全文档',
      '',
      '<script>alert(1)</script>',
      '',
      '@include-code(../private.cpp, cpp)',
      '',
      '![图](./assets/chart.png)',
    ].join('\n'));
    fs.writeFileSync(path.join(problemDir, 'talking_with_ai', 'assets', 'chart.png'), 'image');

    const result = scanAiNotes(problemDir);
    const note = result.notes[0];
    assert.doesNotMatch(readAiNoteMarkdown(problemDir, note), /^# 安全文档/m);
    const html = renderAiNoteMarkdown(problemDir, note, null, '/problems/test/one/ai-notes/assets');
    assert.match(html, /&lt;script&gt;alert\(1\)&lt;\/script&gt;/);
    assert.match(html, /@include-code\(/);
    assert.doesNotMatch(html, /PRIVATE_CONTENT/);
    assert.match(html, /src="\/problems\/test\/one\/ai-notes\/assets\/chart\.png"/);
  } finally {
    fs.rmSync(root, { recursive: true, force: true });
  }
});

test('AI 对话图片只允许 assets 中的普通受支持图片', () => {
  const { root, problemDir } = makeTempProblem();
  try {
    const assets = path.join(problemDir, 'talking_with_ai', 'assets');
    fs.writeFileSync(path.join(assets, 'chart.png'), 'image');
    fs.writeFileSync(path.join(problemDir, 'secret.txt'), 'secret');

    assert.equal(resolveAiNoteAssetPath(problemDir, 'chart.png'), path.join(assets, 'chart.png'));
    assert.equal(resolveAiNoteAssetPath(problemDir, '../secret.txt'), null);
    assert.equal(resolveAiNoteAssetPath(problemDir, '../../secret.txt'), null);
    assert.equal(resolveAiNoteAssetPath(problemDir, 'chart.svg'), null);
  } finally {
    fs.rmSync(root, { recursive: true, force: true });
  }
});

test('catalog 将不合规 AI 对话作为内容错误，同时保留有效题目', () => {
  const { root, problemDir } = makeTempProblem();
  try {
    fs.writeFileSync(path.join(problemDir, 'index.md'), [
      '---',
      'oj: test',
      'problem_id: one',
      'title: Test',
      '---',
      '',
      '# Test',
    ].join('\n'));
    writeNote(problemDir, 'invalid.md', {
      title: '缺少字段',
      date: '2026-09-15',
      slug: 'broken-note',
    });

    const manager = new ProblemManager({ auto_load: false, baseDir: root });
    const catalog = manager.buildCatalog();
    assert.equal(catalog.problems.length, 1);
    assert.equal(catalog.problems[0].aiNotes.length, 0);
    assert.equal(catalog.errors[0].type, 'ai-note');
  } finally {
    fs.rmSync(root, { recursive: true, force: true });
  }
});

test('公开 AI 对话有列表、阅读和 Raw 接口，原始目录路径不可绕过草稿保护', async () => {
  const app = await buildApp({ logger: false });
  try {
    const list = await app.inject({ method: 'GET', url: '/problems/luogu/P4036/ai-notes/' });
    assert.equal(list.statusCode, 200);
    assert.match(list.body, /AI 对话记录/);
    assert.match(list.body, /后缀数组与 LCQ 求解原理/);

    const detail = await app.inject({ method: 'GET', url: '/problems/luogu/P4036/ai-notes/suffix-array-lcq/' });
    assert.equal(detail.statusCode, 200);
    assert.match(detail.body, /Markdown 原文/);
    assert.match(detail.body, /阅读提示/);

    const raw = await app.inject({ method: 'GET', url: '/api/problems/luogu/P4036/ai-notes/suffix-array-lcq/raw' });
    assert.equal(raw.statusCode, 200);
    assert.match(raw.json().md_content, /后缀数组与LCQ求解原理/);

    const blocked = await app.inject({
      method: 'GET',
      url: '/problems/luogu/P4036/talking_with_ai/_____LCQ_____2026-09-15.md',
    });
    assert.equal(blocked.statusCode, 404);
  } finally {
    await app.close();
  }
});
