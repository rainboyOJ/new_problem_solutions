"""Locate the Scriba checkout and put it on ``sys.path``.

Scriba is a separate repository on this machine, not a dependency of rbook, so
the skills cannot ``import scriba`` blind. Resolution order, first hit wins:

1. ``--scriba-root PATH``  — explicit; must be valid or we stop.
2. ``$SCRIBA_ROOT``        — explicit; must be valid or we stop.
3. ``~/__git__/scriba``    — the default checkout on this machine.
4. ``import scriba``       — an installed package or a checkout already on
   ``sys.path``.

An explicitly named root that is not a Scriba checkout is a hard error: silently
falling back to a *different* checkout would render with the wrong Scriba
version, and the version is part of the output contract.
"""
from __future__ import annotations

import os
import sys
from pathlib import Path

DEFAULT_ROOT = Path("~/__git__/scriba").expanduser()


def _is_checkout(path: Path) -> bool:
    return (path / "scriba" / "__init__.py").is_file() and (path / "render.py").is_file()


def use(explicit: Path | None = None) -> Path:
    """Make a Scriba checkout importable and return its root."""
    for label, candidate in (
        ("--scriba-root", explicit),
        ("SCRIBA_ROOT", Path(os.environ["SCRIBA_ROOT"]).expanduser()
         if os.environ.get("SCRIBA_ROOT") else None),
    ):
        if candidate is None:
            continue
        if not _is_checkout(candidate):
            sys.exit(f"error: {label}={candidate} is not a Scriba checkout "
                     "(needs scriba/__init__.py and render.py)")
        if str(candidate) not in sys.path:
            sys.path.insert(0, str(candidate))
        return candidate

    if _is_checkout(DEFAULT_ROOT):
        if str(DEFAULT_ROOT) not in sys.path:
            sys.path.insert(0, str(DEFAULT_ROOT))
        return DEFAULT_ROOT

    try:  # installed package (pip install scriba-tex) — render.py may be absent
        import scriba  # noqa: F401
    except ImportError:
        sys.exit(
            "error: cannot find a Scriba checkout.\n"
            f"  clone it to {DEFAULT_ROOT}, or set SCRIBA_ROOT=/path/to/scriba,"
            " or pass --scriba-root /path/to/scriba"
        )
    return Path(getattr(scriba, "__file__", "")).resolve().parent.parent
