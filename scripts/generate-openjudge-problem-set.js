import { existsSync, readdirSync, readFileSync, writeFileSync } from 'node:fs';
import path from 'node:path';

const SOURCE_ROOT = '/home/rainboy/mycode/problems/other_oj/noiopenjudge';
const OUTPUT_PATH = path.resolve('problem-sets/noi-openjudge-basic.md');

const CHAPTER_TITLES = {
  ch0101: '1.1 编程基础之输入输出',
  ch0102: '1.2 编程基础之变量定义、赋值及转换',
  ch0103: '1.3 编程基础之算术表达式与顺序执行',
  ch0104: '1.4 编程基础之逻辑表达式与条件分支',
  ch0105: '1.5 编程基础之循环控制',
  ch0106: '1.6 编程基础之一维数组',
  ch0107: '1.7 编程基础之字符串',
  ch0108: '1.8 编程基础之多维数组',
  ch0109: '1.9 编程基础之顺序查找',
  ch0110: '1.10 编程基础之简单排序',
  ch0111: '1.11 编程基础之二分查找',
  ch0112: '1.12 编程基础之函数与过程抽象',
  ch0113: '1.13 编程基础之综合应用',
  ch0201: '2.1 基本算法之枚举',
  ch0202: '2.2 基本算法之递归和自调用函数',
  ch0203: '2.3 基本算法之递归变递推',
  ch0204: '2.4 基本算法之分治',
  ch0205: '2.5 基本算法之搜索',
  ch0206: '2.6 基本算法之动态规划',
  ch0207: '2.7 基本算法之算法效率',
  ch0301: '3.1 数据结构之结构',
  ch0302: '3.2 数据结构之指针和链表',
  ch0303: '3.3 数据结构之栈',
  ch0304: '3.4 数据结构之队列',
  ch0305: '3.5 数据结构之哈希',
  ch0306: '3.6 数据结构之二叉树',
  ch0307: '3.7 数据结构之堆',
  ch0308: '3.8 数据结构之图',
  ch0309: '3.9 数据结构之 C++ STL',
  ch0401: '4.1 算法之排序和算法性能',
  ch0402: '4.2 算法之数论',
  ch0403: '4.3 算法之图论',
  ch0404: '4.4 算法之分治',
  ch0405: '4.5 算法之动态规划',
  ch0406: '4.6 算法之贪心',
  ch0407: '4.7 算法之搜索',
  english: '简单英文题',
  math: '小学奥数',
};

function parseConfig(raw) {
  return JSON.parse(raw.replace(/,\s*([}\]])/g, '$1'));
}

function discoverProblems() {
  const groups = new Map();

  for (const group of readdirSync(SOURCE_ROOT, { withFileTypes: true })) {
    if (!group.isDirectory()) continue;

    const groupDirectory = path.join(SOURCE_ROOT, group.name);
    const problems = [];
    for (const entry of readdirSync(groupDirectory, { withFileTypes: true })) {
      if (!entry.isDirectory()) continue;

      const configPath = path.join(groupDirectory, entry.name, 'config.json');
      if (!existsSync(configPath)) continue;
      const config = parseConfig(readFileSync(configPath, 'utf8'));
      problems.push({ id: entry.name, title: config.title, source: config.source });
    }

    problems.sort((left, right) => left.id.localeCompare(right.id, 'en', { numeric: true }));
    if (problems.length > 0) groups.set(group.name, problems);
  }

  return [...groups.entries()].sort(([left], [right]) => left.localeCompare(right, 'en', { numeric: true }));
}

function renderProblemSet(groups) {
  const problemCount = groups.reduce((sum, [, problems]) => sum + problems.length, 0);
  const sections = groups.map(([group, problems]) => [
    `## ${CHAPTER_TITLES[group] || group}（${problems.length} 题）`,
    '',
    ...problems.map((problem) => {
      const problemId = `${group}-${problem.id}`;
      return `- [ ] [[problem: noi_openjudge,${problemId}]] · [${problem.title}](${problem.source})`;
    }),
    '',
  ].join('\n'));

  return [
    '---',
    'title: "OpenJudge 全站题单"',
    'description: "由本地 noi.openjudge.cn 题面缓存生成的完整题单。"',
    'order: 41',
    'source: "http://noi.openjudge.cn/"',
    '---',
    '',
    '# OpenJudge 全站题单',
    '',
    '[OpenJudge NOI 题库](http://noi.openjudge.cn/)',
    '',
    `本题单按本地题面缓存收录 ${groups.length} 个章节、${problemCount} 道题，并与仓库中的 noi_openjudge 解析目录关联。`,
    '使用 `node scripts/generate-openjudge-problem-set.js` 可从本地缓存重新生成。',
    '',
    ...sections,
  ].join('\n');
}

if (!existsSync(SOURCE_ROOT)) {
  throw new Error(`本地 OpenJudge 缓存不存在：${SOURCE_ROOT}`);
}

const groups = discoverProblems();
const markdown = renderProblemSet(groups);
writeFileSync(OUTPUT_PATH, markdown, 'utf8');
console.log(`已生成 ${OUTPUT_PATH}，包含 ${groups.length} 个章节、${groups.reduce((sum, [, items]) => sum + items.length, 0)} 道题。`);
