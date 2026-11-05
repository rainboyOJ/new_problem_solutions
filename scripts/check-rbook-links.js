#!/usr/bin/env node

/**
 * 校验题解里引用的 rbook 文章 id 真的存在。
 *
 * 格式问题（裸 id、缺 reason、id/url 同时写）由 lib/problem.js 的归一化在
 * 载入阶段拦下，`npm run check:content` 就会失败，这里不重复那套判断。
 * 本脚本只做一件 check:content 做不到的事：联网确认 id 在 rbook 目录里。
 *
 * 三条口径：
 *  1. 只拉被引用的站点——仓库里没有 `rbook1:` 引用就不访问 rbook1，
 *     这样 ejs 的目录缺一天不会挡住无关的 push。
 *  2. 被引用的站点必须可用，404 或超时就算失败（不做静默降级，
 *     否则「校验通过但线上点不进去」会重新出现）。
 *  3. `--skip-network` 只跳过存在性，格式仍由 check:content 把关。
 */

import ProblemManager from '../lib/problem.js';
import { RbookArticleService, parseRbookRef } from '../lib/rbook-articles.js';

const skipNetwork = process.argv.includes('--skip-network');

function collectReferences(problems) {
  const references = new Map();
  const record = (ref, field, problemKey) => {
    if (!parseRbookRef(ref)) return;
    if (!references.has(ref)) references.set(ref, { ref, fields: new Set(), problems: [] });
    const entry = references.get(ref);
    entry.fields.add(field);
    if (!entry.problems.includes(problemKey)) entry.problems.push(problemKey);
  };

  for (const problem of problems) {
    const problemKey = `${problem.oj}/${problem.problem_id}`;
    for (const ref of problem.showAtRbook || []) record(ref, 'showAtRbook', problemKey);
    for (const link of problem.rbookLinks || []) {
      if (typeof link?.id === 'string') record(link.id, 'rbookLinks', problemKey);
    }
  }

  return references;
}

async function main() {
  const problemManager = new ProblemManager();
  const problems = problemManager.getAll();
  const loadErrors = problemManager.catalog?.errors || problemManager.errors || [];
  if (loadErrors.length > 0) {
    console.error(`题目索引有 ${loadErrors.length} 个错误，先跑 npm run check:content`);
    process.exitCode = 1;
    return;
  }

  const references = collectReferences(problems);
  const sites = [...new Set([...references.keys()].map((ref) => parseRbookRef(ref).site))].sort();

  if (references.size === 0) {
    console.log('没有任何 rbook 文章引用，跳过');
    return;
  }
  if (skipNetwork) {
    console.log(`跳过联网校验：${references.size} 个 rbook 引用（${sites.join(', ')}）未确认存在`);
    return;
  }

  const service = new RbookArticleService({ logger: { warn() {} } });

  try {
    await service.assertSitesAvailable(sites);
  } catch (error) {
    console.error(error.message);
    console.error(`被引用的站点: ${sites.join(', ')}。站点不可用时不放行，避免发布点不开的链接。`);
    process.exitCode = 1;
    return;
  }

  const resolved = await service.resolveRefs([...references.keys()]);
  const missing = [...references.values()].filter((entry) => !resolved.has(entry.ref));

  if (missing.length > 0) {
    console.error(`有 ${missing.length} 个 rbook 文章 id 在目录里找不到：`);
    for (const entry of missing) {
      console.error(`- ${entry.ref}（${[...entry.fields].join(' / ')}）引用自 ${entry.problems.join(', ')}`);
    }
    process.exitCode = 1;
    return;
  }

  const bySite = new Map();
  for (const entry of references.values()) {
    const { site } = parseRbookRef(entry.ref);
    bySite.set(site, (bySite.get(site) || 0) + 1);
  }
  const summary = [...bySite.entries()].map(([site, count]) => `${site} ${count}`).join('，');
  console.log(`rbook 引用全部有效：${references.size} 个 id（${summary}）`);
}

main().catch((error) => {
  console.error(error.stack || error.message);
  process.exitCode = 1;
});
