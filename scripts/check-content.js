#!/usr/bin/env node

import path from 'node:path';
import { pathToFileURL } from 'node:url';
import ContentService from '../lib/content-service.js';
import ProblemManager from '../lib/problem.js';
import ProblemSetManager from '../lib/problem-set.js';

// 首页按 updated 排序，所以有 date 却没有 updated 的题必须在这里拦住。
// 这条规则只属于校验入口：运行时会回退到 date，不会因为缺字段让网站挂掉。
export function collectMissingUpdatedErrors(problems, baseDir) {
  return problems
    .filter((problem) => problem.date && !problem.updated)
    .map((problem) => ({
      type: 'problem',
      key: `${problem.oj}/${problem.problem_id}`,
      path: problem.md_path ? path.join(baseDir, problem.md_path) : null,
      message: 'frontmatter 缺少 updated 字段（首页按最后修改时间排序需要它）',
    }));
}

export async function inspectContent() {
  const problemManager = new ProblemManager({ auto_load: false });
  const problemSetManager = new ProblemSetManager(problemManager, { auto_load: false });
  const contentService = new ContentService({
    problemManager,
    problemSetManager,
    revisionProvider: () => 'pre-push-verification',
    logger: { error() {}, warn() {} },
  });

  await contentService.initialize();

  const health = contentService.detailedHealth();
  const missing = collectMissingUpdatedErrors(problemManager.getAll(), problemManager.baseDir);
  if (missing.length === 0) return health;

  return {
    ...health,
    state: health.state === 'healthy' ? 'degraded' : health.state,
    errorCount: health.errorCount + missing.length,
    errors: [...health.errors, ...missing],
  };
}

export function formatContentErrors(errors, cwd = process.cwd()) {
  return errors.map((error) => {
    const location = error.path ? path.relative(cwd, error.path) : error.key;
    return `- [${error.type}] ${location}: ${error.message}`;
  }).join('\n');
}

function isMainModule() {
  return process.argv[1]
    && pathToFileURL(path.resolve(process.argv[1])).href === import.meta.url;
}

if (isMainModule()) {
  try {
    const health = await inspectContent();
    if (health.state !== 'healthy' || health.errorCount !== 0) {
      console.error(`内容索引状态: ${health.state}, 错误数: ${health.errorCount}`);
      if (health.errors.length > 0) {
        console.error(formatContentErrors(health.errors));
      }
      process.exitCode = 1;
    } else {
      console.log(
        `内容索引健康: ${health.problemCount} 道题目, ${health.problemSetCount} 个题目单`,
      );
    }
  } catch (error) {
    console.error(error.stack || error.message);
    process.exitCode = 1;
  }
}
