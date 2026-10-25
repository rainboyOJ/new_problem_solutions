import test from 'node:test';
import assert from 'node:assert/strict';
import { spawnSync } from 'node:child_process';
import { mkdtempSync, writeFileSync, readFileSync, mkdirSync } from 'node:fs';
import { tmpdir } from 'node:os';
import { join } from 'node:path';

// duipai.py 的 --deadline 是整轮对拍的总时限：用尽后必须停下来并返回 3，
// 不能靠外层 timeout 兜底（外层杀掉的话报告和退出码都丢了）。
const script = 'scripts/problem-analysis-tools/duipai.py';

function makeFixture() {
  const dir = mkdtempSync(join(tmpdir(), 'duipai-deadline-'));
  writeFileSync(
    join(dir, 'gen.py'),
    [
      'import sys',
      'from cyaron import IO, randint',
      'io = IO(input_file=sys.stdout, disable_output=True)',
      'io.input_writeln(randint(1, 100), randint(1, 100))',
      '',
    ].join('\n'),
  );
  writeFileSync(
    join(dir, 'main.cpp'),
    '#include <bits/stdc++.h>\nint main(){long long a,b;std::cin>>a>>b;std::cout<<a+b<<"\\n";}\n',
  );
  writeFileSync(
    join(dir, 'brute.cpp'),
    '#include <bits/stdc++.h>\nint main(){long long a,b;std::cin>>a>>b;std::cout<<a+b<<"\\n";}\n',
  );
  mkdirSync(join(dir, 'workspace'), { recursive: true });
  return dir;
}

function run(dir, args) {
  return spawnSync(
    'python3',
    [
      script,
      '--gen', join(dir, 'gen.py'),
      '--user', join(dir, 'main.cpp'),
      '--brute', join(dir, 'brute.cpp'),
      '--report', join(dir, 'report.md'),
      '--failed-dir', join(dir, 'failed'),
      ...args,
    ],
    { cwd: process.cwd(), encoding: 'utf8', timeout: 180_000 },
  );
}

test('duipai stops with exit 3 when --deadline is exhausted', () => {
  const dir = makeFixture();
  const result = run(dir, ['-n', '200', '--deadline', '0.01']);

  assert.equal(result.status, 3, result.stderr || result.stdout);
  assert.match(result.stdout, /Deadline exceeded after \d+ case/);
  // 报告必须留下：外层 timeout 杀进程不会有退出码，也不会有报告。
  const report = readFileSync(join(dir, 'report.md'), 'utf8');
  assert.match(report, /超时退出（--deadline 用尽）/);
});

test('duipai still runs to completion with a generous --deadline', () => {
  const dir = makeFixture();
  const result = run(dir, ['-n', '3', '--deadline', '600']);

  assert.equal(result.status, 0, result.stderr || result.stdout);
  assert.match(result.stdout, /Passed 3 tests/);
  const report = readFileSync(join(dir, 'report.md'), 'utf8');
  assert.match(report, /- 结果：通过/);
});

test('duipai rejects a negative --deadline', () => {
  const dir = makeFixture();
  const result = run(dir, ['-n', '1', '--deadline', '-1']);

  assert.notEqual(result.status, 0);
  assert.match(result.stderr, /--deadline must be non-negative/);
});
