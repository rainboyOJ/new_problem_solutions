import test from 'node:test';
import assert from 'node:assert/strict';
import { execFileSync } from 'node:child_process';
import { mkdirSync, mkdtempSync, readFileSync, writeFileSync } from 'node:fs';
import { tmpdir } from 'node:os';
import { join } from 'node:path';

const AUDIT = 'scripts/problem-analysis-tools/roj_py_read_audit.py';
const REGRESS = 'scripts/problem-analysis-tools/roj_py_sample_regress.py';

function runAudit(args) {
  return execFileSync('python3', [AUDIT, ...args], { cwd: process.cwd(), encoding: 'utf8' });
}

function writeProblem(root, id, mainPy) {
  const dir = join(root, 'roj', id);
  mkdirSync(dir, { recursive: true });
  writeFileSync(join(dir, 'main.py'), mainPy);
  return dir;
}

test('roj_py_read_audit 按读入方式分级', () => {
  const root = mkdtempSync(join(tmpdir(), 'roj-read-audit-'));
  writeProblem(root, '9001', [
    'import sys',
    '',
    '',
    'def solve() -> None:',
    '    data = list(map(int, sys.stdin.buffer.read().split()))',
    '    n = data[0]',
    '    for i in range(1, n + 1):',
    '        print(data[i])',
    '',
    '',
    'if __name__ == "__main__":',
    '    solve()',
    '',
  ].join('\n'));
  writeProblem(root, '9002', [
    'import sys',
    '',
    '',
    'def solve() -> None:',
    '    data = iter(map(int, sys.stdin.buffer.read().split()))',
    '    n = next(data)',
    '    print(n)',
    '',
    '',
    'if __name__ == "__main__":',
    '    solve()',
    '',
  ].join('\n'));
  writeProblem(root, '9003', [
    'import sys',
    '',
    '',
    'def solve() -> None:',
    '    a, b = map(int, sys.stdin.buffer.read().split())',
    '    print(a + b)',
    '',
    '',
    'if __name__ == "__main__":',
    '    solve()',
    '',
  ].join('\n'));

  const report = join(root, 'audit.json');
  runAudit(['--problems', join(root, 'roj'), '--json', report]);
  const data = JSON.parse(readFileSync(report, 'utf8'));
  const tiers = Object.fromEntries(data.records.map((r) => [r.problem, r.tier]));

  assert.equal(tiers['roj/9001'], 'offset_index');
  assert.equal(tiers['roj/9002'], 'next_ok');
  assert.equal(tiers['roj/9003'], 'unpack_ok');

  const ids = runAudit(['--problems', join(root, 'roj'), '--tier', 'offset_index', '--ids']).trim();
  assert.equal(ids, 'roj/9001');
});

test('roj_py_sample_regress 抽取多种题面格式的样例', () => {
  const root = mkdtempSync(join(tmpdir(), 'roj-samples-'));
  const dir = join(root, 'roj', '9004');
  mkdirSync(dir, { recursive: true });
  const problemMd = [
    '### 【输入样例】',
    '',
    '```',
    '1 2',
    '```',
    '',
    '### 【输出样例】',
    '',
    '```',
    '3',
    '```',
    '',
    '## 样例 2 输入',
    '',
    '```plaintext',
    '4 5',
    '```',
    '',
    '## 样例 2 输出',
    '',
    '```plaintext',
    '9',
    '```',
    '',
    '**输入样例#3：**',
    '',
    '\\-3.14',
    '',
    '**输出样例#3：**',
    '',
    '3.14',
    '',
    '### 【样例 4 输入】',
    '',
    '    7 8',
    '',
    '### 【样例 4 输出】',
    '',
    '    15',
    '',
  ].join('\n');
  writeFileSync(join(dir, 'problem.md'), problemMd);

  const script = [
    'import json, pathlib, sys',
    "sys.path.insert(0, 'scripts/problem-analysis-tools')",
    'import roj_py_sample_regress as m',
    "print(json.dumps(m.extract_samples(pathlib.Path(sys.argv[1]))))",
  ].join('\n');
  const output = execFileSync(
    'python3',
    ['-c', script, join(dir, 'problem.md')],
    { cwd: process.cwd(), encoding: 'utf8' },
  );
  const pairs = JSON.parse(output);

  assert.deepEqual(pairs, [
    ['1 2', '3'],
    ['4 5', '9'],
    ['-3.14', '3.14'],
    ['7 8', '15'],
  ]);
});
