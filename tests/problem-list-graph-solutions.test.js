import test from 'node:test';
import assert from 'node:assert/strict';
import { readFileSync, readdirSync, statSync } from 'node:fs';
import { createHash } from 'node:crypto';
import path from 'node:path';
import vm from 'node:vm';
import { normalizeProblemId } from '../lib/problem.js';

const REPO = path.resolve('.');
const ARTIFACT_DIR = path.join(REPO, 'public', 'problem-list-graph');
const HTML_PATH = path.join(ARTIFACT_DIR, 'index.html');
const JSON_PATH = path.join(ARTIFACT_DIR, 'problems.json');
const README_PATH = path.join(REPO, 'problem-list-graph', 'README.md');
const PROBLEMS_DIR = path.join(REPO, 'problems');

const DATA_PREFIX = '<script>var DATA=';
const DATA_SUFFIX = ';</script>';

function readArtifacts() {
  const html = readFileSync(HTML_PATH, 'utf8');
  const start = html.indexOf(DATA_PREFIX);
  assert.notEqual(start, -1, 'index.html 里应有内嵌的 var DATA={…};');
  const end = html.indexOf(DATA_SUFFIX, start);
  assert.notEqual(end, -1, 'index.html 的内嵌 DATA 应以 };<\/script> 收尾');
  const embedded = html.slice(start + DATA_PREFIX.length, end);
  const json = readFileSync(JSON_PATH, 'utf8');
  return {
    html,
    embedded,
    json,
    // 两份产物各解析一份，避免其中一份漂移时被另一份掩盖。
    embeddedData: JSON.parse(embedded),
    fileData: JSON.parse(json),
  };
}

function extractFunction(html, name) {
  const start = html.indexOf(`function ${name}(`);
  assert.notEqual(start, -1, `index.html 里应有 function ${name}(`);
  const end = html.indexOf('\n}', start);
  assert.notEqual(end, -1, `function ${name} 应以行首 } 收尾`);
  return html.slice(start, end + 2);
}

// 页面的 keyOf 是进度键的唯一权威：从 index.html 抽出来直接用。
function readPageKeyOf(html) {
  const match = /\/\* keyOf:start \*\/([\s\S]*?)\/\* keyOf:end \*\//.exec(html);
  assert.ok(match, 'index.html 里应有 /* keyOf:start */ … /* keyOf:end */ 包裹的 keyOf');
  const keyOf = vm.runInNewContext(`${match[1]}\nkeyOf;`, {});
  assert.equal(typeof keyOf, 'function', '抽出来的 keyOf 应是函数');
  return keyOf;
}

function scanSiteSolutions() {
  const found = new Map(); // 小写键 → 真实键
  for (const oj of readdirSync(PROBLEMS_DIR)) {
    const ojDir = path.join(PROBLEMS_DIR, oj);
    if (!statSync(ojDir).isDirectory()) continue;
    for (const id of readdirSync(ojDir)) {
      const dir = path.join(ojDir, id);
      if (!statSync(dir).isDirectory()) continue;
      try {
        statSync(path.join(dir, 'index.md'));
      } catch {
        continue;
      }
      const key = `${oj}/${normalizeProblemId(oj, id)}`;
      found.set(key.toLowerCase(), key);
    }
  }
  return found;
}

function solveExpected(keyOf, data) {
  const site = scanSiteSolutions();
  const keys = new Set();
  for (const problem of data.problems) {
    const want = keyOf(problem.id);
    const real = site.get(want.toLowerCase());
    if (real === undefined) continue;
    assert.equal(
      real,
      want,
      `题目单里的 ${problem.id} 推导出 ${want}，但仓库里的真实键是 ${real}：进度键会与题目单错配`,
    );
    keys.add(real);
  }
  return [...keys].sort();
}

test('keyOf 覆盖五类题号的推导规则', () => {
  const { html } = readArtifacts();
  const keyOf = readPageKeyOf(html);
  assert.equal(keyOf('P1048'), 'luogu/P1048');
  assert.equal(keyOf('SP1716'), 'luogu/SP1716');
  assert.equal(keyOf('UVA10298'), 'luogu/UVA10298');
  assert.equal(keyOf('CF600E'), 'codeforces/600E');
  assert.equal(keyOf('AT_agc001_e'), 'atcoder/agc001_e');
});

test('解析 chip 排在题号之后、题目名之前', () => {
  const { html } = readArtifacts();
  const body = extractFunction(html, 'rowHTML');
  const at = (needle) => {
    const index = body.indexOf(needle);
    assert.notEqual(index, -1, `rowHTML 里应渲染 ${needle}`);
    return index;
  };
  assert.ok(at('class="pid"') < at('class="sol"'), '「解析」应排在题号之后');
  assert.ok(
    at('class="sol"') < at('class="pname"'),
    '「解析」应排在题目名之前：.pname 是 flex:1，放到它后面会被推到右侧、看起来像个 tag',
  );
});

test('solutions 与 problems/ 独立复算的结果一致', () => {
  const { html, embeddedData, fileData } = readArtifacts();
  const keyOf = readPageKeyOf(html);
  const expected = solveExpected(keyOf, embeddedData);

  for (const [label, data] of [
    ['index.html 内嵌 DATA', embeddedData],
    ['problems.json', fileData],
  ]) {
    assert.deepEqual(
      data.solutions,
      expected,
      `${label} 的 solutions 与 problems/ 漂移了，请重跑 python3 problem-list-graph/build-solutions.py`,
    );
    assert.equal(new Set(data.solutions).size, data.solutions.length, 'solutions 不应有重复键');
    assert.ok(data.solutions.length > 0, 'solutions 不应为空');
  }
});

test('solutions 里每个键都指向真实存在的解析目录', () => {
  const { embeddedData, fileData } = readArtifacts();
  for (const data of [embeddedData, fileData]) {
    for (const key of data.solutions) {
      assert.ok(
        /^[a-z0-9_]+\/.+$/i.test(key),
        `${key} 应是 <oj>/<题号> 形式（页面直接把它当题目路径用）`,
      );
      statSync(path.join(PROBLEMS_DIR, key, 'index.md'));
    }
  }
});

test('solGenerated 是合法日期，且不晚于今天', () => {
  const { embeddedData, fileData } = readArtifacts();
  for (const data of [embeddedData, fileData]) {
    assert.match(data.solGenerated, /^\d{4}-\d{2}-\d{2}$/);
    const generated = new Date(`${data.solGenerated}T00:00:00Z`);
    assert.ok(Number.isFinite(generated.getTime()), 'solGenerated 应是可解析的日期');
    assert.ok(generated.getTime() <= Date.now() + 86400000, 'solGenerated 不应是未来日期');
  }
});

test('problems.json 与 index.html 内嵌 DATA 是同一份字节', () => {
  const { embedded, json } = readArtifacts();
  assert.equal(json, embedded, '两份产物必须由脚本一起写出，内容逐字节相同');
  assert.ok(json.length > 700000, 'DATA 不应被截断');
});

test('顶层字段顺序稳定，solutions 在 problems 之前', () => {
  const { embeddedData, fileData } = readArtifacts();
  for (const data of [embeddedData, fileData]) {
    assert.deepEqual(Object.keys(data).slice(0, 3), ['generated', 'solGenerated', 'total']);
    const keys = Object.keys(data);
    assert.ok(keys.indexOf('solutions') < keys.indexOf('problems'), 'solutions 应在 problems 之前');
    assert.equal(data.problems.length, data.total);
  }
});

test('README 记录的 sha256 与产物一致', () => {
  const readme = readFileSync(README_PATH, 'utf8');
  const block = /当前产物（[^）]*）：\r?\n\r?\n```\r?\n([\s\S]*?)\r?\n```/.exec(readme);
  assert.ok(block, 'README.md 里应有「当前产物（…）」+ hash 代码块');

  const recorded = new Map();
  for (const line of block[1].split(/\r?\n/)) {
    const [hash, name] = line.trim().split(/\s+/);
    recorded.set(name, hash);
  }

  for (const [name, file] of [
    ['index.html', HTML_PATH],
    ['problems.json', JSON_PATH],
  ]) {
    const actual = createHash('sha256').update(readFileSync(file)).digest('hex');
    assert.equal(
      recorded.get(name),
      actual,
      `README.md 里 ${name} 的 sha256 过期了，请重跑 python3 problem-list-graph/build-solutions.py`,
    );
  }
});
