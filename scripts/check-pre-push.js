#!/usr/bin/env node

import fs from 'node:fs';
import path from 'node:path';
import { spawnSync } from 'node:child_process';
import { pathToFileURL } from 'node:url';

export function parsePushRefs(input) {
  return String(input || '')
    .split(/\r?\n/)
    .map((line) => line.trim())
    .filter(Boolean)
    .map((line) => {
      const fields = line.split(/\s+/);
      if (fields.length !== 4) {
        throw new Error(`无法解析 Git pre-push 输入: ${line}`);
      }
      return {
        localRef: fields[0],
        localSha: fields[1],
        remoteRef: fields[2],
        remoteSha: fields[3],
      };
    });
}

export function findNonHeadRefs(refs, headSha) {
  return refs.filter((ref) => !/^0+$/.test(ref.localSha) && ref.localSha !== headSha);
}

function runGit(args, options = {}) {
  const result = spawnSync('git', args, {
    cwd: options.cwd || process.cwd(),
    encoding: 'utf8',
  });
  if (result.status !== 0) {
    throw new Error(result.stderr.trim() || `git ${args.join(' ')} failed`);
  }
  return result.stdout;
}

// 一次 cat-file --batch 读完所有版本的文件，避免逐目录起 git 进程（2000+ 目录会慢十几秒）。
function readBlobs(cwd, specs) {
  const blobs = new Map();
  if (specs.length === 0) return blobs;

  const result = spawnSync('git', ['cat-file', '--batch'], {
    cwd,
    input: `${specs.join('\n')}\n`,
    maxBuffer: 1 << 28,
  });
  if (result.status !== 0) {
    throw new Error(result.stderr?.toString().trim() || 'git cat-file --batch failed');
  }

  const output = result.stdout;
  let offset = 0;
  for (const spec of specs) {
    const headerEnd = output.indexOf(0x0a, offset);
    if (headerEnd === -1) break;
    const header = output.toString('utf8', offset, headerEnd);
    offset = headerEnd + 1;

    if (header.endsWith(' missing')) {
      blobs.set(spec, null);
      continue;
    }

    const size = Number(header.split(' ')[2]);
    if (!Number.isInteger(size)) {
      blobs.set(spec, null);
      break;
    }
    blobs.set(spec, output.toString('utf8', offset, offset + size));
    offset += size + 1; // 跳过文件内容后面的换行
  }
  return blobs;
}

const PROBLEM_DIR_RE = /^problems\/[^/]+\/[^/]+\//;
const STAMP_RE = /^(\d{4})-(\d{2})-(\d{2})(?:[ T](\d{2}):(\d{2}))?/;

// 题目目录指 problems/<oj>/<id>/，目录内任何被跟踪文件的改动都算这道题被改了。
export function problemDirOf(relativePath) {
  if (!PROBLEM_DIR_RE.test(relativePath)) return null;
  return relativePath.split('/').slice(0, 3).join('/');
}

// 读取 frontmatter 顶层字段，只认第一个 --- 块，避免误读正文。
export function frontmatterField(content, field) {
  const match = /^---\r?\n([\s\S]*?)\r?\n---/.exec(String(content || ''));
  if (!match) return null;

  for (const line of match[1].split(/\r?\n/)) {
    const separator = line.indexOf(':');
    if (separator <= 0 || line !== line.trim()) continue;
    if (line.slice(0, separator).trim() !== field) continue;
    return line.slice(separator + 1).trim().replace(/^["']|["']$/g, '');
  }
  return null;
}

// 把 updated 解析成时间戳；格式不认识时返回 null，交给调用方决定是否放行。
export function parseUpdatedStamp(value) {
  const match = STAMP_RE.exec(String(value || '').trim());
  if (!match) return null;

  const [, year, month, day, hour = '00', minute = '00'] = match;
  const timestamp = new Date(
    Number(year),
    Number(month) - 1,
    Number(day),
    Number(hour),
    Number(minute),
  ).getTime();
  return Number.isFinite(timestamp) ? timestamp : null;
}

// 本次 push 里被改动、但 updated 没有跟着变新的题目。
export function findStaleUpdatedProblems({ cwd = process.cwd(), refs = [] } = {}) {
  const stale = [];

  for (const ref of refs) {
    if (/^0+$/.test(ref.localSha)) continue; // 删除引用，没有内容要检查
    if (/^0+$/.test(ref.remoteSha)) continue; // 新分支没有可比基线

    const changed = runGit(
      ['diff', '--name-only', `${ref.remoteSha}..${ref.localSha}`, '--', 'problems'],
      { cwd },
    ).split('\n').filter(Boolean);

    const directories = [...new Set(changed.map(problemDirOf).filter(Boolean))].sort();
    const specs = [];
    for (const directory of directories) {
      specs.push(`${ref.localSha}:${directory}/index.md`);
      specs.push(`${ref.remoteSha}:${directory}/index.md`);
    }
    const blobs = readBlobs(cwd, specs);

    for (const directory of directories) {
      const headSpec = `${ref.localSha}:${directory}/index.md`;
      const baseSpec = `${ref.remoteSha}:${directory}/index.md`;
      const headContent = blobs.get(headSpec) ?? null;
      if (headContent === null) continue; // 本题没有 index.md，由内容检查负责

      const headValue = frontmatterField(headContent, 'updated');
      if (parseUpdatedStamp(headValue) === null) {
        stale.push({
          directory,
          reason: 'index.md 的 updated 缺失或格式不是 YYYY-MM-DD HH:MM',
        });
        continue;
      }

      const baseContent = blobs.get(baseSpec) ?? null;
      if (baseContent === null) continue; // 本次 push 新增的题目

      const baseValue = frontmatterField(baseContent, 'updated');
      const baseStamp = parseUpdatedStamp(baseValue);
      if (baseStamp === null) continue; // 远端还没有这个字段，属于引入该字段的过渡期

      if (parseUpdatedStamp(headValue) <= baseStamp) {
        stale.push({
          directory,
          reason: `updated 仍是 ${baseValue}，没有晚于远端版本`,
        });
      }
    }
  }

  return stale.sort((left, right) => left.directory.localeCompare(right.directory));
}

export function checkPrePush({ cwd = process.cwd(), input = '' } = {}) {
  const status = runGit(
    ['status', '--porcelain=v1', '--untracked-files=all', '--ignore-submodules=none'],
    { cwd },
  );
  if (status.trim()) {
    const error = new Error('Git 工作区不是干净状态');
    error.details = status.trimEnd();
    error.suggestion = '先提交、删除或忽略这些文件，再重新 push。';
    throw error;
  }

  const headSha = runGit(['rev-parse', 'HEAD'], { cwd }).trim();
  const refs = parsePushRefs(input);
  const nonHeadRefs = findNonHeadRefs(refs, headSha);
  if (nonHeadRefs.length > 0) {
    const error = new Error('push 包含不指向当前 HEAD 的引用');
    error.details = nonHeadRefs
      .map((ref) => `${ref.localRef} -> ${ref.remoteRef}: ${ref.localSha}`)
      .join('\n');
    error.suggestion = '切换到对应 commit 后分别 push；删除远端引用不受此限制。';
    throw error;
  }

  const stale = findStaleUpdatedProblems({ cwd, refs });
  if (stale.length > 0) {
    const error = new Error('题目目录有改动，但 frontmatter 的 updated 没有跟着更新');
    error.details = stale
      .map((item) => `- ${item.directory}: ${item.reason}`)
      .join('\n');
    error.suggestion = '把这些问题 index.md 的 updated 改成当前时间（格式 YYYY-MM-DD HH:MM），'
      + '它是首页「最后更新」列的排序依据；确实不该刷新时也请显式改一个更晚的值。';
    throw error;
  }

  return { headSha, refs };
}

function isMainModule() {
  return process.argv[1]
    && pathToFileURL(path.resolve(process.argv[1])).href === import.meta.url;
}

if (isMainModule()) {
  try {
    const input = fs.readFileSync(0, 'utf8');
    const result = checkPrePush({ input });
    console.log(`[pre-push] Git 前置检查通过: ${result.headSha.slice(0, 12)}`);
  } catch (error) {
    console.error('\n[pre-push] Git 前置检查失败');
    console.error(`原因: ${error.message}`);
    if (error.details) console.error(`\n${error.details}`);
    console.error(`\n建议: ${error.suggestion || '修复以上问题后重试。'}`);
    process.exitCode = 1;
  }
}
