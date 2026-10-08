#!/usr/bin/env python3
"""Manage sample and local data files for one OJ problem directory."""

from __future__ import annotations

import argparse
from dataclasses import dataclass
from pathlib import Path
import re
import shutil
import sys

sys.path.insert(0, str(Path(__file__).resolve().parent))
from datafiles import find_inputs, find_output_for, find_outputs  # noqa: E402


REPO_ROOT = Path(__file__).resolve().parents[2]


@dataclass
class DataCase:
    name: str
    input_path: Path
    answer_path: Path | None
    source: str


def rel(path: Path) -> str:
    try:
        return str(path.resolve().relative_to(REPO_ROOT))
    except ValueError:
        return str(path)


def natural_root_key(path: Path) -> tuple[int, str]:
    match = re.fullmatch(r"in(\d*)", path.name)
    if not match:
        return (10**9, path.name)
    suffix = match.group(1)
    return (int(suffix) if suffix else 0, path.name)


def answer_for_root_input(input_path: Path) -> Path | None:
    match = re.fullmatch(r"in(\d*)", input_path.name)
    if not match:
        return None
    suffix = match.group(1)
    answer = input_path.with_name(f"out{suffix}")
    return answer if answer.exists() else None


def answer_for_data_input(input_path: Path) -> Path | None:
    # ⚠ 不能用 with_suffix：对 SNOW1.IN 它会去找 SNOW1.out，而实际是 SNOW1.OUT。
    return find_output_for(input_path)


def discover_cases(problem_dir: Path) -> list[DataCase]:
    cases: list[DataCase] = []
    root_inputs = sorted(
        [p for p in problem_dir.iterdir() if p.is_file() and re.fullmatch(r"in(\d*)", p.name)],
        key=natural_root_key,
    )
    for input_path in root_inputs:
        cases.append(DataCase(input_path.name, input_path, answer_for_root_input(input_path), "root"))

    data_dir = problem_dir / "data"
    if data_dir.is_dir():
        for input_path in find_inputs(data_dir):
            cases.append(
                DataCase(
                    f"data/{input_path.name}",
                    input_path,
                    answer_for_data_input(input_path),
                    "data",
                )
            )
    return cases


def discover_orphan_answers(problem_dir: Path, cases: list[DataCase]) -> list[Path]:
    used = {case.answer_path.resolve() for case in cases if case.answer_path is not None}
    answers: list[Path] = []
    answers.extend(p for p in problem_dir.iterdir() if p.is_file() and re.fullmatch(r"out(\d*)", p.name))
    data_dir = problem_dir / "data"
    if data_dir.is_dir():
        answers.extend(sorted([*find_outputs(data_dir)]))
    return sorted([p for p in answers if p.resolve() not in used])


def ensure_problem_dir(path: Path) -> Path:
    problem_dir = path.resolve()
    if not problem_dir.exists() or not problem_dir.is_dir():
        raise FileNotFoundError(f"题目目录不存在：{rel(problem_dir)}")
    return problem_dir


def print_cases(problem_dir: Path) -> int:
    cases = discover_cases(problem_dir)
    orphans = discover_orphan_answers(problem_dir, cases)
    if not cases:
        print(f"未找到输入数据：{rel(problem_dir)}")
    for idx, case in enumerate(cases, 1):
        answer = rel(case.answer_path) if case.answer_path else "缺少答案"
        print(f"[{idx}] {case.name}")
        print(f"  input : {rel(case.input_path)}")
        print(f"  answer: {answer}")
        print(f"  source: {case.source}")
    if orphans:
        print("\n孤立答案文件：")
        for path in orphans:
            print(f"- {rel(path)}")
    return 1 if any(case.answer_path is None for case in cases) or orphans else 0


def normalize_file(path: Path) -> bool:
    data = path.read_bytes()
    normalized = data.replace(b"\r\n", b"\n").replace(b"\r", b"\n")
    if normalized == data:
        return False
    path.write_bytes(normalized)
    return True


def normalize_data(problem_dir: Path) -> int:
    cases = discover_cases(problem_dir)
    targets = {case.input_path for case in cases}
    targets.update(case.answer_path for case in cases if case.answer_path is not None)
    changed = 0
    for path in sorted(targets):
        if normalize_file(path):
            changed += 1
            print(f"normalized: {rel(path)}")
    print(f"完成：{changed} 个文件被修改")
    return 0


def case_name_from_input(input_path: Path) -> str:
    match = re.fullmatch(r"in(\d*)", input_path.name)
    if match:
        suffix = match.group(1)
        return f"sample{suffix or '0'}"
    return input_path.stem


def copy_file(src: Path, dst: Path, force: bool) -> None:
    if dst.exists() and not force:
        raise FileExistsError(f"目标已存在：{rel(dst)}，使用 --force 覆盖")
    dst.parent.mkdir(parents=True, exist_ok=True)
    shutil.copyfile(src, dst)


def add_case(problem_dir: Path, input_arg: str, answer_arg: str | None, name_arg: str | None, force: bool) -> int:
    input_path = Path(input_arg)
    if not input_path.is_absolute():
        input_path = problem_dir / input_path
    if not input_path.exists():
        raise FileNotFoundError(f"输入文件不存在：{rel(input_path)}")

    answer_path = None
    if answer_arg:
        answer_path = Path(answer_arg)
        if not answer_path.is_absolute():
            answer_path = problem_dir / answer_path
        if not answer_path.exists():
            raise FileNotFoundError(f"答案文件不存在：{rel(answer_path)}")

    name = name_arg or case_name_from_input(input_path)
    data_dir = problem_dir / "data"
    dst_in = data_dir / f"{name}.in"
    copy_file(input_path, dst_in, force)
    print(f"added input : {rel(dst_in)}")

    if answer_path is not None:
        ext = ".ans" if answer_path.suffix == ".ans" else ".out"
        dst_answer = data_dir / f"{name}{ext}"
        copy_file(answer_path, dst_answer, force)
        print(f"added answer: {rel(dst_answer)}")
    return 0


def copy_samples_to_data(problem_dir: Path, force: bool) -> int:
    root_cases = [case for case in discover_cases(problem_dir) if case.source == "root"]
    if not root_cases:
        print("没有根目录样例可复制")
        return 0
    for case in root_cases:
        name = case_name_from_input(case.input_path)
        copy_file(case.input_path, problem_dir / "data" / f"{name}.in", force)
        print(f"copied input : {case.name} -> data/{name}.in")
        if case.answer_path is not None:
            copy_file(case.answer_path, problem_dir / "data" / f"{name}.out", force)
            print(f"copied answer: {case.answer_path.name} -> data/{name}.out")
    return 0


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description="Manage OJ problem data files")
    sub = parser.add_subparsers(dest="cmd", required=True)

    def add_problem_arg(p: argparse.ArgumentParser) -> None:
        p.add_argument("problem_dir", nargs="?", type=Path, default=Path.cwd())

    list_parser = sub.add_parser("list", help="list paired and unpaired data files")
    add_problem_arg(list_parser)

    normalize_parser = sub.add_parser("normalize", help="normalize CRLF to LF")
    add_problem_arg(normalize_parser)

    add_parser = sub.add_parser("add", help="copy one input/answer pair into data/")
    add_problem_arg(add_parser)
    add_parser.add_argument("--input", required=True)
    add_parser.add_argument("--answer", default=None)
    add_parser.add_argument("--name", default=None)
    add_parser.add_argument("--force", action="store_true")

    copy_parser = sub.add_parser("copy-samples-to-data", help="copy root in/out samples into data/")
    add_problem_arg(copy_parser)
    copy_parser.add_argument("--force", action="store_true")

    return parser.parse_args()


def main() -> int:
    args = parse_args()
    try:
        problem_dir = ensure_problem_dir(args.problem_dir)
        if args.cmd == "list":
            return print_cases(problem_dir)
        if args.cmd == "normalize":
            return normalize_data(problem_dir)
        if args.cmd == "add":
            return add_case(problem_dir, args.input, args.answer, args.name, args.force)
        if args.cmd == "copy-samples-to-data":
            return copy_samples_to_data(problem_dir, args.force)
    except Exception as exc:
        print(f"错误：{exc}", file=sys.stderr)
        return 2
    return 2


if __name__ == "__main__":
    raise SystemExit(main())
