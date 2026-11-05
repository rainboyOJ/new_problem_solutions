"""Locate the Scriba checkout and put it on ``sys.path``.

Scriba is a separate repository on this machine, not a dependency of rbook, so
the skills cannot ``import scriba`` blind. Resolution order:

1. ``--scriba-root`` (handled by the caller, which then calls :func:`use`)
2. ``$SCRIBA_ROOT``
3. ``~/__git__/scriba``
4. any ``scriba`` package already importable

:func:`use` returns the resolved root and makes ``render.py`` + the ``scriba``
package importable from it.
"""
from __future__ import annotations

import os
import sys
from pathlib import Path

DEFAULT_ROOT = Path("~/__git__/scriba")


def resolve(explicit: Path | None = None) -> Path | None:
    """Return the Scriba checkout root, or ``None`` if already importable."""
    for candidate in (
        explicit,
        Path(os.environ["SCRIBA_ROOT"]).expanduser() if os.environ.get("SCRIBA_ROOT") else None,
        DEFAULT_ROOT.expanduser(),
    ):
        if candidate and (candidate / "scriba" / "__init__.py").is_file():
            return candidate
    try:  # already installed (pip / a plain checkout earlier on sys.path)
        import scriba  # noqa: F401
    except ImportError:
        return None
    return Path("")


def use(explicit: Path | None = None) -> Path:
    """Make the checkout importable and return its root; exit(2) if missing."""
    root = resolve(explicit)
    if root is None:
        sys.exit(
            "error: cannot find a Scriba checkout.\n"
            "  Set SCRIBA_ROOT=/path/to/scriba, pass --scriba-root, or clone it to\n"
            f"  {DEFAULT_ROOT.expanduser()}"
        )
    if root != Path("") and str(root) not in sys.path:
        sys.path.insert(0, str(root))
    if not (root / "render.py").is_file():
        sys.exit(f"error: {root / 'render.py'} not found — that is not a Scriba checkout")
    return root
