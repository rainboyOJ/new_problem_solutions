#!/usr/bin/env python3
"""Generate and update standard C++ headers for OJ solution files."""

from __future__ import annotations

import argparse
import datetime as dt
from pathlib import Path
import re


TIME_FORMAT = "%Y-%m-%d %H:%M"
TOP_HEADER_RE = re.compile(r"\A/\*\*.*?\*/\s*", re.S)
FIELD_RE = re.compile(
    r"^\s*\*\s*(?P<name>create_at|date)\s*:\s*"
    r"(?P<value>\d{4}-\d{2}-\d{2} \d{2}:\d{2})(?::\d{2})?\s*$",
    re.M,
)


def format_cpp_time(value: dt.datetime | str | None = None) -> str:
    if value is None:
        return dt.datetime.now().strftime(TIME_FORMAT)
    if isinstance(value, dt.datetime):
        return value.strftime(TIME_FORMAT)
    return value[:16]


def build_cpp_header(
    create_at: dt.datetime | str | None = None,
    update_at: dt.datetime | str | None = None,
    *,
    now: dt.datetime | None = None,
) -> str:
    base_time = now or dt.datetime.now()
    create_text = format_cpp_time(create_at or base_time)
    update_text = format_cpp_time(update_at or base_time)
    return f"""/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: {create_text}
 * update_at: {update_text}
 */
"""


def extract_create_at(header: str) -> str | None:
    for match in FIELD_RE.finditer(header):
        if match.group("name") in {"create_at", "date"}:
            return match.group("value")
    return None


def replace_or_insert_header(
    content: str,
    *,
    now: dt.datetime | None = None,
    create_at: dt.datetime | str | None = None,
    update_at: dt.datetime | str | None = None,
) -> str:
    base_time = now or dt.datetime.now()
    match = TOP_HEADER_RE.match(content)

    old_create_at = None
    body = content
    if match is not None:
        old_header = match.group(0)
        if "Author by Rainboy" in old_header:
            old_create_at = extract_create_at(old_header)
            body = content[match.end():]

    header = build_cpp_header(
        create_at=create_at or old_create_at or base_time,
        update_at=update_at or base_time,
    )
    return header + body


def update_cpp_header(path: Path, *, now: dt.datetime | None = None) -> bool:
    content = path.read_text(encoding="utf-8")
    updated = replace_or_insert_header(content, now=now)
    if updated == content:
        return False
    path.write_text(updated, encoding="utf-8")
    return True


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description="Generate or update standard C++ headers.")
    parser.add_argument("paths", nargs="*", type=Path, help="C++ files to update in place.")
    parser.add_argument("--print", dest="print_header", action="store_true", help="Print a fresh header.")
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    if args.print_header:
        print(build_cpp_header(), end="")

    if not args.paths:
        return 0 if args.print_header else 2

    for path in args.paths:
        changed = update_cpp_header(path)
        status = "updated" if changed else "unchanged"
        print(f"{status}: {path}")

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
