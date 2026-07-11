#!/usr/bin/env python3
"""Download official USACO test data into a problem directory."""

from __future__ import annotations

import argparse
from io import BytesIO
import json
from pathlib import Path, PurePosixPath
import re
import sys
import zipfile


SCRIPT_DIR = Path(__file__).resolve().parent
REPO_ROOT = SCRIPT_DIR.parents[1]
PROBLEMS_ROOT = REPO_ROOT / "problems"
for import_path in (SCRIPT_DIR, REPO_ROOT):
    if str(import_path) not in sys.path:
        sys.path.insert(0, str(import_path))

from fetchers import FetchError  # noqa: E402
from fetchers.usaco import USACOFetcher, canonical_cpid  # noqa: E402
from problem_scaffold import relative_to_repo  # noqa: E402


class USACOTestDataError(RuntimeError):
    pass


def rel(path: Path) -> str:
    return relative_to_repo(path, REPO_ROOT)


def infer_problem_dir_from_cwd() -> Path | None:
    try:
        relative = Path.cwd().resolve().relative_to(PROBLEMS_ROOT)
    except ValueError:
        return None
    if len(relative.parts) >= 2 and relative.parts[0] == "usaco":
        return PROBLEMS_ROOT / relative.parts[0] / relative.parts[1]
    return None


def resolve_target(target: str | None) -> tuple[str, Path]:
    if not target:
        problem_dir = infer_problem_dir_from_cwd()
        if problem_dir is None:
            raise USACOTestDataError(
                "未指定目标，且当前目录不在 problems/usaco/<cpid>/ 下。"
            )
        return canonical_cpid(problem_dir.name), problem_dir

    if target.startswith(("http://", "https://")):
        fetcher = USACOFetcher()
        _oj, cpid = fetcher.parse_url(target)
        return cpid, PROBLEMS_ROOT / "usaco" / cpid

    path = Path(target)
    if path.exists() and path.is_dir():
        problem_dir = path.resolve()
        try:
            relative = problem_dir.relative_to(PROBLEMS_ROOT)
        except ValueError as exc:
            raise USACOTestDataError(
                f"题目目录必须位于 problems/usaco/<cpid>/ 下：{target}"
            ) from exc
        if len(relative.parts) < 2 or relative.parts[0] != "usaco":
            raise USACOTestDataError(f"不是 USACO 题目目录：{target}")
        return canonical_cpid(relative.parts[1]), problem_dir

    if re.fullmatch(r"(?:cpid)?\d+", target, flags=re.I):
        cpid = canonical_cpid(target)
        return cpid, PROBLEMS_ROOT / "usaco" / cpid

    raise USACOTestDataError(
        "目标必须是 USACO cpid、题目 URL，或 problems/usaco/<cpid>/ 目录。"
    )


def safe_zip_name(raw_name: str) -> str | None:
    name = raw_name.replace("\\", "/")
    path = PurePosixPath(name)
    if path.is_absolute() or any(part == ".." for part in path.parts):
        raise USACOTestDataError(f"zip 中存在不安全路径：{raw_name}")
    if not path.name or path.name.startswith(".") or "__MACOSX" in path.parts:
        return None
    if path.suffix.lower() not in {".in", ".out", ".ans"}:
        return None
    return path.name


def normalize_text_bytes(data: bytes) -> str:
    return data.decode("utf-8", errors="replace").replace("\r\n", "\n").replace("\r", "\n")


def write_testdata_zip(
    zip_bytes: bytes,
    data_dir: Path,
    *,
    force: bool,
    dry_run: bool,
) -> tuple[list[str], list[str]]:
    written: list[str] = []
    skipped: list[str] = []
    used_names: set[str] = set()

    try:
        archive = zipfile.ZipFile(BytesIO(zip_bytes))
    except zipfile.BadZipFile as exc:
        raise USACOTestDataError("下载内容不是合法 zip 文件。") from exc

    with archive:
        for info in archive.infolist():
            if info.is_dir():
                continue
            filename = safe_zip_name(info.filename)
            if filename is None:
                skipped.append(info.filename)
                continue
            if filename in used_names:
                raise USACOTestDataError(f"zip 解压后文件名冲突：{filename}")
            used_names.add(filename)

            target = data_dir / filename
            if target.exists() and not force:
                skipped.append(rel(target))
                continue
            if not dry_run:
                data_dir.mkdir(parents=True, exist_ok=True)
                target.write_text(normalize_text_bytes(archive.read(info)), encoding="utf-8")
            written.append(rel(target))

    if not written and not skipped:
        raise USACOTestDataError("zip 中没有找到 .in/.out/.ans 测试数据。")
    return written, skipped


def fetch_usaco_testdata(args: argparse.Namespace) -> dict[str, object]:
    cpid, problem_dir = resolve_target(args.target)
    if not problem_dir.exists() and not args.dry_run:
        raise USACOTestDataError(
            f"题目目录不存在：{rel(problem_dir)}，请先运行 fetch_problem usaco {cpid}。"
        )

    fetcher = USACOFetcher()
    try:
        links = fetcher.fetch_asset_links(cpid)
        zip_bytes, _charset = fetcher.http_get_bytes(links.testdata_url, timeout=args.timeout)
    except FetchError as exc:
        raise USACOTestDataError(str(exc)) from exc

    written, skipped = write_testdata_zip(
        zip_bytes,
        problem_dir / "data",
        force=args.force,
        dry_run=args.dry_run,
    )

    return {
        "ok": True,
        "cpid": cpid,
        "problem_dir": rel(problem_dir),
        "data_dir": rel(problem_dir / "data"),
        "result_url": links.result_url,
        "testdata_url": links.testdata_url,
        "solution_url": links.solution_url,
        "written": written,
        "skipped": skipped,
        "dry_run": args.dry_run,
    }


def print_human(payload: dict[str, object]) -> None:
    print(f"USACO cpid: {payload['cpid']}")
    print(f"Directory: {payload['problem_dir']}")
    print(f"Data dir: {payload['data_dir']}")
    print(f"Test data: {payload['testdata_url']}")
    print(f"Solution: {payload['solution_url']}")
    written = payload.get("written") or []
    if written:
        print("Written:")
        for item in written:
            print(f"- {item}")
    skipped = payload.get("skipped") or []
    if skipped:
        print("Skipped:")
        for item in skipped:
            print(f"- {item}")


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Download official USACO test data into problems/usaco/<cpid>/data/"
    )
    parser.add_argument(
        "target",
        nargs="?",
        help="USACO cpid, problem URL, problem directory, or omit inside a USACO problem dir",
    )
    parser.add_argument("--force", action="store_true", help="overwrite existing data files")
    parser.add_argument("--dry-run", action="store_true", help="show paths without writing files")
    parser.add_argument("--json", action="store_true", help="print machine-readable JSON")
    parser.add_argument("--timeout", type=int, default=30, help="network timeout in seconds")
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    try:
        payload = fetch_usaco_testdata(args)
    except USACOTestDataError as exc:
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
