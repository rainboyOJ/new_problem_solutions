#!/usr/bin/env node

import fs from 'node:fs';
import os from 'node:os';
import path from 'node:path';
import { spawnSync } from 'node:child_process';
import { fileURLToPath, pathToFileURL } from 'node:url';

const ROOT = path.resolve(path.dirname(fileURLToPath(import.meta.url)), '..');
const GENERATED_DIR = path.join(ROOT, 'public', 'relations-graph');

export class VerificationFailure extends Error {
  constructor(message, options = {}) {
    super(message, { cause: options.cause });
    this.name = 'VerificationFailure';
    this.stage = options.stage || '未知阶段';
    this.command = options.command || '-';
    this.exitCode = options.exitCode ?? 1;
    this.suggestion = options.suggestion || '根据上方错误修复后，重新运行 npm run verify:push。';
  }
}

function listTree(root) {
  const entries = new Map();
  if (!fs.existsSync(root)) return entries;

  function visit(directory, prefix = '') {
    const children = fs.readdirSync(directory, { withFileTypes: true })
      .sort((left, right) => left.name.localeCompare(right.name));
    for (const child of children) {
      const relativePath = prefix ? `${prefix}/${child.name}` : child.name;
      const absolutePath = path.join(directory, child.name);
      if (child.isDirectory()) {
        visit(absolutePath, relativePath);
      } else if (child.isFile()) {
        entries.set(relativePath, fs.readFileSync(absolutePath));
      } else {
        entries.set(relativePath, Buffer.from(`unsupported:${child.isSymbolicLink()}`));
      }
    }
  }

  visit(root);
  return entries;
}

export function compareDirectoryTrees(expectedDir, actualDir) {
  const expected = listTree(expectedDir);
  const actual = listTree(actualDir);
  const missing = [];
  const unexpected = [];
  const changed = [];

  for (const [relativePath, expectedContent] of expected) {
    const actualContent = actual.get(relativePath);
    if (!actualContent) missing.push(relativePath);
    else if (!expectedContent.equals(actualContent)) changed.push(relativePath);
  }
  for (const relativePath of actual.keys()) {
    if (!expected.has(relativePath)) unexpected.push(relativePath);
  }

  return { missing, unexpected, changed };
}

function commandText(command, args) {
  return [command, ...args.map((arg) => (/\s/.test(arg) ? JSON.stringify(arg) : arg))].join(' ');
}

function runCommand(stage, command, args, options = {}) {
  const capture = options.capture === true;
  const result = spawnSync(command, args, {
    cwd: options.cwd || ROOT,
    env: options.env || process.env,
    encoding: capture ? 'utf8' : undefined,
    stdio: capture ? ['ignore', 'pipe', 'pipe'] : 'inherit',
  });
  if (result.status === 0) return result;

  if (capture) {
    if (result.stdout?.trim()) console.error(result.stdout.trimEnd());
    if (result.stderr?.trim()) console.error(result.stderr.trimEnd());
  }
  throw new VerificationFailure(result.error?.message || `${command} 执行失败`, {
    stage,
    command: commandText(command, args),
    exitCode: result.status ?? 1,
    suggestion: options.suggestion,
  });
}

function printDirectoryDiff(diff) {
  for (const item of diff.missing) console.error(`- 已提交产物存在、临时构建缺少: ${item}`);
  for (const item of diff.unexpected) console.error(`- 临时构建新增、已提交产物缺少: ${item}`);
  for (const item of diff.changed) console.error(`- 内容不一致: ${item}`);
}

function runDependencyCheck(stage) {
  const nodeMajor = Number(process.versions.node.split('.')[0]);
  if (!Number.isInteger(nodeMajor) || nodeMajor < 22) {
    throw new VerificationFailure(`当前 Node.js 版本为 ${process.version}，项目要求 Node.js >=22`, {
      stage,
      command: 'node --version',
      suggestion: '切换到 Node.js 22 或更高版本后重试。',
    });
  }
  if (!fs.existsSync(path.join(ROOT, 'node_modules'))) {
    throw new VerificationFailure('node_modules 不存在', {
      stage,
      command: 'npm ls --all',
      suggestion: '手动运行 npm ci 安装依赖，然后重试。',
    });
  }

  runCommand(stage, 'npm', [
    'ci', '--dry-run', '--ignore-scripts', '--no-audit', '--no-fund',
  ], {
    suggestion: 'package.json 与 package-lock.json 不一致；修复 lockfile 后重试。',
  });
  runCommand(stage, 'npm', ['ls', '--all', '--loglevel=error'], {
    capture: true,
    suggestion: '本地依赖缺失或版本不匹配；手动运行 npm ci 后重试。',
  });
}

function runBuildCheck(stage) {
  const temporaryRoot = fs.mkdtempSync(path.join(os.tmpdir(), 'rbook-build-'));
  const outputDir = path.join(temporaryRoot, 'relations-graph');
  const args = [
    'run', 'build:relations', '--', '--outDir', outputDir,
  ];
  try {
    runCommand(stage, 'npm', args, {
      suggestion: '修复关系图编译错误后重试。',
    });
    const diff = compareDirectoryTrees(GENERATED_DIR, outputDir);
    if (diff.missing.length || diff.unexpected.length || diff.changed.length) {
      printDirectoryDiff(diff);
      throw new VerificationFailure('关系图构建产物与源码不一致', {
        stage,
        command: commandText('npm', args),
        suggestion: '运行 npm run build，检查并提交 public/relations-graph/ 的变化。',
      });
    }
  } finally {
    fs.rmSync(temporaryRoot, { recursive: true, force: true });
  }
}

export function createVerificationStages() {
  return [
    {
      name: '运行环境与依赖',
      command: 'node --version && npm ci --dry-run && npm ls --all',
      run: (stage) => runDependencyCheck(stage),
    },
    {
      name: '自动化测试',
      command: 'npm test',
      run: (stage) => runCommand(stage, 'npm', ['test'], {
        suggestion: '根据失败测试的断言和堆栈修复代码。',
      }),
    },
    {
      name: '关系图编译与产物一致性',
      command: 'npm run build:relations -- --outDir <temporary-directory>',
      run: (stage) => runBuildCheck(stage),
    },
    {
      name: '全量内容索引',
      command: 'npm run check:content',
      run: (stage) => runCommand(stage, 'npm', ['run', 'check:content'], {
        suggestion: '根据列出的文件路径修复 frontmatter 或内容目录错误。',
      }),
    },
    {
      name: '真实服务启动与健康检查',
      command: 'npm run check:smoke',
      run: (stage) => runCommand(stage, 'npm', ['run', 'check:smoke'], {
        suggestion: '根据服务日志修复启动错误或不健康的内容状态。',
      }),
    },
  ];
}

export function runVerification(stages = createVerificationStages()) {
  const startedAt = Date.now();
  for (let index = 0; index < stages.length; index += 1) {
    const stage = stages[index];
    const label = `${index + 1}/${stages.length} ${stage.name}`;
    console.log(`\n[verify:push] ${label}`);
    if (process.env.GITHUB_ACTIONS === 'true') console.log(`::group::${label}`);
    const stageStartedAt = Date.now();
    try {
      stage.run(stage.name);
      console.log(`[verify:push] 通过 (${((Date.now() - stageStartedAt) / 1000).toFixed(1)}s)`);
    } catch (error) {
      if (process.env.GITHUB_ACTIONS === 'true') console.log('::endgroup::');
      if (error instanceof VerificationFailure) throw error;
      throw new VerificationFailure(error.message, {
        stage: stage.name,
        command: stage.command,
        cause: error,
      });
    }
    if (process.env.GITHUB_ACTIONS === 'true') console.log('::endgroup::');
  }
  console.log(`\n[verify:push] 全部检查通过 (${((Date.now() - startedAt) / 1000).toFixed(1)}s)`);
}

function isMainModule() {
  return process.argv[1]
    && pathToFileURL(path.resolve(process.argv[1])).href === import.meta.url;
}

if (isMainModule()) {
  process.chdir(ROOT);
  try {
    runVerification();
  } catch (error) {
    const failure = error instanceof VerificationFailure
      ? error
      : new VerificationFailure(error.message, { cause: error });
    console.error('\n[verify:push] 检查失败');
    console.error(`阶段: ${failure.stage}`);
    console.error(`命令: ${failure.command}`);
    console.error(`退出码: ${failure.exitCode}`);
    console.error(`原因: ${failure.message}`);
    console.error(`建议: ${failure.suggestion}`);
    process.exitCode = failure.exitCode;
  }
}
