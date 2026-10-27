import test from 'node:test';
import assert from 'node:assert/strict';
import {
  existsSync,
  mkdirSync,
  mkdtempSync,
  readFileSync,
  realpathSync,
  rmSync,
  writeFileSync,
} from 'node:fs';
import { execFileSync, spawnSync } from 'node:child_process';
import { tmpdir } from 'node:os';
import path from 'node:path';

const repoRoot = path.resolve();
const migrationScript = path.join(repoRoot, 'scripts', 'migrate-luogu-dir-prefix.py');

test('Luogu fetcher keeps the id casing Luogu gives', () => {
  // 目录名与 frontmatter 的 problem_id 一律按洛谷 id 原样，不再主动折叠大小写。
  // 唯一例外：纯数字与 p<digits> 归一成规范的大写 P 前缀。
  const code = [
    'import json',
    'import sys',
    'sys.path.insert(0, "scripts/problem-analysis-tools")',
    'from fetchers.luogu import LuoguFetcher',
    'fetcher = LuoguFetcher()',
    'data = fetcher.build_data_from_id("luogu", "1001")',
    'assert data.problem_id == "P1001"',
    'assert data.problem_dir_id == "P1001"',
    // 小写 p 是常见写法，仍归一成大写 P
    'assert fetcher.build_data_from_id("luogu", "p1001").problem_dir_id == "P1001"',
    // 非 P 题号：目录名与 problem_id 保持洛谷给的大小写
    'assert fetcher.build_data_from_id("luogu", "B2002").problem_id == "B2002"',
    'assert fetcher.build_data_from_id("luogu", "B2002").problem_dir_id == "B2002"',
    'assert fetcher.build_data_from_id("luogu", "U502676").problem_dir_id == "U502676"',
    'assert fetcher.build_data_from_id("luogu", "AT_abc123_a").problem_dir_id == "AT_abc123_a"',
    'print(json.dumps({"problem_id": data.problem_id, "problem_dir_id": data.problem_dir_id}))',
  ].join('\n');
  const output = execFileSync('python3', ['-c', code], { cwd: repoRoot, encoding: 'utf8' });
  assert.deepEqual(JSON.parse(output.trim()), {
    problem_id: 'P1001',
    problem_dir_id: 'P1001',
  });
});

test('Luogu fetcher prefers the pid Luogu returns over the caller casing', () => {
  // 用户可能输 uva1316 / u502676 这类小写，但洛谷返回的 pid 是大写。
  // 目录名和 problem_id 都应以洛谷返回的 pid 为准。
  const code = [
    'import json',
    'import sys',
    'sys.path.insert(0, "scripts/problem-analysis-tools")',
    'from fetchers.luogu import LuoguFetcher',
    'fetcher = LuoguFetcher()',
    'out = {}',
    'for caller, pid in (("uva1316", "UVA1316"), ("u502676", "U502676"), ("b2002", "B2002")):',
    '    data = fetcher.problem_from_luogu_json({"pid": pid, "title": "T"}, caller)',
    '    out[caller] = [data.problem_id, data.problem_dir_id]',
    // pid 缺失时回退到调用者给的题号
    '    fallback = fetcher.problem_from_luogu_json({"title": "T"}, "u502676")',
    '    out[caller + "_fallback"] = fallback.problem_dir_id',
    'print(json.dumps(out))',
  ].join('\n');
  const output = execFileSync('python3', ['-c', code], { cwd: repoRoot, encoding: 'utf8' });
  assert.deepEqual(JSON.parse(output.trim()), {
    uva1316: ['UVA1316', 'UVA1316'],
    uva1316_fallback: 'u502676',
    u502676: ['U502676', 'U502676'],
    u502676_fallback: 'u502676',
    b2002: ['B2002', 'B2002'],
    b2002_fallback: 'u502676',
  });
});

test('check_problem rejects numeric Luogu directory names', () => {
  // macOS 的 /var 是 /private/var 的软链接；Python 侧 resolve() 会解析软链接，
  // 因此临时目录必须先用 realpath 归一化，否则 relative_to 会失败。
  const root = mkdtempSync(path.join(realpathSync(tmpdir()), 'rbook-luogu-check-'));
  const problemDir = path.join(root, 'problems', 'luogu', '1001');
  try {
    mkdirSync(problemDir, { recursive: true });
    writeFileSync(path.join(problemDir, 'main.cpp'), 'int main() { return 0; }\n');
    writeFileSync(path.join(problemDir, 'index.md'), '---\noj: luogu\nproblem_id: P1001\n---\n');
    const code = [
      'from pathlib import Path',
      'import sys',
      'sys.path.insert(0, "scripts/problem-analysis-tools")',
      'import check_problem',
      'check_problem.PROBLEMS_ROOT = Path(sys.argv[1]) / "problems"',
      'raise SystemExit(check_problem.check_problem(Path(sys.argv[1]) / "problems" / "luogu" / "1001"))',
    ].join('\n');
    const result = spawnSync('python3', ['-c', code, root], {
      cwd: repoRoot,
      encoding: 'utf8',
    });
    assert.equal(result.status, 1);
    assert.match(result.stdout, /Luogu 数字题目录必须使用 P 前缀/);
  } finally {
    rmSync(root, { recursive: true, force: true });
  }
});

test('Luogu scaffold writes P-prefixed directories and frontmatter', () => {
  const root = mkdtempSync(path.join(tmpdir(), 'rbook-luogu-scaffold-'));
  try {
    const code = [
      'from pathlib import Path',
      'import sys',
      'sys.path.insert(0, "scripts/problem-analysis-tools")',
      'from problem_scaffold import create_problem_dir',
      'result = create_problem_dir("luogu", "1001", problems_root=Path(sys.argv[1]), with_workspace=False)',
      'assert result.problem_dir.name == "P1001"',
      'assert "problem_id: \\"P1001\\"" in (result.problem_dir / "index.md").read_text()',
    ].join('\n');
    execFileSync('python3', ['-c', code, root], { cwd: repoRoot, encoding: 'utf8' });
    assert.ok(existsSync(path.join(root, 'luogu', 'P1001', 'index.md')));
    assert.equal(existsSync(path.join(root, 'luogu', '1001')), false);
  } finally {
    rmSync(root, { recursive: true, force: true });
  }
});

test('Luogu directory migration is dry-run by default and applies idempotently', () => {
  const root = mkdtempSync(path.join(tmpdir(), 'rbook-luogu-migrate-'));
  const luoguRoot = path.join(root, 'luogu');
  try {
    mkdirSync(path.join(luoguRoot, '1001'), { recursive: true });
    mkdirSync(path.join(luoguRoot, '1002'), { recursive: true });
    writeFileSync(path.join(luoguRoot, '1001', 'index.md'), 'keep\n');

    const dryRun = spawnSync('python3', [migrationScript, '--root', luoguRoot], {
      cwd: repoRoot,
      encoding: 'utf8',
    });
    assert.equal(dryRun.status, 0, dryRun.stderr || dryRun.stdout);
    assert.match(dryRun.stdout, /numeric directories: 2/);
    assert.ok(existsSync(path.join(luoguRoot, '1001')));
    assert.equal(existsSync(path.join(luoguRoot, 'P1001')), false);

    const apply = spawnSync('python3', [migrationScript, '--root', luoguRoot, '--apply'], {
      cwd: repoRoot,
      encoding: 'utf8',
    });
    assert.equal(apply.status, 0, apply.stderr || apply.stdout);
    assert.ok(existsSync(path.join(luoguRoot, 'P1001', 'index.md')));
    assert.ok(existsSync(path.join(luoguRoot, 'P1002')));
    assert.equal(readFileSync(path.join(luoguRoot, 'P1001', 'index.md'), 'utf8'), 'keep\n');

    const secondApply = execFileSync('python3', [migrationScript, '--root', luoguRoot, '--apply'], {
      cwd: repoRoot,
      encoding: 'utf8',
    });
    assert.match(secondApply, /numeric directories: 0/);
  } finally {
    rmSync(root, { recursive: true, force: true });
  }
});

test('Luogu directory migration refuses pre-existing P targets', () => {
  const root = mkdtempSync(path.join(tmpdir(), 'rbook-luogu-migrate-collision-'));
  const luoguRoot = path.join(root, 'luogu');
  try {
    mkdirSync(path.join(luoguRoot, '1001'), { recursive: true });
    mkdirSync(path.join(luoguRoot, 'P1001'), { recursive: true });

    const result = spawnSync('python3', [migrationScript, '--root', luoguRoot, '--apply'], {
      cwd: repoRoot,
      encoding: 'utf8',
    });
    assert.equal(result.status, 2);
    assert.match(result.stdout, /target directories already exist/);
    assert.ok(existsSync(path.join(luoguRoot, '1001')));
  } finally {
    rmSync(root, { recursive: true, force: true });
  }
});
