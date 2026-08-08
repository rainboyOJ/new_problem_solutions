#!/usr/bin/env python3
"""Rename Luogu numeric problem directories to the canonical P-prefixed form."""

from __future__ import annotations

import argparse
from pathlib import Path
import re


REPO_ROOT = Path(__file__).resolve().parents[1]
DEFAULT_ROOT = REPO_ROOT / "problems" / "luogu"
NUMERIC_DIR_RE = re.compile(r"^[0-9]+$")


def planned_moves(root: Path) -> list[tuple[Path, Path]]:
    if not root.exists():
        raise FileNotFoundError(root)
    if not root.is_dir():
        raise NotADirectoryError(root)

    sources = sorted(
        (entry for entry in root.iterdir() if entry.is_dir() and NUMERIC_DIR_RE.fullmatch(entry.name)),
        key=lambda entry: (int(entry.name), entry.name),
    )
    moves = [(source, root / f"P{source.name}") for source in sources]
    source_set = {source for source, _target in moves}
    collisions = [target for _source, target in moves if target.exists() and target not in source_set]
    if collisions:
        names = ", ".join(str(path) for path in collisions)
        raise FileExistsError(f"target directories already exist: {names}")
    return moves


def display_path(path: Path, root: Path) -> str:
    try:
        return str(path.relative_to(root.parent.parent))
    except ValueError:
        return str(path)


def migrate(root: Path, *, apply: bool, verbose: bool) -> int:
    moves = planned_moves(root)
    mode = "apply" if apply else "dry-run"
    print(f"mode: {mode}")
    print(f"root: {root}")
    print(f"numeric directories: {len(moves)}")

    if verbose:
        for source, target in moves:
            print(f"{display_path(source, root)} -> {display_path(target, root)}")
    elif moves:
        preview = moves[:3]
        for source, target in preview:
            print(f"  {source.name} -> {target.name}")
        if len(moves) > len(preview):
            print(f"  ... {len(moves) - len(preview)} more")

    if not apply:
        print("dry-run complete; rerun with --apply to rename directories")
        return 0

    for source, target in moves:
        source.rename(target)
    print(f"renamed: {len(moves)}")
    return 0


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--root", type=Path, default=DEFAULT_ROOT)
    parser.add_argument("--apply", action="store_true", help="perform the renames")
    parser.add_argument("--verbose", action="store_true", help="print every planned move")
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    try:
        return migrate(args.root.resolve(), apply=args.apply, verbose=args.verbose)
    except (FileExistsError, FileNotFoundError, NotADirectoryError) as exc:
        print(f"error: {exc}")
        return 2


if __name__ == "__main__":
    raise SystemExit(main())
