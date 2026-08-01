#!/usr/bin/env node

import path from 'node:path';
import { pathToFileURL } from 'node:url';
import ContentService from '../lib/content-service.js';
import ProblemManager from '../lib/problem.js';
import ProblemSetManager from '../lib/problem-set.js';

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
  return contentService.detailedHealth();
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
