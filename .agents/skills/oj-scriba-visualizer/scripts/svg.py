#!/usr/bin/env python3
"""Render a Scriba .tex (diagram or one frame) to a standalone .svg.

Scriba emits SVG that is styled by its companion CSS (state classes such as
``scriba-state-current``). A bare .svg dropped into a website that does not
ship scriba-scene-primitives.css paints everything in fallback grey, so this
tool bakes the needed rules into a ``<style>`` block inside the SVG.

Usage:
    python3 svg.py input.tex -o out.svg
    python3 svg.py input.tex -o out.svg --frame 2
"""
from __future__ import annotations

import argparse
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))

import scriba_root  # noqa: E402

CSS_FILES = ("scriba-scene-primitives.css",)

# Rules the primitives sheet never carries because a hosted page supplies
# them: the SVG inherits the document font, and the stage svg is a flex
# child sized by its parent. Inside a standalone .svg there is no document
# and no parent, so the host font stack and an intrinsic width must be
# stated here or every <text> would fall back to the rasterizer's default.
SVG_OWN_CSS = """
svg.scriba-standalone {
  font-family: "Scriba Sans", -apple-system, BlinkMacSystemFont, "Segoe UI",
               Roboto, "Noto Sans CJK SC", "Source Han Sans SC", sans-serif;
  font-size: 14px;
}
svg.scriba-standalone text { font-family: inherit; }
"""


def _used_classes(svg: str) -> set[str]:
    used: set[str] = set()
    for m in re.finditer(r'class="([^"]+)"', svg):
        used.update(m.group(1).split())
    return used


def _used_primitives(svg: str) -> set[str]:
    return set(re.findall(r'data-primitive="([^"]+)"', svg))


def _split_blocks(css: str) -> list[tuple[str, str]]:
    """Split a stylesheet into (prelude, body) pairs by brace matching.

    A regex cannot do this: ``@media`` wrappers nest braces, and a comment or
    prelude may legitimately contain braces. Comments must already be gone.
    """
    blocks: list[tuple[str, str]] = []
    i, n = 0, len(css)
    while i < n:
        depth_open = css.find("{", i)
        if depth_open < 0:
            break
        prelude = css[i:depth_open]
        depth, j = 0, depth_open
        while j < n:
            if css[j] == "{":
                depth += 1
            elif css[j] == "}":
                depth -= 1
                if depth == 0:
                    break
            j += 1
        blocks.append((prelude, css[depth_open + 1:j]))
        i = j + 1
    return blocks


def _drop_dark_blocks(css: str) -> str:
    """Keep only the light theme.

    A standalone .svg has no theme toggle, so the dark overrides are dead
    weight — and worse, ``:root:not([data-theme="light"])`` under
    ``prefers-color-scheme: dark`` would match and repaint a light figure in
    dark ink on a dark page.
    """
    kept: list[str] = []
    for prelude, body in _split_blocks(css):
        sel = prelude.strip()
        if "prefers-color-scheme: dark" in sel:
            continue
        if "data-theme" in sel and "light" not in sel.replace('[data-theme="light"]', ""):
            continue
        if 'data-theme="dark"' in sel or "data-theme='dark'" in sel:
            continue
        kept.append(f"{prelude}{{{body}}}" if sel.startswith("@") else f"{sel}{{{body}}}")
    return "\n".join(kept)


def _drop_unused_tokens(css: str) -> str:
    """Remove custom-property declarations nothing references (transitively)."""
    decls = re.findall(r'(--scriba-[\w-]+)\s*:\s*([^;]+);', css)
    roots = set(re.findall(r'var\((--scriba-[\w-]+)', css))
    live: set[str] = set()
    stack = list(roots)
    by_name = dict(decls)
    while stack:
        name = stack.pop()
        if name in live or name not in by_name:
            continue
        live.add(name)
        stack.extend(re.findall(r'var\((--scriba-[\w-]+)', by_name[name]))

    def _strip(m: re.Match[str]) -> str:
        return m.group(0) if m.group(1) in live else ""

    return re.sub(r'(--scriba-[\w-]+)\s*:\s*[^;]+;', _strip, css)


def _prune_css(css: str, used: set[str], prims: set[str],
               *, keep_tokens: set[str]) -> str:
    """Drop rule blocks whose class selectors are all unused.

    Token definitions (custom properties) are always kept: they are cheap,
    and a pruned rule can still reference one.
    """
    out: list[str] = []
    # Comments must go FIRST: the sheet documents usage in comments such as
    # ``svg { --scriba-diagram-font-scale: 1.3; }`` and those braces would
    # otherwise be parsed as real block boundaries.
    css = re.sub(r'/\*.*?\*/', '', css, flags=re.S)
    for prelude, body in _split_blocks(css):
        sel = prelude
        sel_clean = sel.strip()
        if not sel_clean:
            out.append(f"{sel}{{{body}}}")
            continue
        if '--' in body and ':' in body:
            out.append(f"{sel}{{{body}}}")      # token block: keep
            continue
        classes = set(re.findall(r'\.([\w-]+)', sel_clean))
        prim_refs = set(re.findall(
            r'\[data-primitive=(?:"|\')?([\w-]+)', sel_clean))
        if prim_refs and not (prim_refs & prims):
            continue                            # rule for an absent primitive
        if not classes:
            out.append(f"{sel}{{{body}}}")      # element/id/pseudo selector
            continue
        if classes & used or classes & keep_tokens:
            out.append(f"{sel}{{{body}}}")
    pruned = "\n".join(out)
    # Comments are the bulk of the sheet (design notes); they carry no style.
    pruned = re.sub(r'/\*.*?\*/', '', pruned, flags=re.S)
    # A standalone .svg carries one theme: the dark override blocks would
    # double the sheet and never match (no [data-theme] on the root).
    pruned = _drop_dark_blocks(pruned)
    pruned = _drop_unused_tokens(pruned)
    pruned = re.sub(r'\s*\n\s*', ' ', pruned)
    return pruned.strip() + "\n"


def _bake_css() -> str:
    from scriba.core.css_bundler import inline_text_font_css, load_css

    # The @font-face must come first: Scriba measures every cell/node/caption
    # text run against the shipped "Scriba Sans" advance table. Without the
    # embedded face a standalone .svg falls back to the viewer's font and the
    # measured widths — hence the column/row geometry — no longer fit.
    css = inline_text_font_css() + "\n" + load_css(*CSS_FILES)
    # The tokens are declared on :root; inside a standalone SVG there is no
    # <html>, so re-declare them on the <svg> root element.
    return css.replace(":root", "svg")


def _extract_svgs(html: str) -> list[str]:
    return re.findall(r"<svg\b.*?</svg>", html, re.DOTALL)


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("input", type=Path)
    ap.add_argument("--scriba-root", type=Path, default=None,
                    help="Scriba checkout (default: $SCRIBA_ROOT or ~/__git__/scriba)")
    ap.add_argument("-o", "--output", type=Path, required=True)
    ap.add_argument("--frame", type=int, default=None,
                    help="1-based frame index for an animation (default: first)")
    ap.add_argument("--compact", action="store_true",
                    help="drop CSS rules whose classes the SVG never uses")
    ap.add_argument("--no-plate", dest="plate", action="store_false",
                    help="do not paint an opaque background plate")
    ap.add_argument("--plate-color", default="#ffffff",
                    help="background plate colour (default #ffffff)")
    ap.add_argument("--scale", type=float, default=1.0,
                    help="multiply the published width/height (viewBox is "
                         "unchanged, so the artwork scales crisply)")
    args = ap.parse_args()
    scriba_root.use(args.scriba_root)
    from render import render_file  # noqa: PLC0415  (needs the root on sys.path)

    tmp = args.output.with_suffix(".scriba.html")
    render_file(args.input, tmp)
    svgs = _extract_svgs(tmp.read_text(encoding="utf-8"))
    tmp.unlink(missing_ok=True)
    if not svgs:
        print("error: no <svg> found in the rendered output", file=sys.stderr)
        return 1
    idx = (args.frame or 1) - 1
    if not 0 <= idx < len(svgs):
        print(f"error: --frame must be 1..{len(svgs)}", file=sys.stderr)
        return 1
    svg = svgs[idx]

    # Mark it standalone (some host stylesheets target .scriba-stage-svg
    # only inside a widget) and inline the baked stylesheet right after the
    # opening tag. Keep the existing class list — never emit a second
    # `class` attribute (that is not well-formed XML).
    css = SVG_OWN_CSS + _bake_css()
    if args.compact:
        css = _prune_css(css, _used_classes(svg), _used_primitives(svg),
                         keep_tokens={"scriba-annotation", "scriba-primitive-label"})
    svg = svg.replace('class="scriba-stage-svg',
                      'class="scriba-standalone scriba-stage-svg', 1)

    # An <img src="*.svg"> needs an intrinsic size or the browser falls back
    # to 300x150. Publish the viewBox size as width/height and drop the
    # widget-only max-width (the host page decides the display size).
    vb = re.search(r'viewBox="([\d.\- ]+)"', svg)
    if vb:
        x, y, w, h = (float(v) for v in vb.group(1).split())
        svg = re.sub(r'\sstyle="max-width:calc\([^"]*\)"', '', svg, count=1)
        svg = svg.replace(
            vb.group(0),
            f'{vb.group(0)} width="{w * args.scale:g}" '
            f'height="{h * args.scale:g}"', 1)
    # Scriba paints a white halo behind every caption so a label stays legible
    # over lines — that halo assumes a light page. As a bare <img> the SVG sits
    # on whatever background the host uses, and on a dark theme the halo
    # becomes a white outline around dark text. An opaque plate makes the
    # figure read identically in both themes.
    if args.plate and vb:
        plate = (f'<rect x="0" y="0" width="{w:g}" height="{h:g}" '
                 f'fill="{args.plate_color}"/>')
        svg = re.sub(r'(</title>)', r'\1' + plate, svg, count=1)
    if "<![CDATA[" in css or "]]>" in css:
        raise SystemExit("refusing: CSS contains a CDATA terminator")
    svg = svg.replace(">", f"><style><![CDATA[{css}]]></style>", 1)
    args.output.write_text(svg + "\n", encoding="utf-8")
    print(f"wrote {args.output} ({len(svg)} bytes, frame {idx + 1}/{len(svgs)})")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
