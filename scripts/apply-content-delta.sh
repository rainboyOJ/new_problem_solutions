#!/usr/bin/env bash
set -euo pipefail

BASE_DIR="${1:?missing base content directory}"
TARGET_DIR="${2:?missing target content directory}"
ARCHIVE="${3:?missing content delta archive}"
CHANGED_LIST="${4:?missing changed-path list}"
DELETED_LIST="${5:?missing deleted-path list}"
CONTENT_SHA="${6:?missing content SHA}"

[[ "$CONTENT_SHA" =~ ^[0-9a-f]{40}$ ]] || { echo "invalid content SHA" >&2; exit 2; }
[[ -d "$BASE_DIR/problems" && -d "$BASE_DIR/problem-sets" ]] \
  || { echo "base content snapshot is incomplete: $BASE_DIR" >&2; exit 1; }
[[ ! -e "$TARGET_DIR" ]] || { echo "target content directory already exists: $TARGET_DIR" >&2; exit 1; }

mkdir -p "$TARGET_DIR"
cp -al "$BASE_DIR/." "$TARGET_DIR/"

python3 - "$TARGET_DIR" "$CHANGED_LIST" "$DELETED_LIST" <<'PY'
import os
from pathlib import Path
import shutil
import sys

target = Path(sys.argv[1]).resolve()

for manifest_name in sys.argv[2:]:
    for raw_path in Path(manifest_name).read_bytes().split(b'\0'):
        if not raw_path:
            continue
        relative = os.fsdecode(raw_path)
        parts = Path(relative).parts
        valid_root = parts and parts[0] in {'problems', 'problem-sets'}
        if relative != 'content.env' and not valid_root:
            raise SystemExit(f'unsafe content delta path: {relative!r}')
        if Path(relative).is_absolute() or any(part in {'', '.', '..'} for part in parts):
            raise SystemExit(f'unsafe content delta path: {relative!r}')

        destination = target.joinpath(*parts)
        try:
            destination.relative_to(target)
        except ValueError:
            raise SystemExit(f'content delta escaped target: {relative!r}')

        if destination.is_dir() and not destination.is_symlink():
            shutil.rmtree(destination)
        else:
            destination.unlink(missing_ok=True)
PY

zstd -dc "$ARCHIVE" | tar --unlink-first -xf - -C "$TARGET_DIR"
find "$TARGET_DIR/problems" "$TARGET_DIR/problem-sets" -depth -mindepth 1 -type d -empty -delete

[[ -d "$TARGET_DIR/problems" && -d "$TARGET_DIR/problem-sets" ]] \
  || { echo "assembled content snapshot is incomplete" >&2; exit 1; }
grep -qx "PROBLEMS_SOLUTION_CONTENT_SHA=$CONTENT_SHA" "$TARGET_DIR/content.env"
