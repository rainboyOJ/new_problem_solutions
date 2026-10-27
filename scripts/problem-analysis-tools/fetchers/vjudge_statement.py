"""把 VJudge 题面 HTML 转成本仓库约定的 Markdown。

两件容易出错的事单独在这里处理：

1. **数学定界符**：VJudge 用 ``<var>\\(N\\)</var>`` / ``\\[..\\]``，而本仓库的
   markdown-it-texmath 只开了 ``dollars`` + ``beg_end``，``\\(N\\)`` 会原样输出成
   普通文本。所以这里统一转成 ``$...$`` / ``$$...$$``。
2. **样例表**：``<table class='vjudge_sample'>`` 里一对 ``<pre>`` 就是 in/out，
   ``<pre>`` 内部要保留原文，不能做数学替换，也不能被 strip 掉首尾空格。
"""

from __future__ import annotations

from html import unescape
import re
from typing import NamedTuple

from .base import Sample

# 单个 <pre> 的占位符，避免转换过程污染代码块内容。
_SENTINEL = "\x00PRE{}\x00"

_BLOCK_TAGS = (
    "p",
    "div",
    "section",
    "ul",
    "ol",
    "li",
    "table",
    "thead",
    "tbody",
    "tr",
    "h1",
    "h2",
    "h3",
    "h4",
    "h5",
    "h6",
    "blockquote",
)


class ParsedStatement(NamedTuple):
    body_md: str
    samples: list[Sample]
    sample_notes: list[str]


def convert_math(html: str) -> str:
    """把 ``\\(..\\)`` / ``\\[..\\]`` 转成 ``$..$`` / ``$$..$$``。"""

    html = re.sub(r"\\\[([\s\S]*?)\\\]", lambda m: f"$${m.group(1).strip()}$$", html)
    html = re.sub(r"\\\(([\s\S]*?)\\\)", lambda m: f"${m.group(1).strip()}$", html)
    return html


def _protect_pre(html: str) -> tuple[str, list[str]]:
    """把 <pre> 换为占位符；内部的 <var>数学</var> 仍然要转成 $..$。"""

    blocks: list[str] = []

    def repl(match: re.Match[str]) -> str:
        inner = match.group(1)
        # <var> 包着的公式：先把定界符换掉，再抽掉 var 标签。
        inner = re.sub(
            r"<var[^>]*>([\s\S]*?)</var>",
            lambda m: convert_math(m.group(1)).strip(),
            inner,
            flags=re.I,
        )
        # 代码块里其余标签一律去掉，但保留换行与缩进。
        inner = unescape(re.sub(r"<[^>]+>", "", inner)).strip("\n")
        blocks.append(inner)
        return _SENTINEL.format(len(blocks) - 1)

    return re.sub(r"<pre[^>]*>([\s\S]*?)</pre>", repl, html, flags=re.I), blocks


def _restore_pre(text: str, blocks: list[str]) -> str:
    """占位符还原为围栏代码块，与仓库现有 problem.md 写法一致。"""

    for index, block in enumerate(blocks):
        text = text.replace(_SENTINEL.format(index), "\n```\n" + block + "\n```\n")
    return text


def pre_text(raw: str) -> str:
    """<pre> 内部：只去标签、还原实体，保留换行与行首空格。"""

    return unescape(re.sub(r"<[^>]+>", "", raw))


def html_to_markdown(html: str) -> str:
    """题面正文小节转 Markdown（保留数学、列表、代码块、粗斜体、链接）。"""

    if not html.strip():
        return ""

    # 先剔除 VJudge 注入的脚本与空标题。
    html = re.sub(r"<script[\s\S]*?</script>", "", html, flags=re.I)
    html = re.sub(r"<h3[^>]*>\s*</h3>", "", html, flags=re.I)

    html, pre_blocks = _protect_pre(html)
    html = convert_math(html)

    # 行内语义标签。
    html = re.sub(r"<(/?)strong[^>]*>", r"\1**", html, flags=re.I)
    html = re.sub(r"<(/?)b[^>]*>", r"\1**", html, flags=re.I)
    html = re.sub(r"<(/?)em[^>]*>", r"\1*", html, flags=re.I)
    html = re.sub(r"<(/?)i[^>]*>", r"\1*", html, flags=re.I)
    html = re.sub(r"<code[^>]*>([\s\S]*?)</code>", lambda m: f"`{unescape(re.sub(r'<[^>]+>', '', m.group(1)))}`", html, flags=re.I)
    html = re.sub(
        r'<a[^>]*href=["\']([^"\']+)["\'][^>]*>([\s\S]*?)</a>',
        lambda m: f"[{re.sub(r'<[^>]+>', '', m.group(2)).strip()}]({m.group(1)})",
        html,
        flags=re.I,
    )

    # 列表项。
    html = re.sub(r"<li[^>]*>", "\n- ", html, flags=re.I)
    html = re.sub(r"</li>", "", html, flags=re.I)

    # 块级标签转换为换行。
    for tag in _BLOCK_TAGS:
        html = re.sub(rf"</?{tag}\b[^>]*>", "\n", html, flags=re.I)
    html = re.sub(r"<br\s*/?>", "\n", html, flags=re.I)

    # 剩余标签一律去掉，避免把 HTML 带进 Markdown。
    html = re.sub(r"<[^>]+>", "", html)
    text = unescape(html)
    text = _restore_pre(text, pre_blocks)

    lines = []
    for line in text.replace("\r\n", "\n").replace("\r", "\n").split("\n"):
        stripped = line.strip()
        if stripped:
            lines.append(re.sub(r"[ \t]+", " ", stripped) if not line.startswith(" ") else line.rstrip())
        elif lines and lines[-1] != "":
            lines.append("")
    while lines and lines[-1] == "":
        lines.pop()
    md = "\n".join(lines)
    return re.sub(r"\n{3,}", "\n\n", md).strip()


def extract_sample_table(html: str) -> tuple[Sample | None, str]:
    """从一个样例小节里取出 (样例, 表格之后的说明文字)。"""

    match = re.search(
        r"<table[^>]*class=['\"]vjudge_sample['\"][\s\S]*?</table>", html, flags=re.I
    )
    if not match:
        return None, html
    table = match.group(0)
    pres = re.findall(r"<pre[^>]*>([\s\S]*?)</pre>", table, flags=re.I)
    sample = None
    if len(pres) >= 2:
        sample = Sample(input=pre_text(pres[0]), output=pre_text(pres[1]))
    tail = html[match.end() :]
    # 表格后面的空 <section> 要清掉，别把空白当说明。
    tail = re.sub(r"<section[^>]*>\s*</section>", "", tail, flags=re.I)
    note = html_to_markdown(tail)
    return sample, note


def is_sample_section(title: str) -> bool:
    lower = (title or "").strip().lower()
    return lower.startswith(("sample", "样例", "示例", "例子", "ví dụ", "ejemplo", "esempio")) or "样例" in lower or "示例" in lower


SECTION_TITLES_ZH = {
    "problem statement": "题目描述",
    "题目描述": "题目描述",
    "问题描述": "题目描述",
    "description": "题目描述",
    "constraints": "约束",
    "约束条件": "约束",
    "约束": "约束",
    "制約": "约束",
    "input": "输入格式",
    "输入": "输入格式",
    "输入格式": "输入格式",
    "入力": "输入格式",
    "output": "输出格式",
    "输出": "输出格式",
    "输出格式": "输出格式",
    "出力": "输出格式",
    "note": "说明",
    "notes": "说明",
    "说明": "说明",
    "hint": "说明",
    "注意": "说明",
}


def normalize_section_title(title: str) -> str:
    clean = (title or "").strip()
    return SECTION_TITLES_ZH.get(clean.lower(), SECTION_TITLES_ZH.get(clean, clean))


def build_statement(title_line: str, sections: list[tuple[str, str]]) -> ParsedStatement:
    """把 VJudge 的 sections 组装成本仓库的 problem.md 正文。"""

    body_parts: list[str] = [title_line.strip()]
    samples: list[Sample] = []
    notes: list[str] = []

    for section_title, content in sections:
        if is_sample_section(section_title):
            sample, note = extract_sample_table(content)
            if sample is not None:
                samples.append(sample)
            if note.strip():
                notes.append(note.strip())
            continue
        body = html_to_markdown(content)
        if body:
            body_parts.append(f"## {normalize_section_title(section_title)}\n\n{body}")

    if samples:
        sample_blocks = []
        for index, sample in enumerate(samples, start=1):
            sample_blocks.append(
                "\n".join(
                    [
                        f"## 输入输出样例 #{index}",
                        "",
                        f"### 输入 #{index}",
                        "",
                        "```",
                        sample.input.rstrip(),
                        "```",
                        "",
                        f"### 输出 #{index}",
                        "",
                        "```",
                        sample.output.rstrip(),
                        "```",
                    ]
                )
            )
        body_parts.append("\n\n".join(sample_blocks) + "\n")

    if notes:
        joined = "\n\n".join(note for note in notes if note)
        if joined.strip():
            body_parts.append(f"## 样例说明\n\n{joined.strip()}")

    body_md = "\n\n".join(part.rstrip() for part in body_parts if part.strip()).rstrip() + "\n"
    return ParsedStatement(body_md=body_md, samples=samples, sample_notes=notes)
