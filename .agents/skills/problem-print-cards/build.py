#!/usr/bin/env python3
"""把 OJ 题目排版成 A4 复习卡 PDF（typst 渲染）。

只用本地已入库的题目材料：
  problems/<oj>/<id>/problem.md   题面（结构化拆分：描述/输入/输出/样例/数据范围）
  problems/<oj>/<id>/index.md     frontmatter(title/difficulty/tags/source) + 正解/思路（做法来源）

用法（agent 面向）：
  # 1) 采集：扫题目、抽结构、写出 cards.json（agent 之后补 summary/typical 坑）
  python3 build.py collect --batch prints/demo --name "CSP-J 400 分题单" roj/10000 roj/1000 luogu/b2002

  # 2) 渲染：cards.json -> cards.typ -> demo.pdf
  python3 build.py render --batch prints/demo

  # 3) 一步到位（cards.json 已存在时保留 agent 字段，只刷新自动字段）
  python3 build.py build --batch prints/demo roj/10000 roj/1000

约定：本脚本不做任何题的算法推导；solution.approach 能从 index.md 的「正解/思路」
抽到就预填，抽不到留空并在索引表里标「待补」。
"""

from __future__ import annotations

import argparse
import datetime as dt
import json
import math
import os
import re
import subprocess
import sys
from pathlib import Path

SKILL_DIR = Path(__file__).resolve().parent
REPO_ROOT = SKILL_DIR.parents[2]
TEMPLATE = SKILL_DIR / "template.typ"

# 难度 -> 5 档方块数（洛谷档位原文）
DIFFICULTY_DOTS = {
    "入门": 1,
    "普及-": 2,
    "普及": 2,
    "普及+/提高-": 3,
    "普及/提高-": 3,
    "普及+/提高": 3,
    "提高": 4,
    "提高+/省选-": 4,
    "省选/NOI-": 5,
    "NOI/NOI+/CTSC": 5,
}

# tags 里属于「实现语言」而非「考察点」的标签
LANG_TAGS = {"python", "c++", "cpp", "c", "java", "go", "rust", "pascal", "py"}

SAMPLE_LIMIT = 3          # 样例最多保留几个（Q15 裁剪顺序）
SAMPLE_MAX_LINES = 12     # 单个样例框最多几行
SAMPLE_MAX_CHARS = 640    # 单个样例框最多几字符
COMPACT_MAX_LINES = 21    # 超过则整页排（一页一卡，可跨页）
COMPACT_DESC_CHARS = 340
FULL_DESC_CHARS = 900
CONSTRAINT_CHARS = 360

URL_TEMPLATES = {
    "luogu": "https://www.luogu.com.cn/problem/{id}",
    "roj": "https://roj.ac.cn/problem/{id}",
    "codeforces": "https://codeforces.com/problemset/problem/{id}",
    "atcoder": "https://atcoder.jp/contests/{id}",
    "leetcodecn": "https://leetcode.cn/problems/{id}/",
    "noi_openjudge": "https://noi.openjudge.cn/ch{id}/",
    "kattis": "https://open.kattis.com/problems/{id}",
    "shumeng": "https://oj.shumeng.tech/problem/{id}",
}


# --------------------------------------------------------------------------- #
# typst 标记生成
# --------------------------------------------------------------------------- #
ESC = {
    "\\": "\\\\",
    "#": "\\#",
    "*": "\\*",
    "_": "\\_",
    "@": "\\@",
    "~": "\\~",
    "<": "\\<",
    ">": "\\>",
    "[": "\\[",
    "]": "\\]",
    "`": "\\`",
}

MATH_MAP = {
    r"\leqslant": "<=", r"\geqslant": ">=", r"\le": "<=", r"\leq": "<=",
    r"\ge": ">=", r"\geq": ">=", r"\neq": "!=", r"\ne": "!=", r"\lt": "<", r"\gt": ">",
    r"\times": "times", r"\cdot": "dot.op", r"\div": "div", r"\dots": "dots",
    r"\ldots": "dots.h", r"\cdots": "dots.h", r"\vdots": "dots.v", r"\sum": "sum",
    r"\prod": "prod", r"\int": "integral", r"\to": "->", r"\rightarrow": "->",
    r"\longrightarrow": "->", r"\leftarrow": "<-", r"\Rightarrow": "=>",
    r"\Leftrightarrow": "<=>", r"\infty": "oo", r"\pm": "plus.minus",
    r"\mp": "minus.plus", r"\lfloor": "floor.l", r"\rfloor": "floor.r",
    r"\lceil": "ceil.l", r"\rceil": "ceil.r", r"\lvert": "|", r"\rvert": "|",
    r"\vert": "|", r"\mid": "|", r"\bmod": "mod", r"\mod": "mod",
    r"\in": "in", r"\notin": "in.not", r"\subseteq": "subset.eq",
    r"\subset": "subset", r"\cup": "union", r"\cap": "sect", r"\emptyset": "emptyset",
    r"\forall": "forall", r"\exists": "exists", r"\equiv": "equiv", r"\approx": "approx",
    r"\oplus": "plus.circle", r"\otimes": "times.circle", r"\circ": "compose",
    r"\gcd": "gcd", r"\min": "min", r"\max": "max", r"\log": "log", r"\ln": "ln",
    r"\exp": "exp", r"\sin": "sin", r"\cos": "cos", r"\tan": "tan",
    r"\%": "percent", r"\&": "&", r"\quad": "space", r"\qquad": "space",
    r"\,": "thin", r"\;": "med", r"\!": "", r"\left": "", r"\right": "",
    r"\sim": "tilde", r"\propto": "prop", r"\ast": "star", r"\star": "star",
    r"\bullet": "bullet", r"\angle": "angle", r"\degree": "degree",
    r"\triangle": "triangle.stroked.t", r"\square": "square.stroked",
    r"\big": "", r"\Big": "", r"\bigl": "", r"\bigr": "",
}
STRIP_WRAPPERS = {"text", "mathrm", "operatorname", "mathbf", "mathit", "textit", "textbf", "mathcal", "mathbb"}

_FRAC_RE = re.compile(r"\\[dt]?frac\{([^{}]*)\}\{([^{}]*)\}")
_SQRT_RE = re.compile(r"\\sqrt\{([^{}]*)\}")
_CMD_RE = re.compile(r"\\([A-Za-z]+)")
_IDENT_RE = re.compile(r'(?<![\\\w."])([A-Za-z]{2,})(?![\w"])')
MATH_IDENTS = {
    "sqrt", "abs", "norm", "floor", "ceil", "round", "min", "max", "clamp", "mod", "rem",
    "quot", "gcd", "lcm", "log", "ln", "exp", "sin", "cos", "tan", "sum", "prod", "integral",
    "union", "sect", "subset", "in", "notin", "forall", "exists", "equiv", "approx", "prop",
    "tilde", "star", "bullet", "angle", "degree", "emptyset", "compose", "op", "upright",
    "bold", "italic", "serif", "sans", "mono", "text", "display", "inline", "limits", "scripts",
    "frac", "binom", "cases", "mat", "vec", "overline", "underline", "and", "or", "not",
    "true", "false", "none", "auto", "pt", "em", "fr", "si",
    "dots", "thin", "med", "space", "percent", "quot", "plus", "minus", "times", "div",
}


def latex_math(src: str) -> str:
    """把常见 LaTeX 数学转成 typst math（够用即可，不追求完备）。"""
    s = src
    for _ in range(4):
        new = _FRAC_RE.sub(lambda m: f"({m.group(1)})/({m.group(2)})", s)
        if new == s:
            break
        s = new
    s = _SQRT_RE.sub(lambda m: f"sqrt({m.group(1)})", s)
    s = re.sub(r"\\pmod\{([^{}]*)\}", r"(mod \1)", s)

    def repl(m: re.Match) -> str:
        key = "\\" + m.group(1)
        if key in MATH_MAP:
            return MATH_MAP[key]
        if m.group(1) in STRIP_WRAPPERS:
            return ""
        return f'"{m.group(1)}"'   # 未知命令：退化成直立文字，避免 typst 报 unknown variable

    s = _CMD_RE.sub(repl, s)
    s = s.replace("\\ ", " ")

    # 裸多字母标识符（如 i>reach、ans、cnt）：typst 数学里必须写成字符串
    def ident(m: re.Match) -> str:
        word = m.group(1)
        if word.lower() in MATH_IDENTS or "." in word:
            return word
        return f'"{word}"'

    s = _IDENT_RE.sub(ident, s)
    return s


def inline_md(text: str, img_dir: Path | None = None) -> str:
    """行内 markdown -> typst markup。"""
    out: list[str] = []
    i, n = 0, len(text)
    while i < n:
        c = text[i]
        if c == "`":
            j = text.find("`", i + 1)
            if j == -1:
                out.append(ESC["`"])
                i += 1
                continue
            code = text[i + 1:j].replace("`", "")
            out.append("`" + code + "`")
            i = j + 1
            continue
        if c == "$":
            j = text.find("$", i + 1)
            if j == -1:
                out.append("\\$")
                i += 1
                continue
            out.append("$" + latex_math(text[i + 1:j]) + "$")
            i = j + 1
            continue
        if text.startswith("**", i) or text.startswith("__", i):
            mark = text[i:i + 2]
            j = text.find(mark, i + 2)
            if j != -1:
                out.append("*" + inline_md(text[i + 2:j], img_dir) + "*")
                i = j + 2
                continue
        if text.startswith("![", i):
            m = re.match(r"!\[([^\]]*)\]\(([^)]+)\)", text[i:])
            if m:
                out.append(_image(m.group(2), img_dir))
                i += m.end()
                continue
        if c == "[":
            m = re.match(r"\[([^\]]*)\]\(([^)]+)\)", text[i:])
            if m:
                out.append(
                    '#link("' + m.group(2).replace('"', "") + '")[' + inline_md(m.group(1), img_dir) + "]"
                )
                i += m.end()
                continue
        out.append(ESC.get(c, c))
        i += 1
    return "".join(out)


def _image(src: str, img_dir: Path | None) -> str:
    """图片引用 -> typst image()，路径写成相对仓库根的 /problems/... 形式。"""
    p = Path(src)
    if not p.is_absolute():
        p = (img_dir or Path.cwd()) / src.lstrip("./")
    p = p.resolve()
    if not p.exists():
        return text_quote(f"［图片缺失：{src}］")
    try:
        rel = p.relative_to(REPO_ROOT)
        typ_path = "/" + rel.as_posix()
    except ValueError:
        typ_path = os.path.relpath(p, REPO_ROOT).as_posix()
    return f'#block(breakable: false)[#image("{typ_path}", width: 94%)]'


def fix_trailing_backslash(line: str) -> str:
    """行尾的字面反斜杠会被 typst 当成换行/语法，统一改成 #("\\\\")。"""
    return re.sub(r"(\\+)\s*$", lambda m: '#("\\\\")' * (len(m.group(1)) // 2), line)


def text_quote(s: str) -> str:
    return '#text(fill: luma(150))[' + inline_md(s) + "]"


def md_to_typst(text: str, img_dir: Path | None = None) -> str:
    """块级 markdown -> typst markup。"""
    lines = text.replace("\r\n", "\n").split("\n")
    out: list[str] = []
    i = 0
    while i < len(lines):
        line = lines[i]
        fence = re.match(r"^\s*(`{3,}|~{3,})", line)
        if fence:
            mark = fence.group(1)
            body: list[str] = []
            i += 1
            while i < len(lines) and not lines[i].strip().startswith(mark):
                body.append(lines[i])
                i += 1
            i += 1
            fence_out = "```"
            while fence_out in "\n".join(body):
                fence_out += "`"
            out.append(fence_out + "\n" + "\n".join(body) + "\n" + fence_out)
            continue
        if re.match(r"^\s*<(?!/?b>|/?i>|br)", line):     # <video>/<img>/<div> 等
            m = re.search(r'src="([^"]+)"', line)
            out.append(_image(m.group(1), img_dir) if m else "")
            i += 1
            continue
        if re.match(r"^\s*@include-code", line):
            i += 1
            continue
        if re.match(r"^\s*(---+|\*\*\*+)\s*$", line):
            out.append('#line(length: 100%, stroke: 0.3pt + luma(180))')
            i += 1
            continue
        if re.match(r"^( {4,}|\t)", line) and not re.match(r"^\s*[-*+]\s|^\s*\d+[.)]\s", line):
            # 缩进代码块（ASCII 艺术、缩进样例等）：整块转成 raw，避免标记被当语法
            body: list[str] = []
            while i < len(lines) and (re.match(r"^( {4,}|\t)", lines[i]) or not lines[i].strip()):
                if not lines[i].strip() and (
                    i + 1 >= len(lines) or not re.match(r"^( {4,}|\t)", lines[i + 1])
                ):
                    break
                body.append(re.sub(r"^( {4}|\t)", "", lines[i]))
                i += 1
            fence_out = "```"
            blob = "\n".join(body)
            while fence_out in blob:
                fence_out += "`"
            out.append(fence_out + "\n" + blob + "\n" + fence_out)
            continue

        m = re.match(r"^(\s*)#{1,6}\s+(.*)$", line)
        if m:
            out.append(m.group(1) + "*" + inline_md(m.group(2), img_dir) + "*")
            i += 1
            continue
        m = re.match(r"^(\s*)[-*+]\s+(.*)$", line)
        if m:
            indent = " " * (len(m.group(1)) // 2 * 2)
            out.append(indent + "- " + inline_md(m.group(2), img_dir))
            i += 1
            continue
        m = re.match(r"^(\s*)\d+[.)]\s+(.*)$", line)
        if m:
            indent = " " * (len(m.group(1)) // 2 * 2)
            out.append(indent + "+ " + inline_md(m.group(2), img_dir))
            i += 1
            continue
        if line.lstrip().startswith("|"):
            cells = [c.strip() for c in line.strip().strip("|").split("|")]
            if all(re.fullmatch(r":?-{2,}:?", c) for c in cells if c):
                i += 1
                continue
            out.append(inline_md(" ｜ ".join(c for c in cells if c), img_dir))
            i += 1
            continue
        m = re.match(r"^\s*>\s?(.*)$", line)
        if m:
            out.append(inline_md(m.group(1), img_dir))
            i += 1
            continue
        out.append(fix_trailing_backslash(inline_md(line, img_dir)))
        i += 1
    return "\n".join(out).strip("\n")


# --------------------------------------------------------------------------- #
# 题目材料解析
# --------------------------------------------------------------------------- #
def read_frontmatter(path: Path) -> dict:
    if not path.exists():
        return {}
    raw = path.read_text(encoding="utf-8")
    m = re.match(r"^---\n(.*?)\n---\n?", raw, re.S)
    if not m:
        return {}
    fm: dict = {}
    for line in m.group(1).split("\n"):
        mm = re.match(r"^([a-z_]+):\s*(.*)$", line)
        if not mm:
            continue
        key, val = mm.group(1), mm.group(2).strip()
        if val.startswith("[") and val.endswith("]"):
            fm[key] = [v.strip().strip('"') for v in val[1:-1].split(",") if v.strip()]
        else:
            fm[key] = val.strip('"')
    return fm


def strip_frontmatter(raw: str) -> str:
    return re.sub(r"^---\n.*?\n---\n?", "", raw, count=1, flags=re.S)


def section_text(raw: str, names: list[str]) -> str:
    """取 index.md 里某个二级标题下的正文（首个非空段落片段）。"""
    lines = raw.split("\n")
    pat = re.compile(r"^##+\s*(" + "|".join(names) + r")\s*$")
    for idx, line in enumerate(lines):
        if pat.match(line):
            body: list[str] = []
            for nxt in lines[idx + 1:]:
                if re.match(r"^#{2,}\s", nxt) or re.match(r"^<!--", nxt):
                    break
                if nxt.strip().startswith("@include-code"):
                    continue
                body.append(nxt)
            text = "\n".join(body).strip()
            text = re.sub(r"```.*?```", "", text, flags=re.S)
            return text.strip()
    return ""


def first_sentences(text: str, limit: int = 210) -> str:
    text = re.sub(r"\s+", " ", text).strip()
    text = re.sub(r"\*\*|__", "", text)
    if not text:
        return ""
    if len(text) <= limit:
        return text
    cut = text[:limit]
    pos = max(cut.rfind("。"), cut.rfind("；"), cut.rfind(". "))
    if pos > 60:
        return cut[: pos + 1]
    return cut.rstrip() + "…"


HEAD_RULES = [
    ("_samples", r"(输入输出样例|样例)(\d*)"),
    ("_samples", r"(Samples?|Examples?)(\d*)"),
    ("description", r"(题目描述|问题描述|题目|描述|ProblemStatement|Description|Task)"),
    ("background", r"(题目背景|背景|前言|Background|Story)"),
    ("sample_in", r"(样例(\d*)输入|输入样例(\d*)|SampleInput(\d*)|ExampleInput(\d*))"),
    ("sample_out", r"(样例(\d*)输出|输出样例(\d*)|SampleOutput(\d*)|ExampleOutput(\d*))"),
    ("input", r"(输入格式|输入描述|Input|InputFormat)"),
    ("output", r"(输出格式|输出描述|Output|OutputFormat)"),
    ("constraints", r"(数据范围与提示|数据范围与约定|数据范围|提示|说明|约定|限制|约束|Constraints|Notes?|限制条件)"),
    ("_discard", r"(来源|题目来源|Source|时空限制|时间限制|Title|赛事信息|比赛信息|Info)"),
    ("sample_in", r"输入(\d+)"),
    ("sample_out", r"输出(\d+)"),
    ("input", r"输入"),
    ("output", r"输出"),
]


def canon_heading(title: str) -> tuple[str, int] | None:
    """标题 -> (规范 key, 样例序号)。无法归类的标题返回 None。"""
    t = re.sub(r"[【】\[\]#*\s:：]", "", title)
    for key, pattern in HEAD_RULES:
        m = re.fullmatch(pattern, t)
        if m:
            digits = next((g for g in m.groups() if g and g.isdigit()), "")
            return key, int(digits) if digits.isdigit() else 0
    return None


def parse_problem_md(raw: str) -> dict:
    """按标题把题面拆成 {描述, 输入, 输出, 样例[], 数据范围, 背景, 图片[]}。"""
    buckets: dict[tuple[str, int], list[str]] = {}
    cur = ("_preamble", 0)
    buckets[cur] = []
    for line in raw.split("\n"):
        m = re.match(r"^#{1,6}\s+(.*)$", line)
        if m:
            canon = canon_heading(m.group(1))
            if canon:
                key, num = canon
                if key in ("_samples", "_discard"):
                    cur = ("_discard", 0)        # 容器标题：正文丢弃，等子标题接管
                else:
                    cur = (key, num)
                buckets.setdefault(cur, [])
                continue
            continue    # 未识别的标题：忽略标题行，内容仍归当前小节
        buckets.setdefault(cur, []).append(line)

    def joined(key: str) -> str:
        return "\n".join(
            "\n".join(v) for (k, _), v in buckets.items() if k == key
        ).strip()

    by_key: dict[str, dict[int, str]] = {}
    for (k, num), v in buckets.items():
        by_key.setdefault(k, {})[num] = "\n".join(v).strip()

    description = by_key.get("description", {}).get(0, "").strip()
    if not description:
        description = "\n".join(
            l for l in buckets[("_preamble", 0)]
            if not l.strip().startswith(("![", "<", "# ", "---", "|"))
        ).strip()

    ins = by_key.get("sample_in", {})
    outs = by_key.get("sample_out", {})
    idxs = sorted(set(ins) | set(outs), key=lambda i: (i == 0, i))
    samples = [{"in": ins.get(i, ""), "out": outs.get(i, "")} for i in idxs]

    images = re.findall(r"!\[[^\]]*\]\(([^)]+)\)", raw)
    images += re.findall(r'<(?:img|video)[^>]*src="([^"]+)"', raw)
    has_video = bool(re.search(r"<video", raw))

    def clean(s: str) -> str:
        lines = [l for l in s.split("\n") if not re.match(r"^\s*(`{3,}|~{3,})", l)]
        return re.sub(r"\n{3,}", "\n\n", "\n".join(lines)).strip()

    return {
        "description": clean(description),
        "background": clean(joined("background")),
        "input": clean(joined("input")),
        "output": clean(joined("output")),
        "constraints": clean(joined("constraints")),
        "samples": [{"in": clean(s["in"]), "out": clean(s["out"])} for s in samples],
        "images": images,
        "has_video": has_video,
    }


# --------------------------------------------------------------------------- #
# 采集
# --------------------------------------------------------------------------- #
def parse_target(tok: str) -> tuple[str, str] | None:
    tok = tok.strip()
    if not tok:
        return None
    tok = tok.replace("https://", "http://")
    m = re.search(r"luogu\.com\.cn/problem/([A-Za-z0-9_]+)", tok)
    if m:
        return "luogu", m.group(1)
    m = re.search(r"roj\.ac\.cn/problem/(\d+)", tok)
    if m:
        return "roj", m.group(1)
    m = re.search(r"codeforces\.com/(?:problemset/problem|contest)/(\d+)/(?:problem/)?([A-Za-z0-9]+)", tok)
    if m:
        return "codeforces", f"{m.group(1)}/{m.group(2)}"
    m = re.search(r"atcoder\.jp/contests/([^/]+)/tasks/([^/?#\s]+)", tok)
    if m:
        return "atcoder", f"{m.group(1)}/{m.group(2)}"
    m = re.search(r"leetcode\.cn/problems/([^/?#\s]+)", tok)
    if m:
        return "leetcodecn", m.group(1)
    m = re.match(r"^([A-Za-z_][A-Za-z0-9_]*)[/# ]+([A-Za-z0-9_./-]+)$", tok)
    if m:
        oj = m.group(1)
        # oj 名以 problems/ 下真实目录为准（usaco、hdu 等没有 URL 模板也能用）
        if oj.lower() in URL_TEMPLATES or (REPO_ROOT / "problems" / oj).is_dir():
            return oj, m.group(2)
        if (REPO_ROOT / "problems" / oj.lower()).is_dir():
            return oj.lower(), m.group(2)
    return None


def pick_url(oj: str, pid: str, fm: dict) -> str:
    if fm.get("source"):
        return fm["source"]
    tpl = URL_TEMPLATES.get(oj)
    return tpl.format(id=pid) if tpl else ""


def collect_card(oj: str, pid: str) -> dict | None:
    pdir = REPO_ROOT / "problems" / oj / pid
    pmd = pdir / "problem.md"
    imd = pdir / "index.md"
    if not pmd.exists() and not imd.exists():
        return None
    fm = read_frontmatter(imd)
    raw_p = pmd.read_text(encoding="utf-8") if pmd.exists() else ""
    parsed = parse_problem_md(raw_p) if raw_p else {
        "description": "", "background": "", "input": "", "output": "",
        "constraints": "", "samples": [], "images": [], "has_video": False,
    }
    idx_raw = strip_frontmatter(imd.read_text(encoding="utf-8")) if imd.exists() else ""

    approach_raw = section_text(idx_raw, [r"正解", r"思路", r"题目解析", r"解法", r"分析"])
    approach = first_sentences(approach_raw, 200)
    complexity = ""
    cpx = section_text(idx_raw, [r"复杂度", r"复杂度分析"])
    if cpx:
        complexity = first_sentences(cpx, 60)
    else:
        m = re.search(r"(时间复杂度|时间)[^\n]{0,6}?(O\([^)]+\))", idx_raw)
        if m:
            complexity = m.group(2)

    difficulty = fm.get("difficulty") or "未知"
    tags = [t for t in fm.get("tags", [])
            if t.lower() not in LANG_TAGS and t not in LANG_TAGS and t != difficulty]

    # 题面来源优先级：problem.md 正文 -> index.md「题目描述」-> 题面截图
    source_note = ""
    if not (parsed["description"].strip() or parsed["input"].strip()):
        idx_desc = section_text(idx_raw, [r"题目描述", r"题面", r"题目大意"])
        if len(idx_desc) >= 80:
            parsed["description"] = idx_desc
            source_note = "原题为截图，此处用本仓题解页的整理版题面"
        else:
            parsed["images"] = parsed["images"][:2]
            parsed["has_video"] = False
            source_note = "题面为截图/视频，完整题面见索引表链接"

    layout = "auto" if parsed["description"].strip() else "full"

    return {
        "oj": oj,
        "id": pid,
        "sid": f"{oj}#{pid}",
        "dir": str(pdir.relative_to(REPO_ROOT)),
        "title": fm.get("title") or (parsed["description"].split("\n")[0][:40] if parsed["description"] else f"{oj} {pid}"),
        "difficulty": difficulty,
        "tags": tags,
        "url": pick_url(oj, pid, fm),
        "layout": layout,
        "statement": parsed,
        "statement_note": source_note,
        "body": {"summary": "", "note": ""},
        "solution": {
            "approach": approach,
            "approach_note": "" if approach else "",
            "complexity": complexity,
            "points": tags,
            "pitfall": "",
        },
    }


def merge_agent_fields(new: dict, old: dict | None) -> dict:
    """重跑 collect 时保留 agent 手写的字段。"""
    if not old:
        return new
    for key in ("summary", "note"):
        if old.get("body", {}).get(key):
            new["body"][key] = old["body"][key]
    for key in ("approach", "approach_note", "complexity", "pitfall"):
        if old.get("solution", {}).get(key):
            new["solution"][key] = old["solution"][key]
    if old.get("solution", {}).get("points"):
        new["solution"]["points"] = old["solution"]["points"]
    if old.get("layout_locked") and old.get("layout"):
        new["layout"] = old["layout"]
        new["layout_locked"] = True
    return new


# --------------------------------------------------------------------------- #
# 排版测量（估算行数，决定 2-up / 1-up）
# --------------------------------------------------------------------------- #
def unit_width(s: str) -> float:
    return sum(0.55 if ord(c) < 128 else 1.0 for c in s)


def est_lines(text: str, per_line: float = 60.0) -> float:
    total = 0.0
    for para in text.split("\n"):
        if not para.strip():
            total += 0.4
            continue
        total += max(1.0, math.ceil(unit_width(para) / per_line))
    return total


def sample_lines(code: str, per_line: float = 74.0) -> float:
    """样例框：标签 1 行 + 等宽内容行 + 内边距。"""
    body = 0.0
    for line in code.split("\n"):
        body += max(1.0, math.ceil(unit_width(line) / per_line))
    return body + 1.6


def clip_sample(code: str) -> str:
    """样例过长时截断，避免单张卡被一个巨型样例撑爆。"""
    code = re.sub(r"!\[[^\]]*\]\([^)]*\)", "［图］", code)   # 样例里的 markdown 图片没法渲染
    lines = code.split("\n")
    clipped = False
    if len(lines) > SAMPLE_MAX_LINES:
        lines = lines[:SAMPLE_MAX_LINES]
        clipped = True
    out = "\n".join(lines)
    if len(out) > SAMPLE_MAX_CHARS:
        out = out[:SAMPLE_MAX_CHARS]
        clipped = True
    return out.rstrip() + ("\n…（样例过长已截断）" if clipped else "")


def sample_fits_pair(cin: str, cout: str) -> bool:
    """输入输出都比较短时并排放，省一半高度。"""
    def ok(code: str) -> bool:
        lines = code.split("\n")
        return len(lines) <= 4 and all(unit_width(l) <= 34 for l in lines)

    return ok(cin) and ok(cout)


def build_body(card: dict, desc_cap: int, samples_kept: int) -> tuple[str, float]:
    st = card["statement"]
    img_dir = REPO_ROOT / card["dir"]
    parts: list[str] = []
    height = 0.0

    summary = card["body"].get("summary") or st["description"]
    summary = re.sub(r"\n{2,}", "\n\n", summary).strip()
    truncated = False
    if len(summary) > desc_cap:
        summary = summary[:desc_cap].rstrip() + "……"
        truncated = True
    if summary:
        rendered = md_to_typst(summary, img_dir)
        parts.append(rendered)
        height += est_lines(summary)

    if st["images"] and not st["description"].strip():
        for img in st["images"][:2]:
            parts.append(_image(img, img_dir))
            height += 26          # 一张缩略图约 26 行高度
        if st.get("has_video"):
            parts.append(text_quote("（原题含视频，完整题面见索引表）"))
            height += 1

    if st["input"]:
        parts.append("*输入格式*　" + md_to_typst(st["input"], img_dir))
        height += est_lines(st["input"]) + 0.6
    if st["output"]:
        parts.append("*输出格式*　" + md_to_typst(st["output"], img_dir))
        height += est_lines(st["output"]) + 0.6

    kept = st["samples"][:samples_kept]
    for i, smp in enumerate(kept, 1):
        cin, cout = clip_sample(smp["in"]), clip_sample(smp["out"])
        if cin and cout and sample_fits_pair(cin, cout):
            parts.append('#sample-pair("样例 %d 输入", %s, "样例 %d 输出", %s)'
                         % (i, typ_str(cin), i, typ_str(cout)))
            height += max(sample_lines(cin), sample_lines(cout))
            continue
        if cin:
            parts.append('#sample("样例 %d 输入", %s)' % (i, typ_str(cin)))
            height += sample_lines(cin)
        if cout:
            parts.append('#sample("样例 %d 输出", %s)' % (i, typ_str(cout)))
            height += sample_lines(cout)
    if len(st["samples"]) > samples_kept:
        parts.append(text_quote(f"（另 {len(st['samples']) - samples_kept} 组样例见索引表链接）"))
        height += 1

    if st["constraints"]:
        cons = st["constraints"][:CONSTRAINT_CHARS]
        if len(st["constraints"]) > CONSTRAINT_CHARS:
            cons += "……"
        parts.append("*数据范围*　" + md_to_typst(cons, img_dir))
        height += est_lines(cons) + 0.6

    if card.get("statement_note"):
        parts.append(text_quote("（" + card["statement_note"] + "）"))
        height += 1.2
    if truncated:
        parts.append(text_quote("（题面已压缩，完整题意见索引表链接）"))
        height += 1

    body = "\n\n".join(p for p in parts if p.strip())
    return body, height


def typ_str(s: str) -> str:
    return '"' + s.replace("\\", "\\\\").replace('"', '\\"') + '"'


def typ_content(md: str, img_dir: Path | None = None) -> str:
    """markdown 片段 -> typst content block；空串 -> none。"""
    if not md or not md.strip():
        return "none"
    return "[" + md_to_typst(md.strip(), img_dir) + "]"


def typ_list(items: list[str]) -> str:
    if not items:
        return "()"
    return "(" + ", ".join(typ_str(i) for i in items) + ("," if len(items) == 1 else "") + ")"


def pending_fields(card: dict) -> list[str]:
    sol = card["solution"]
    miss = []
    if not sol.get("approach"):
        miss.append("做法")
    if not sol.get("points"):
        miss.append("考察")
    if not sol.get("pitfall"):
        miss.append("典型坑")
    return miss


def render_card(card: dict) -> tuple[str, str]:
    """返回 (layout, typst 调用串)。"""
    n_samples = len(card["statement"]["samples"])
    samples_kept = min(SAMPLE_LIMIT, n_samples)
    want_full = card["layout"] == "full"

    if not want_full:
        desc_cap = COMPACT_DESC_CHARS
        body, height = build_body(card, desc_cap, samples_kept)
        while height > COMPACT_MAX_LINES and samples_kept > 1:
            samples_kept -= 1
            body, height = build_body(card, desc_cap, samples_kept)
        while height > COMPACT_MAX_LINES and desc_cap > 200:
            desc_cap -= 80
            body, height = build_body(card, desc_cap, samples_kept)
        if height > COMPACT_MAX_LINES:
            want_full = True

    if want_full:
        body, height = build_body(card, FULL_DESC_CHARS, min(SAMPLE_LIMIT, n_samples))

    sol = card["solution"]
    meta_bits = [card["difficulty"]]
    if card["tags"]:
        meta_bits.append(" · ".join(card["tags"][:4]))
    args = [
        f"title: {typ_str(card['title'])}",
        f"meta: {typ_str(' · '.join(meta_bits))}",
        f"dots-n: {DIFFICULTY_DOTS.get(card['difficulty'], 0)}",
        f"sid: {typ_str(card['sid'])}",
        f"body: [{body}]",
        f"approach: {typ_content(sol.get('approach', ''), REPO_ROOT / card['dir'])}",
        f"approach-note: {typ_str(sol.get('approach_note', '')) if sol.get('approach_note') else 'none'}",
        f"complexity: {typ_content(sol.get('complexity', ''), REPO_ROOT / card['dir'])}",
        f"points: {typ_list(sol.get('points', []))}",
        f"pitfall: {typ_content(sol.get('pitfall', ''), REPO_ROOT / card['dir'])}",
    ]
    fn = "card-flow" if want_full else "card-fixed"
    return ("full" if want_full else "compact"), f"{fn}(\n    " + ",\n    ".join(args) + ",\n  )"


def write_typst(batch_dir: Path, data: dict) -> Path:
    cards = data["cards"]
    batch = data["batch"]
    rendered = [render_card(c) for c in cards]

    out = [
        "// 由 build.py 生成，不要手改（改 cards.json 后重跑 build.py render）",
        f'#import "/{TEMPLATE.relative_to(REPO_ROOT)}": *',
        f"#show: it => doc({typ_str(batch['name'])}, it)",
        f"#cover({typ_str(batch['name'])}, {typ_str(batch['date'])}, {len(cards)}, "
        f"{typ_str(batch.get('source', ''))}, {data['pending_total']}, {typ_str(batch.get('note', ''))})",
        "#index-table((" + ", ".join(
            "(" + ", ".join([
                f"sid: {typ_str(c['sid'])}",
                f"diff: {typ_str(c['difficulty'])}",
                f"url: {typ_str(c['url'])}",
                f"pending: {len(pending_fields(c))}",
            ]) + ")"
            for c in cards
        ) + ",))",
    ]

    groups: list[str] = []
    i = 0
    while i < len(rendered):
        layout, call = rendered[i]
        if layout == "compact" and i + 1 < len(rendered) and rendered[i + 1][0] == "compact":
            groups.append("#card-pair(\n  " + call + ",\n  " + rendered[i + 1][1] + ",\n)")
            i += 2
        else:
            groups.append("#card-solo(\n  " + call + ",\n)")
            i += 1
    out.append("\n#pagebreak()\n".join(groups))

    typ = batch_dir / "cards.typ"
    typ.write_text("\n".join(out) + "\n", encoding="utf-8")

    manifest = [{"sid": c["sid"], "layout": r[0], "title": c["title"]} for c, r in zip(cards, rendered)]
    (batch_dir / "layout.json").write_text(json.dumps(manifest, ensure_ascii=False, indent=2), encoding="utf-8")
    return typ


def compile_pdf(batch_dir: Path, typ: Path) -> Path:
    pdf = batch_dir / f"{batch_dir.name}.pdf"
    cmd = ["typst", "compile", "--root", str(REPO_ROOT), str(typ), str(pdf)]
    print("→", " ".join(cmd))
    res = subprocess.run(cmd, capture_output=True, text=True)
    if res.returncode != 0:
        print(res.stdout, file=sys.stderr)
        print(res.stderr, file=sys.stderr)
        raise SystemExit(f"typst 编译失败（{typ}）")
    if res.stderr.strip():
        warn = res.stderr.strip().split("\n")
        print(f"⚠ typst 警告 {len(warn)} 行：")
        for line in warn[:12]:
            print("  " + line)
    print(f"✔ {pdf}  ({pdf.stat().st_size // 1024} KB)")
    return pdf


def load_batch(batch_dir: Path) -> dict | None:
    f = batch_dir / "cards.json"
    if not f.exists():
        return None
    return json.loads(f.read_text(encoding="utf-8"))


def cmd_collect(args) -> Path:
    batch_dir = (REPO_ROOT / args.batch).resolve() if not Path(args.batch).is_absolute() else Path(args.batch)
    batch_dir.mkdir(parents=True, exist_ok=True)
    old = load_batch(batch_dir) or {}
    old_by_sid = {c["sid"]: c for c in old.get("cards", [])}

    cards, missing = [], []
    for tok in args.targets:
        parsed = parse_target(tok)
        if not parsed:
            missing.append(tok)
            continue
        card = collect_card(*parsed)
        if not card:
            missing.append(tok)
            continue
        cards.append(merge_agent_fields(card, old_by_sid.get(card["sid"])))
        print(f"✔ {card['sid']}  {card['title']}  [{card['difficulty']}]")

    if not cards:
        raise SystemExit("没有采集到任何题目：" + ", ".join(missing))

    # 默认增量更新：未出现在本次目标里的旧卡保持原样；--replace 才整体重建
    if old_by_sid and not getattr(args, "replace", False):
        fresh = {c["sid"]: c for c in cards}
        ordered = list(cards)                        # 先按本次目标顺序
        ordered += [oc for oc in old.get("cards", []) if oc["sid"] not in fresh]
        cards = ordered

    data = {
        "batch": {
            "name": args.name or old.get("batch", {}).get("name") or batch_dir.name,
            "date": dt.date.today().isoformat(),
            "source": args.source or old.get("batch", {}).get("source", ""),
            "note": args.note or old.get("batch", {}).get("note", ""),
        },
        "cards": cards,
    }
    data["pending_total"] = sum(len(pending_fields(c)) for c in cards)
    out = batch_dir / "cards.json"
    out.write_text(json.dumps(data, ensure_ascii=False, indent=2), encoding="utf-8")
    print(f"→ {out}（待补 {data['pending_total']} 项字段）")
    if missing:
        print("⚠ 未入库/无法解析，已跳过：" + ", ".join(missing), file=sys.stderr)
    return batch_dir


def cmd_render(args) -> None:
    batch_dir = (REPO_ROOT / args.batch).resolve() if not Path(args.batch).is_absolute() else Path(args.batch)
    data = load_batch(batch_dir)
    if not data:
        raise SystemExit(f"找不到 {batch_dir}/cards.json，先跑 collect")
    data["pending_total"] = sum(len(pending_fields(c)) for c in data["cards"])
    (batch_dir / "cards.json").write_text(json.dumps(data, ensure_ascii=False, indent=2), encoding="utf-8")
    typ = write_typst(batch_dir, data)
    print(f"→ {typ}")
    for c in data["cards"]:
        miss = pending_fields(c)
        if miss:
            print(f"⚠ {c['sid']} 待补：{'、'.join(miss)}")
    if not args.no_compile:
        compile_pdf(batch_dir, typ)


def main() -> None:
    ap = argparse.ArgumentParser(description="OJ 题目复习卡 PDF 生成器")
    sub = ap.add_subparsers(dest="cmd", required=True)

    c = sub.add_parser("collect", help="扫题目、抽结构、写 cards.json")
    c.add_argument("targets", nargs="+", help="oj/id、oj id 或题目 URL 的混合列表")
    c.add_argument("--batch", required=True, help="批次目录，如 prints/csp-j-400")
    c.add_argument("--name", help="批次/题单名")
    c.add_argument("--source", help="来源说明（目录、题单文件等）")
    c.add_argument("--note", help="封面附注")
    c.add_argument("--replace", action="store_true", help="丢弃已有批次，只保留本次目标")

    r = sub.add_parser("render", help="cards.json -> cards.typ -> PDF")
    r.add_argument("--batch", required=True)
    r.add_argument("--no-compile", action="store_true", help="只生成 cards.typ")

    b = sub.add_parser("build", help="collect + render")
    b.add_argument("targets", nargs="+")
    b.add_argument("--batch", required=True)
    b.add_argument("--name")
    b.add_argument("--source")
    b.add_argument("--note")
    b.add_argument("--replace", action="store_true", help="丢弃已有批次，只保留本次目标")
    b.add_argument("--no-compile", action="store_true")

    args = ap.parse_args()
    if args.cmd == "collect":
        cmd_collect(args)
    elif args.cmd == "render":
        cmd_render(args)
    else:
        cmd_collect(args)
        cmd_render(args)


if __name__ == "__main__":
    main()
