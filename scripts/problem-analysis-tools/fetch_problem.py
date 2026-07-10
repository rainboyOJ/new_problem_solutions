#!/usr/bin/env python3
"""Fetch an online judge problem into the current ebook problem structure."""

from __future__ import annotations

import argparse
from dataclasses import asdict
import json
from pathlib import Path
import re
import sys
import tempfile
from typing import Any


SCRIPT_DIR = Path(__file__).resolve().parent
REPO_ROOT = SCRIPT_DIR.parents[1]
if str(REPO_ROOT) not in sys.path:
    sys.path.insert(0, str(REPO_ROOT))

from fetchers import FETCHERS, FetchError, FetchResult, ProblemData, Sample  # noqa: E402
from problem_scaffold import (  # noqa: E402
    PROBLEMS_ROOT,
    create_problem_dir,
    relative_to_repo,
    validate_problem_path_parts,
)


class FetchProblemError(RuntimeError):
    pass


def find_fetcher_by_name(oj: str):
    for fetcher in FETCHERS:
        if fetcher.match_name(oj):
            return fetcher
    raise FetchProblemError(f"不支持的 OJ：{oj}")


def find_fetcher_by_url(url: str):
    for fetcher in FETCHERS:
        if fetcher.match_url(url):
            return fetcher
    raise FetchProblemError(f"无法识别 URL 对应的 OJ：{url}")


def parse_frontmatter(text: str) -> tuple[dict[str, str], str] | None:
    if not text.startswith("---\n"):
        return None
    end = text.find("\n---\n", 4)
    if end == -1:
        return None
    raw = text[4:end]
    body = text[end + len("\n---\n") :]
    data: dict[str, str] = {}
    for line in raw.splitlines():
        if ":" not in line:
            continue
        key, value = line.split(":", 1)
        data[key.strip()] = value.strip()
    return data, body


def yaml_scalar(value: str) -> str:
    if value == "":
        return ""
    if re.search(r"[:#\n\"']", value):
        escaped = value.replace("\\", "\\\\").replace('"', '\\"')
        return f'"{escaped}"'
    return value


def normalize_line_endings(content: str) -> str:
    """抓取页面可能带 CRLF/CR，写入仓库前统一为 LF。"""

    return content.replace("\r\n", "\n").replace("\r", "\n")


def update_index_meta(index_path: Path, data: ProblemData, *, dry_run: bool) -> bool:
    """只更新 frontmatter 里的 title/source，不触碰题解正文。"""

    if not index_path.exists():
        return False
    parsed = parse_frontmatter(index_path.read_text(encoding="utf-8"))
    if parsed is None:
        return False
    frontmatter, body = parsed
    changed = False
    if data.title and frontmatter.get("title") != yaml_scalar(data.title):
        frontmatter["title"] = yaml_scalar(data.title)
        changed = True
    if data.source and frontmatter.get("source") != data.source:
        frontmatter["source"] = data.source
        changed = True
    if not changed:
        return False
    ordered_keys = [
        "oj",
        "problem_id",
        "title",
        "description",
        "date",
        "toc",
        "tags",
        "categories",
        "pre",
        "common",
        "recommend",
        "source",
    ]
    lines: list[str] = ["---"]
    emitted = set()
    for key in ordered_keys:
        if key in frontmatter:
            lines.append(f"{key}: {frontmatter[key]}")
            emitted.add(key)
    for key, value in frontmatter.items():
        if key not in emitted:
            lines.append(f"{key}: {value}")
    lines.append("---")
    new_text = "\n".join(lines) + "\n" + body
    if not dry_run:
        index_path.write_text(new_text, encoding="utf-8")
    return True


def write_text_file(
    path: Path,
    content: str,
    *,
    overwrite: bool,
    dry_run: bool,
    written: list[str],
    skipped: list[str],
    repo_root: Path,
) -> None:
    rel = relative_to_repo(path, repo_root)
    if path.exists() and not overwrite:
        skipped.append(rel)
        return
    if not dry_run:
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(normalize_line_endings(content), encoding="utf-8")
    written.append(rel)


def write_fetch_outputs(
    problem_dir: Path,
    data: ProblemData,
    args: argparse.Namespace,
    *,
    repo_root: Path,
) -> tuple[list[str], list[str]]:
    written: list[str] = []
    skipped: list[str] = []

    if data.statement_md:
        write_text_file(
            problem_dir / "problem.md",
            data.statement_md,
            overwrite=args.force_statement,
            dry_run=args.dry_run,
            written=written,
            skipped=skipped,
            repo_root=repo_root,
        )

    # 样例是抓取产物，默认不覆盖；需要重新抓时只用 --force-samples。
    for index, sample in enumerate(data.samples, start=1):
        write_text_file(
            problem_dir / f"in{index}",
            sample.input,
            overwrite=args.force_samples,
            dry_run=args.dry_run,
            written=written,
            skipped=skipped,
            repo_root=repo_root,
        )
        write_text_file(
            problem_dir / f"out{index}",
            sample.output,
            overwrite=args.force_samples,
            dry_run=args.dry_run,
            written=written,
            skipped=skipped,
            repo_root=repo_root,
        )

    if data.samples:
        write_text_file(
            problem_dir / "in",
            data.samples[0].input,
            overwrite=args.force_samples,
            dry_run=args.dry_run,
            written=written,
            skipped=skipped,
            repo_root=repo_root,
        )

    if args.force_index_meta:
        changed = update_index_meta(problem_dir / "index.md", data, dry_run=args.dry_run)
        if changed:
            written.append(relative_to_repo(problem_dir / "index.md", repo_root))
        else:
            skipped.append(relative_to_repo(problem_dir / "index.md", repo_root))

    return written, skipped


def preview_scaffold_paths(problem_dir: Path, *, repo_root: Path) -> tuple[list[str], list[str]]:
    """dry-run 时模拟 scaffold 会创建/跳过的路径。"""

    workspace = problem_dir / "problem-analysis-workspace"
    paths = [
        problem_dir / "index.md",
        problem_dir / "main.cpp",
        problem_dir / "brute.cpp",
        problem_dir / "gen.py",
        workspace / "01-problem-understanding.md",
        workspace / "02-observation-and-model.md",
        workspace / "03-solution-derivation.md",
        workspace / "04-correctness-and-edge-cases.md",
        workspace / "05-complexity-and-implementation.md",
        workspace / "06-final-index-draft.md",
    ]
    created: list[str] = []
    skipped: list[str] = []
    for path in paths:
        rel = relative_to_repo(path, repo_root)
        if path.exists():
            skipped.append(rel)
        else:
            created.append(rel)
    return created, skipped


def skeleton_result_from_error(oj: str, problem_id: str, source: str, error: Exception) -> FetchResult:
    fetcher = find_fetcher_by_name(oj)
    data = fetcher.build_data_from_id(oj, problem_id)
    if source:
        data.source = source
    data.warnings.append(f"题面/样例抓取失败，仅创建 skeleton：{error}")
    return FetchResult(data=data, fetched=False, warnings=list(data.warnings))


def fetch_from_args(args: argparse.Namespace) -> FetchResult:
    if len(args.target) == 1 and args.target[0].startswith(("http://", "https://")):
        url = args.target[0]
        fetcher = find_fetcher_by_url(url)
        try:
            return fetcher.fetch_by_url(url)
        except FetchError as exc:
            # URL 能解析出 OJ/题号时，允许降级创建 skeleton。
            oj, problem_id = fetcher.parse_url(url)
            return skeleton_result_from_error(oj, problem_id, url, exc)

    if len(args.target) != 2:
        raise FetchProblemError("用法：fetch_problem.py <oj> <problem_id> 或 fetch_problem.py <url>")

    oj, problem_id = args.target
    fetcher = find_fetcher_by_name(oj)
    try:
        return fetcher.fetch(oj, problem_id)
    except FetchError as exc:
        return skeleton_result_from_error(oj, problem_id, "", exc)


def run_fetch(args: argparse.Namespace, *, repo_root: Path = REPO_ROOT, problems_root: Path = PROBLEMS_ROOT) -> dict[str, Any]:
    result = fetch_from_args(args)
    data = result.data
    try:
        validate_problem_path_parts(data.oj, data.problem_dir_id)
    except ValueError as exc:
        raise FetchProblemError(str(exc)) from exc

    problem_dir = problems_root / data.oj / data.problem_dir_id
    created: list[str] = []
    skipped: list[str] = []
    written: list[str] = []

    if args.dry_run:
        # dry-run 只报告将要触碰的位置，不实际创建目录。
        preview_created, preview_skipped = preview_scaffold_paths(problem_dir, repo_root=repo_root)
        created.extend(preview_created)
        skipped.extend(preview_skipped)
    else:
        scaffold = create_problem_dir(
            data.oj,
            data.problem_dir_id,
            display_problem_id=data.problem_id,
            title=data.title,
            source=data.source,
            repo_root=repo_root,
            problems_root=problems_root,
        )
        created.extend(relative_to_repo(path, repo_root) for path in scaffold.created)
        skipped.extend(relative_to_repo(path, repo_root) for path in scaffold.skipped)

    output_written, output_skipped = write_fetch_outputs(problem_dir, data, args, repo_root=repo_root)
    written.extend(output_written)
    skipped.extend(output_skipped)

    warnings = list(dict.fromkeys(result.warnings + data.warnings))
    payload = {
        "ok": True,
        "fetched": result.fetched,
        "oj": data.oj,
        "problem_id": data.problem_id,
        "problem_dir_id": data.problem_dir_id,
        "problem_dir": relative_to_repo(problem_dir, repo_root),
        "title": data.title,
        "source": data.source,
        "created": created,
        "skipped": skipped,
        "written": written,
        "warnings": warnings,
        "dry_run": args.dry_run,
    }
    return payload


def print_human(payload: dict[str, Any]) -> None:
    print(f"OJ: {payload['oj']}")
    print(f"Problem: {payload['problem_id']}")
    print(f"Directory: {payload['problem_dir']}")
    print(f"Fetched: {'yes' if payload['fetched'] else 'no'}")
    if payload.get("title"):
        print(f"Title: {payload['title']}")
    if payload.get("source"):
        print(f"Source: {payload['source']}")
    for key, label in [("created", "Created"), ("written", "Written"), ("skipped", "Skipped")]:
        items = payload.get(key) or []
        if items:
            print(f"{label}:")
            for item in items:
                print(f"- {item}")
    warnings = payload.get("warnings") or []
    if warnings:
        print("Warnings:")
        for item in warnings:
            print(f"- {item}")


def make_luogu_fixture() -> str:
    fixture_data = {
        "data": {
            "problem": {
                "title": "A+B Problem",
                "background": "",
                "description": "输入两个整数 a,b，输出它们的和。",
                "formatI": "一行两个整数 a,b。",
                "formatO": "一个整数，表示 a+b。",
                "samples": [["1 2\n", "3\n"]],
                "hint": "保证答案在 int 范围内。",
            }
        }
    }
    return (
        '<html><body><script id="lentille-context" type="application/json">'
        + json.dumps(fixture_data, ensure_ascii=False)
        + "</script></body></html>"
    )


def run_self_test() -> int:
    from fetchers.kattis import KattisFetcher
    from fetchers.luogu import LuoguFetcher

    fetcher = LuoguFetcher()
    fixture_path = SCRIPT_DIR / "tests" / "fixtures" / "luogu_p1001.html"
    fixture_html = fixture_path.read_text(encoding="utf-8") if fixture_path.exists() else make_luogu_fixture()
    data = fetcher.parse_html(fixture_html, "P1001")
    with tempfile.TemporaryDirectory() as tmp:
        tmp_root = Path(tmp)
        problems_root = tmp_root / "problems"
        scaffold = create_problem_dir(
            data.oj,
            data.problem_dir_id,
            display_problem_id=data.problem_id,
            title=data.title,
            source=data.source,
            repo_root=tmp_root,
            problems_root=problems_root,
        )
        problem_dir = scaffold.problem_dir
        test_args = argparse.Namespace(
            force_statement=False,
            force_samples=False,
            force_index_meta=False,
            dry_run=False,
        )
        write_fetch_outputs(problem_dir, data, test_args, repo_root=tmp_root)
        problem_statement = (problem_dir / "problem.md").read_text(encoding="utf-8")
        checks = [
            problem_dir.name == "1001",
            (problem_dir / "index.md").exists(),
            'description: ""' in (problem_dir / "index.md").read_text(encoding="utf-8"),
            "recommend: []" in (problem_dir / "index.md").read_text(encoding="utf-8"),
            problem_statement.startswith("# P1001 A+B Problem"),
            "## 输入格式\n\n一行两个整数 a,b。" in problem_statement,
            "## 输出格式\n\n一个整数，表示 a+b。" in problem_statement,
            (problem_dir / "in1").read_text(encoding="utf-8") == "1 2\n",
            (problem_dir / "out1").read_text(encoding="utf-8") == "3\n",
            (problem_dir / "brute.cpp").exists(),
            (problem_dir / "gen.py").exists(),
            (problem_dir / "problem-analysis-workspace").is_dir(),
        ]
        if not all(checks):
            print("self-test failed")
            return 1
    kattis_fetcher = KattisFetcher()
    kattis_hello_html = (SCRIPT_DIR / "tests" / "fixtures" / "kattis_hello.html").read_text(encoding="utf-8")
    kattis_hello = kattis_fetcher.parse_html(kattis_hello_html, "hello")
    kattis_r2_html = (SCRIPT_DIR / "tests" / "fixtures" / "kattis_r2.html").read_text(encoding="utf-8")
    kattis_r2 = kattis_fetcher.parse_html(kattis_r2_html, "r2")
    kattis_checks = [
        kattis_hello.oj == "kattis",
        kattis_hello.problem_id == "hello",
        kattis_hello.problem_dir_id == "hello",
        kattis_hello.title == "Hello World!",
        len(kattis_hello.samples) == 0,
        "## 输入格式\n\nThere is no input for this problem." in kattis_hello.statement_md,
        "## 输出格式\n\nOutput should contain one line" in kattis_hello.statement_md,
        kattis_r2.title == "R2",
        len(kattis_r2.samples) == 2,
        kattis_r2.samples[0].input == "11 15",
        kattis_r2.samples[1].output == "2",
        "## 题目描述\n\nThe number $S$ is called" in kattis_r2.statement_md,
        "## 输入输出样例 #2" in kattis_r2.statement_md,
    ]
    if not all(kattis_checks):
        print("self-test failed")
        return 1
    print("self-test passed")
    return 0


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Fetch an online judge problem into problems/<oj>/<problem_id>/"
    )
    parser.add_argument("target", nargs="*", help="<oj> <problem_id> or <url>")
    parser.add_argument("--init", action="store_true", help="兼容旧计划；默认已经会创建/补齐题目目录")
    parser.add_argument("--dry-run", action="store_true", help="只展示将要写入的路径，不实际写文件")
    parser.add_argument("--json", action="store_true", help="输出 JSON，方便 agent 或脚本调用")
    parser.add_argument("--force-statement", action="store_true", help="允许覆盖 problem.md")
    parser.add_argument("--force-samples", action="store_true", help="允许覆盖 in*/out* 样例文件")
    parser.add_argument(
        "--force-index-meta",
        action="store_true",
        help="只更新 index.md frontmatter 中的 title/source，不修改正文",
    )
    parser.add_argument("--self-test", action="store_true", help="运行离线 fixture 自测")
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    if args.self_test:
        return run_self_test()
    try:
        payload = run_fetch(args)
    except FetchProblemError as exc:
        payload = {"ok": False, "error": str(exc)}
        if args.json:
            print(json.dumps(payload, ensure_ascii=False, indent=2))
        else:
            print(str(exc), file=sys.stderr)
        return 2

    if args.json:
        print(json.dumps(payload, ensure_ascii=False, indent=2))
    else:
        print_human(payload)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
