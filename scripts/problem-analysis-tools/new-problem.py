#!/usr/bin/env python3
"""Create a new problem directory using the current OJ ebook structure."""

from __future__ import annotations

import argparse
from pathlib import Path
import sys


SCRIPT_DIR = Path(__file__).resolve().parent
REPO_ROOT = SCRIPT_DIR.parents[1]
for import_path in (SCRIPT_DIR, REPO_ROOT):
    if str(import_path) not in sys.path:
        sys.path.insert(0, str(import_path))

from problem_scaffold import (  # noqa: E402
    PROBLEMS_ROOT,
    create_problem_dir,
    infer_from_cwd,
    relative_to_repo,
)
from fetch_problem import FetchProblemError, print_human, run_fetch  # noqa: E402


def is_url_target(value: str | None) -> bool:
    return bool(value and value.startswith(("http://", "https://")))


def create_problem_from_url(url: str) -> int:
    """URL 模式复用 fetch_problem.py，避免两套抓题/建题逻辑分叉。"""

    fetch_args = argparse.Namespace(
        target=[url],
        dry_run=False,
        force_statement=False,
        force_samples=False,
        force_index_meta=False,
    )
    try:
        payload = run_fetch(fetch_args)
    except FetchProblemError as exc:
        print(str(exc), file=sys.stderr)
        return 2
    print_human(payload)
    return 0


def create_problem(args: argparse.Namespace) -> int:
    oj = args.oj
    problem_id = args.problem_id
    if is_url_target(oj):
        if problem_id:
            print("URL 模式用法：new-problem.py <url>", file=sys.stderr)
            return 2
        return create_problem_from_url(oj)

    if not oj or not problem_id:
        inferred_oj, inferred_id = infer_from_cwd(PROBLEMS_ROOT)
        oj = oj or inferred_oj
        problem_id = problem_id or inferred_id

    if not oj or not problem_id:
        print("缺少 oj/problem_id。用法：new-problem.py <oj> <problem_id> 或 new-problem.py <url>")
        return 2

    try:
        result = create_problem_dir(
            oj,
            problem_id,
            title=args.title,
            source=args.source,
            with_brute=args.with_brute,
            with_gen=args.with_gen,
            with_workspace=args.with_workspace,
        )
    except ValueError as exc:
        print(str(exc))
        return 2

    print(f"题目目录：{relative_to_repo(result.problem_dir)}")
    if result.created:
        print("\n创建：")
        for item in result.created:
            print(f"- {relative_to_repo(item)}")
    if result.skipped:
        print("\n已存在，跳过：")
        for item in result.skipped:
            print(f"- {relative_to_repo(item)}")
    return 0


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description="Create a new OJ problem directory")
    parser.add_argument("oj", nargs="?")
    parser.add_argument("problem_id", nargs="?")
    parser.add_argument("--title", default="")
    parser.add_argument("--source", default="")
    parser.add_argument("--no-brute", dest="with_brute", action="store_false")
    parser.add_argument("--no-gen", dest="with_gen", action="store_false")
    parser.add_argument("--no-workspace", dest="with_workspace", action="store_false")
    parser.set_defaults(with_brute=True, with_gen=True, with_workspace=True)
    return parser.parse_args()


if __name__ == "__main__":
    raise SystemExit(create_problem(parse_args()))
