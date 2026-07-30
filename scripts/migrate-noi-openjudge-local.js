import { existsSync, mkdirSync, readdirSync, readFileSync, writeFileSync } from 'node:fs';
import path from 'node:path';

const SOURCE_ROOT = '/home/rainboy/mycode/problems/other_oj/noiopenjudge';
const TARGET_ROOT = path.resolve('problems/noi_openjudge');
const GENERATED_MARKER = '<!-- generated from noiopenjudge local cache -->';
const NOW = new Date().toLocaleString('sv-SE', { timeZone: 'Asia/Shanghai', hour12: false }).slice(0, 16);

function walk(directory) {
  const entries = readdirSync(directory, { withFileTypes: true });
  const result = [];

  for (const entry of entries) {
    const fullPath = path.join(directory, entry.name);
    if (entry.isDirectory()) result.push(...walk(fullPath));
    else if (entry.name === 'config.json') result.push(fullPath);
  }

  return result;
}

function yamlString(value) {
  return JSON.stringify(String(value || ''));
}

function parseConfig(raw) {
  // 部分历史缓存含有对象或数组末尾逗号，兼容读取但不修改源文件。
  return JSON.parse(raw.replace(/,\s*([}\]])/g, '$1'));
}

function makeProblemId(relativeDirectory) {
  return relativeDirectory.split(path.sep).join('-');
}

function stripFrontMatter(markdown) {
  return markdown.replace(/^---\s*\n[\s\S]*?\n---\s*\n?/, '');
}

function normalizeOriginalAnalysis(markdown) {
  const content = stripFrontMatter(markdown)
    .replace(/<%-\s*include\([^)]*\)\s*_%>/g, '')
    .replace(/^#{1,3}\s+代码\s*$/gim, '')
    .replace(/```(?:cpp|c|haskell)?\s*\n[\s\S]*?```/gi, '')
    .replace(/^#{1,3}\s+/gm, '#### ')
    .trim();

  return content || '<!-- 原解析仅提供代码，代码见下方。 -->';
}

function extractCpp(markdown) {
  const match = markdown.match(/```cpp\s*\n([\s\S]*?)```/i);
  return match ? match[1].trim() : '';
}

function findOriginalCpp(solutionDirectory) {
  if (!existsSync(solutionDirectory)) return '';

  const preferredNames = ['rainboy.cpp', 'rainboy1.cpp', 'dfs.cpp', 'pq.cpp', '1.cpp'];
  const names = new Set(readdirSync(solutionDirectory));
  for (const name of preferredNames) {
    if (names.has(name)) return path.join(solutionDirectory, name);
  }

  return '';
}

function cppHeader() {
  return [
    '/**',
    ' * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx',
    ' * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn',
    ' * rainboy的学习导航网站: https://idx.roj.ac.cn',
    ` * create_at: ${NOW}`,
    ` * update_at: ${NOW}`,
    ' */',
    '',
  ].join('\n');
}

function writeGeneratedFile(destination, content) {
  if (existsSync(destination)) {
    const existing = readFileSync(destination, 'utf8');
    if (!existing.includes(GENERATED_MARKER)) return false;
  }

  writeFileSync(destination, content, 'utf8');
  return true;
}

function renderProblem(problemId, title, content, config) {
  return [
    `# ${problemId} ${title}`,
    '',
    GENERATED_MARKER,
    '',
    content.trim(),
    '',
    '## 限制',
    '',
    `- 时间限制：${config.time}ms`,
    `- 内存限制：${config.memory}MB`,
    '',
  ].join('\n');
}

function renderIndex({ problemId, title, source, analysis, hasAnalysis, hasCpp }) {
  const codeSection = hasCpp
    ? '@include-code(./main.cpp, cpp)'
    : '<!-- 本地原解析中没有可迁移的 C++ 代码。 -->';
  const description = hasAnalysis
    ? '题意与原解析均从本地 OpenJudge 缓存迁移。'
    : '本地题面缓存已迁移，解析内容待补充。';

  return [
    '---',
    'oj: "noi_openjudge"',
    `problem_id: ${yamlString(problemId)}`,
    `title: ${yamlString(title)}`,
    `description: ${yamlString(description)}`,
    'difficulty: "未知"',
    `date: ${NOW}`,
    'toc: true',
    'tags: []',
    'favorite: false',
    'favorite_reason: ""',
    'categories: []',
    'pre: []',
    'common: []',
    'recommend: []',
    `source: ${source || ''}`,
    '---',
    '',
    GENERATED_MARKER,
    '',
    '[[TOC]]',
    '',
    '### 题意',
    '',
    '完整题面见同目录的 `problem.md`。',
    '',
    '### 思路',
    '',
    analysis,
    '',
    '### 代码',
    '',
    codeSection,
    '',
    '### 复杂度',
    '',
    '<!-- 原解析未提供复杂度说明时，后续人工补充。 -->',
    '',
    '### 总结',
    '',
    '<!-- 保留原解析内容，不额外编造结论。 -->',
    '',
  ].join('\n');
}

if (!existsSync(SOURCE_ROOT)) {
  throw new Error(`本地 OpenJudge 缓存不存在：${SOURCE_ROOT}`);
}

let total = 0;
let migratedAnalysis = 0;
let migratedCode = 0;
let skippedExisting = 0;

for (const configPath of walk(SOURCE_ROOT)) {
  const sourceDirectory = path.dirname(configPath);
  const relativeDirectory = path.relative(SOURCE_ROOT, sourceDirectory);
  const problemId = makeProblemId(relativeDirectory);
  const targetDirectory = path.join(TARGET_ROOT, problemId);
  const config = parseConfig(readFileSync(configPath, 'utf8'));
  const content = readFileSync(path.join(sourceDirectory, 'content.md'), 'utf8');
  const solutionDirectory = path.join(sourceDirectory, 'solutions');
  const analysisPath = path.join(solutionDirectory, 'rainboy的解析.md');
  const sourceCppPath = findOriginalCpp(solutionDirectory);
  const originalAnalysis = existsSync(analysisPath) ? readFileSync(analysisPath, 'utf8') : '';
  const embeddedCpp = extractCpp(originalAnalysis);
  const hasSourceCpp = existsSync(sourceCppPath) || Boolean(embeddedCpp);

  mkdirSync(targetDirectory, { recursive: true });
  const problemWritten = writeGeneratedFile(
    path.join(targetDirectory, 'problem.md'),
    renderProblem(problemId, config.title, content, config),
  );
  const indexWritten = writeGeneratedFile(
    path.join(targetDirectory, 'index.md'),
    renderIndex({
      problemId,
      title: config.title,
      source: config.source,
      analysis: originalAnalysis
        ? normalizeOriginalAnalysis(originalAnalysis)
        : '<!-- 本地没有可迁移的原解析正文。 -->',
      hasAnalysis: Boolean(originalAnalysis),
      hasCpp: hasSourceCpp,
    }),
  );

  if (!problemWritten || !indexWritten) skippedExisting++;

  if (hasSourceCpp) {
    const targetCppPath = path.join(targetDirectory, 'main.cpp');
    const originalCpp = existsSync(sourceCppPath)
      ? readFileSync(sourceCppPath, 'utf8').trim()
      : embeddedCpp;

    if (!existsSync(targetCppPath)) {
      const prefix = originalCpp.startsWith('/**') ? '' : cppHeader();
      writeFileSync(targetCppPath, `${prefix}${originalCpp}\n`, 'utf8');
      migratedCode++;
    } else {
      const migratedCpp = readFileSync(targetCppPath, 'utf8');
      if (!migratedCpp.startsWith('/**')) {
        writeFileSync(targetCppPath, `${cppHeader()}${migratedCpp.trim()}\n`, 'utf8');
      }
    }
  }

  if (originalAnalysis) migratedAnalysis++;
  total++;
}

console.log(JSON.stringify({ total, migratedAnalysis, migratedCode, skippedExisting }));
