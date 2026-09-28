#!/usr/bin/env python3
"""Backfill the `updated` frontmatter field of problems/*/*/index.md from Git history.

每道题的 `updated` 取“该题目目录在 Git 中的最后一次提交时间”和已有 `date`
两者中较晚的一个，按分钟写入，紧跟 `date:` 之后。这样首页可以按最后修改时间
降序排列，同时保证 `updated` 不会早于创建时间。

Dry-run by default; pass --apply to rewrite files.
"""

from __future__ import annotations

import argparse
import datetime as dt
from pathlib import Path
import re
import subprocess
import sys


REPO_ROOT = Path(__file__).resolve().parents[1]
DEFAULT_ROOT = REPO_ROOT / "problems"
DATE_RE = re.compile(r"^date:\s*(\d{4}-\d{2}-\d{2} \d{2}:\d{2})\s*$")
UPDATED_RE = re.compile(r"^updated:\s*")
STAMP_FORMAT = "%Y-%m-%d %H:%M"


def git(*args: str, cwd: Path) -> str:
    result = subprocess.run(
        ["git", *args],
        cwd=cwd,
        check=True,
        capture_output=True,
        text=True,
    )
    return result.stdout


def last_commit_times(pathspec: str, *, cwd: Path) -> dict[str, int]:
    """Return {problem directory relative path: last commit unix time}."""
    output = git("log", "--format=C%ct", "--name-only", "--", pathspec, cwd=cwd)
    times: dict[str, int] = {}
    current = 0
    for line in output.splitlines():
        if line.startswith("C") and line[1:].isdigit():
            current = int(line[1:])
            continue
        if not line:
            continue
        directory = str(Path(line).parent)
        if times.get(directory, 0) < current:
            times[directory] = current
    return times


def parse_stamp(text: str) -> dt.datetime | None:
    try:
        return dt.datetime.strptime(text, STAMP_FORMAT)
    except ValueError:
        return None


def stamp_of(timestamp: float) -> str:
    return dt.datetime.fromtimestamp(timestamp).strftime(STAMP_FORMAT)


def updated_block(lines: list[str], stamp: str) -> tuple[list[str], str] | None:
    """Insert or refresh the updated line, returning the new lines and outcome."""
    for index, line in enumerate(lines):
        if UPDATED_RE.match(line):
            if line == f"updated: {stamp}":
                return None
            return [*lines[:index], f"updated: {stamp}", *lines[index + 1:]], "updated"

    for index, line in enumerate(lines):
        match = DATE_RE.match(line)
        if match:
            return [*lines[:index + 1], f"updated: {stamp}", *lines[index + 1:]], "inserted"

    return None


def migrate(root: Path, *, apply: bool, verbose: bool) -> int:
    commit_times = last_commit_times(str(root.relative_to(REPO_ROOT)), cwd=REPO_ROOT)

    stats = {"inserted": 0, "updated": 0, "unchanged": 0, "no-git": 0, "no-date": 0, "clamped": 0}
    samples: list[str] = []

    for index_md in sorted(root.glob("*/*/index.md")):
        problem_dir = index_md.parent
        relative_dir = str(problem_dir.relative_to(REPO_ROOT))
        text = index_md.read_text(encoding="utf-8")
        lines = text.split("\n")

        date_value = None
        for line in lines:
            match = DATE_RE.match(line)
            if match:
                date_value = parse_stamp(match.group(1))
                break
        if date_value is None:
            stats["no-date"] += 1
            print(f"skip (no parsable date): {relative_dir}", file=sys.stderr)
            continue

        commit_time = commit_times.get(relative_dir)
        if commit_time is None:
            stats["no-git"] += 1
            timestamp = date_value.timestamp()
        else:
            timestamp = max(commit_time, date_value.timestamp())
            if commit_time < date_value.timestamp():
                stats["clamped"] += 1
                if verbose:
                    print(
                        f"clamped: {relative_dir} git={stamp_of(commit_time)}"
                        f" date={stamp_of(date_value.timestamp())}"
                    )

        result = updated_block(lines, stamp_of(timestamp))
        if result is None:
            stats["unchanged"] += 1
            continue

        new_lines, outcome = result
        stats[outcome] += 1
        if len(samples) < 5:
            samples.append(
                f"{relative_dir}: date={date_value.strftime(STAMP_FORMAT)}"
                f" updated={stamp_of(timestamp)}"
            )
        if apply:
            index_md.write_text("\n".join(new_lines), encoding="utf-8")

    mode = "apply" if apply else "dry-run"
    print(f"mode: {mode}")
    print(f"root: {root}")
    print(
        f"inserted: {stats['inserted']}, refreshed: {stats['updated']},"
        f" unchanged: {stats['unchanged']}, clamped-to-date: {stats['clamped']}"
    )
    if stats["no-git"] or stats["no-date"]:
        print(f"without git history: {stats['no-git']}, without date: {stats['no-date']}")
    for sample in samples:
        print(f"  {sample}")
    if not apply:
        print("dry-run complete; rerun with --apply to rewrite index.md files")
    return 0


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--root", type=Path, default=DEFAULT_ROOT)
    parser.add_argument("--apply", action="store_true", help="rewrite index.md files")
    parser.add_argument("--verbose", action="store_true", help="print every clamped problem")
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    root = args.root.resolve()
    if not root.is_dir():
        print(f"error: not a directory: {root}", file=sys.stderr)
        return 2
    return migrate(root, apply=args.apply, verbose=args.verbose)


if __name__ == "__main__":
    raise SystemExit(main())
