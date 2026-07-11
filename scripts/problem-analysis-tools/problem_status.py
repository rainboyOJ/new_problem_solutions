#!/usr/bin/env python3
"""Show the current status and next actions for one problem directory."""

from __future__ import annotations

import argparse
from pathlib import Path
import re
import subprocess
import sys


SCRIPT_DIR = Path(__file__).resolve().parent
REPO_ROOT = SCRIPT_DIR.parents[1]
CHECK_PROBLEM = SCRIPT_DIR / "check_problem.py"
CHECK_SAMPLE = SCRIPT_DIR / "check_sample.py"


def rel(path: Path) -> str:
    try:
        return str(path.resolve().relative_to(REPO_ROOT))
    except ValueError:
        return str(path)


def has_samples(problem_dir: Path) -> bool:
    root_inputs = [p for p in problem_dir.iterdir() if p.is_file() and re.fullmatch(r"in(\d*)", p.name)]
    data_dir = problem_dir / "data"
    data_inputs = list(data_dir.glob("*.in")) if data_dir.is_dir() else []
    return bool(root_inputs or data_inputs)


def has_data_inputs(problem_dir: Path) -> bool:
    data_dir = problem_dir / "data"
    return data_dir.is_dir() and any(data_dir.glob("*.in"))


def is_usaco_problem(problem_dir: Path) -> bool:
    try:
        relative = problem_dir.resolve().relative_to(REPO_ROOT / "problems")
    except ValueError:
        return False
    return len(relative.parts) >= 2 and relative.parts[0] == "usaco"


def run_check_problem(problem_dir: Path) -> int:
    result = subprocess.run([sys.executable, str(CHECK_PROBLEM), str(problem_dir)], check=False)
    return result.returncode


def run_check_sample(problem_dir: Path, timeout: float, memory_mb: int | None) -> int:
    cmd = [sys.executable, str(CHECK_SAMPLE), str(problem_dir), "--timeout", str(timeout)]
    if memory_mb is not None:
        cmd.extend(["--memory-mb", str(memory_mb)])
    return subprocess.run(cmd, check=False).returncode


def print_file_status(problem_dir: Path) -> list[str]:
    suggestions: list[str] = []
    expected = [
        ("index.md", "正式题解"),
        ("main.cpp", "正式代码"),
        ("brute.cpp", "朴素解/对拍标准程序"),
        ("gen.py", "随机数据生成器"),
    ]
    print("\n文件：")
    for filename, desc in expected:
        path = problem_dir / filename
        status = "OK" if path.exists() else "缺少"
        print(f"- {filename:<10} {status}  {desc}")
        if not path.exists():
            if filename == "index.md":
                suggestions.append("运行 new-problem 或使用 oj-problem-format-spec 补 index.md。")
            elif filename == "main.cpp":
                suggestions.append("先完成 main.cpp。")
            elif filename == "brute.cpp":
                suggestions.append("使用 oj-problem-analysis-writer 完成 brute.cpp。")
            elif filename == "gen.py":
                suggestions.append("如果要对拍，补 gen.py。")

    workspace = problem_dir / "problem-analysis-workspace"
    print(f"- problem-analysis-workspace/ {'OK' if workspace.is_dir() else '缺少'}  过程文档")
    if not workspace.is_dir():
        suggestions.append("创建 problem-analysis-workspace/，记录题意、推导和验证过程。")

    samples = has_samples(problem_dir)
    print(f"- samples    {'OK' if samples else '缺少'}  in/out 或 data/*.in")
    if not samples:
        suggestions.append("先下载或手写样例数据。")
    return suggestions


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description="Show problem workflow status")
    parser.add_argument("problem_dir", nargs="?", type=Path, default=Path.cwd())
    parser.add_argument("--run-sample", action="store_true", help="also run check_sample.py")
    parser.add_argument("--timeout", type=float, default=2.0)
    parser.add_argument("--memory-mb", type=int, default=None)
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    problem_dir = args.problem_dir.resolve()
    print(f"题目目录：{rel(problem_dir)}")
    if not problem_dir.exists() or not problem_dir.is_dir():
        print("结果：题目目录不存在")
        return 2

    suggestions = print_file_status(problem_dir)

    print("\n规范检查：")
    check_problem_code = run_check_problem(problem_dir)

    check_sample_code = None
    if args.run_sample:
        print("\n样例检查：")
        check_sample_code = run_check_sample(problem_dir, args.timeout, args.memory_mb)

    if is_usaco_problem(problem_dir):
        if has_data_inputs(problem_dir):
            if check_sample_code == 0:
                suggestions.append("USACO data 已通过 check_sample；只有额外怀疑边界时再对拍。")
            elif check_sample_code is None:
                suggestions.append("USACO 题优先运行 check_sample 验证 data/*.in。")
        else:
            suggestions.append("USACO 题优先运行 fetch_usaco_testdata.py 下载官方测试数据。")
    elif (problem_dir / "main.cpp").exists() and (problem_dir / "brute.cpp").exists() and (problem_dir / "gen.py").exists():
        suggestions.append("可以运行 duipai.py 做对拍。")

    if suggestions:
        print("\n下一步建议：")
        seen: set[str] = set()
        for item in suggestions:
            if item in seen:
                continue
            seen.add(item)
            print(f"- {item}")
    else:
        print("\n下一步建议：当前基础材料齐全，可以继续完善题解或运行对拍。")

    if check_problem_code != 0:
        return 1
    if check_sample_code not in (None, 0):
        return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
