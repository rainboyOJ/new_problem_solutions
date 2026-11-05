#!/usr/bin/env python3
"""Print Scriba's authoritative primitive parameter list.

Scriba validates ``\\shape`` parameters against each primitive's
``ACCEPTED_PARAMS``; a wrong name is a hard error (E1114) naming the valid set.
This dumps the same source of truth so a figure can be written without a
guess-and-render loop.

Usage:
    python3 params.py            # one primitive per line
    python3 params.py Stack      # just one (accepts any case)
"""
from __future__ import annotations

import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))

import scriba_root  # noqa: E402

def main() -> int:
    scriba_root.use()
    import scriba.animation.renderer as R  # noqa: PLC0415

    catalog = R._get_catalog()
    want = sys.argv[1].lower() if len(sys.argv) > 1 else None
    hits = 0
    for name in sorted(catalog):
        if want and name.lower() != want:
            continue
        params = getattr(catalog[name], "ACCEPTED_PARAMS", None)
        print(f"{name:16} {' '.join(sorted(params)) if params else '?'}")
        hits += 1
    if not hits:
        print(f"error: no primitive named {sys.argv[1]!r}", file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
