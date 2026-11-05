#!/usr/bin/env python3
"""Render a Scriba .tex to an iframe-friendly HTML page.

``render.py`` writes a standalone *page*: a ``<h1>`` with the file name and a
floating theme-toggle button. That chrome is right for opening the file
directly and wrong inside an ``<iframe>`` in someone else's article, where the
heading repeats the surrounding caption and the toggle fights the host page.

This wrapper calls ``render_file`` and then removes that chrome, pins the
language, and trims the page margins so the widget fills its frame.

Usage:
    python3 embed.py input.tex -o out.html
    python3 embed.py input.tex -o out.html --lang zh-CN
"""
from __future__ import annotations

import argparse
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))

import scriba_root  # noqa: E402

# Injected page rules: the standalone sheet sizes a document (h1 margins, a
# centred prose column); inside a frame the widget should sit flush.
EMBED_CSS = """
<style>
  /* scriba-standalone.css lays out a *document*: 720px max width, a grey
     page background, a 2rem top margin. Inside a frame the widget should
     just centre itself in whatever width the host gives us. */
  html, body {
    margin: 0;
    padding: 0;
    max-width: none;
    background: transparent;
  }
  body { padding: 0.25rem 0.5rem 0.75rem; }
  .scriba-widget { margin: 0 auto; }
</style>
"""


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("input", type=Path)
    ap.add_argument("--scriba-root", type=Path, default=None,
                    help="Scriba checkout (default: $SCRIBA_ROOT or ~/__git__/scriba)")
    ap.add_argument("-o", "--output", type=Path, required=True)
    ap.add_argument("--lang", default="zh-CN", help="BCP 47 tag for <html lang>")
    args = ap.parse_args()
    scriba_root.use(args.scriba_root)
    from render import render_file  # noqa: PLC0415  (needs the root on sys.path)

    render_file(args.input, args.output, lang=args.lang)
    html = args.output.read_text(encoding="utf-8")

    # Drop the standalone-only page chrome.
    html = re.sub(r"<button\b[^>]*data-scriba-action=\"theme-toggle\"[^>]*>.*?</button>\s*",
                  "", html, count=1, flags=re.S)
    html = re.sub(r"<h1>.*?</h1>\s*", "", html, count=1, flags=re.S)
    # The word "theme-toggle" legitimately survives in the stylesheet and in
    # the delegated click listener — only the element itself is removed.
    if "<h1>" in html or "data-scriba-action=\"theme-toggle\"" in html:
        print("warning: page chrome not fully removed; inspect the output",
              file=sys.stderr)

    # The widget measures itself against the frame width, so tell the page it
    # is a frame: no scrollbar, no 100vh assumptions.
    html = html.replace("</head>", f"{EMBED_CSS}</head>", 1)
    args.output.write_text(html, encoding="utf-8")

    kb = len(html.encode("utf-8")) / 1024
    print(f"wrote {args.output} ({kb:.0f} KB, iframe-ready)")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
