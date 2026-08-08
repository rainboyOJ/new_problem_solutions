import test from 'node:test';
import assert from 'node:assert/strict';
import {
  existsSync,
  mkdirSync,
  mkdtempSync,
  readFileSync,
  rmSync,
  writeFileSync,
} from 'node:fs';
import { execFileSync, spawnSync } from 'node:child_process';
import { tmpdir } from 'node:os';
import path from 'node:path';

const repoRoot = path.resolve();
const migrationScript = path.join(repoRoot, 'scripts', 'migrate-luogu-dir-prefix.py');

test('Luogu fetcher uses P-prefixed directory ids for numeric problems', () => {
  const code = [
    'import json',
    'import sys',
    'sys.path.insert(0, "scripts/problem-analysis-tools")',
    'from fetchers.luogu import LuoguFetcher',
    'fetcher = LuoguFetcher()',
    'data = fetcher.build_data_from_id("luogu", "1001")',
    'assert data.problem_id == "P1001"',
    'assert data.problem_dir_id == "P1001"',
    'assert fetcher.build_data_from_id("luogu", "B2002").problem_dir_id == "b2002"',
    'print(json.dumps({"problem_id": data.problem_id, "problem_dir_id": data.problem_dir_id}))',
  ].join('\n');
  const output = execFileSync('python3', ['-c', code], { cwd: repoRoot, encoding: 'utf8' });
  assert.deepEqual(JSON.parse(output.trim()), {
    problem_id: 'P1001',
    problem_dir_id: 'P1001',
  });
});

test('check_problem rejects numeric Luogu directory names', () => {
  const root = mkdtempSync(path.join(tmpdir(), 'rbook-luogu-check-'));
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
