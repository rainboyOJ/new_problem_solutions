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
