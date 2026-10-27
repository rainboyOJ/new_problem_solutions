#!/usr/bin/env python3
"""列出 rbook 书里可用于 showAtRbook 的文章 id。

用法:
    python3 list_rbook_articles.py                      # 全部可用文章
    python3 list_rbook_articles.py --grep 线段树 二分     # 按关键词过滤 title/id
    python3 list_rbook_articles.py --json               # 机器可读
    python3 list_rbook_articles.py --verify a,b,c       # 核对 id 是否可用
    python3 list_rbook_articles.py --all                # 连草稿一起列出

判定规则（实测定标，见 SKILL.md「数据来源」）:
    候选 = book/pages 下所有带 frontmatter `id` 的 markdown，
           排除「所在目录名含『草稿』」或「文件名(不含扩展名)含 草稿 / todo / draft」的文件。

这条规则是从 470 篇本地文件反推出来的：rbook 线上 catalog（445 篇）恰好等于
470 减去这 25 篇草稿。book.yaml 只是导航目录，并不等于收录范围，所以这里不按
book.yaml 过滤。
"""

from __future__ import annotations

import argparse
import json
import os
import re
import sys
from pathlib import Path

DRAFT_PATTERN = re.compile(r"草稿|todo|draft", re.I)


def default_book_dir() -> Path:
    env = os.environ.get("RBOOK2_CODE_PATH", "").strip()
    if env:
        candidate = Path(env).expanduser()
        if (candidate / "book.yaml").exists():
            return candidate
        if (candidate.parent / "book.yaml").exists():
            return candidate.parent
    return Path("~/mycode/rbook_nunjucks/book").expanduser()


def read_frontmatter(md_path: Path) -> dict[str, str]:
    try:
        head = md_path.read_text(encoding="utf-8", errors="ignore")[:1500]
    except OSError:
        return {}
    m = re.search(r"^---\s*\n(.*?)\n---", head, re.S)
    if not m:
        return {}
    fm = m.group(1)
    result = {}
    for key in ("id", "title"):
        km = re.search(rf'^{key}:\s*["\']?(.*?)["\']?\s*$', fm, re.M)
        if km:
            result[key] = km.group(1).strip()
    return result


def is_draft(rel_path: Path) -> bool:
    """所在目录名含『草稿』，或文件名（不含扩展名）含 草稿/todo/draft。"""
    if any("草稿" in part for part in rel_path.parts[:-1]):
        return True
    return bool(DRAFT_PATTERN.search(rel_path.stem))


def collect_articles(book_dir: Path, include_drafts: bool = False) -> list[dict]:
    pages_root = book_dir / "pages"
    if not pages_root.is_dir():
        raise SystemExit(f"未找到 {pages_root}")

    articles: list[dict] = []
    seen: set[str] = set()
    draft_count = 0

    for md in sorted(pages_root.rglob("*.md")):
        rel = md.relative_to(pages_root)
        fm = read_frontmatter(md)
        article_id = fm.get("id", "").strip()
        if not article_id or article_id in seen:
            continue

        draft = is_draft(rel)
        if draft:
            draft_count += 1
            if not include_drafts:
                continue

        seen.add(article_id)
        articles.append(
            {
                "id": article_id,
                "title": fm.get("title", ""),
                "md": str(rel),
                "draft": draft,
            }
        )

    articles.sort(key=lambda a: a["id"])
    collect_articles.draft_count = draft_count
    return articles


def main() -> int:
    parser = argparse.ArgumentParser(description="列出 rbook 书中可用于 showAtRbook 的文章")
    parser.add_argument("--book", default="", help="book 目录，默认读 RBOOK2_CODE_PATH")
    parser.add_argument("--grep", nargs="*", default=[], help="按关键词过滤 title 或 id")
    parser.add_argument("--json", action="store_true", help="输出 JSON")
    parser.add_argument("--verify", default="", help="核对 id，逗号分隔")
    parser.add_argument("--all", action="store_true", help="连草稿一起列出")
    args = parser.parse_args()

    book_dir = Path(args.book).expanduser() if args.book else default_book_dir()
    articles = collect_articles(book_dir, include_drafts=args.all)
    known = {a["id"] for a in articles}

    if args.verify:
        wanted = [x.strip() for x in args.verify.split(",") if x.strip()]
        bad = [w for w in wanted if w not in known]
        for article_id in wanted:
            print(f"{'OK   ' if article_id in known else 'FAIL '} {article_id}")
        print(f"\n{len(wanted) - len(bad)}/{len(wanted)} 个 id 可用")
        if bad:
            print("不可用（可能是草稿、拼错，或不在 pages 下）:", ", ".join(bad))
        return 0 if not bad else 1

    if args.grep:
        keywords = [k.lower() for k in args.grep]
        articles = [
            a
            for a in articles
            if any(k in a["title"].lower() or k in a["id"].lower() for k in keywords)
        ]

    if args.json:
        print(json.dumps(articles, ensure_ascii=False, indent=2))
    else:
        drafts = getattr(collect_articles, "draft_count", 0)
        print(f"book 目录: {book_dir}")
        print(f"可用文章: {len(articles)} 篇" + (f"（另有 {drafts} 篇草稿已排除）" if not args.all else ""))
        print()
        for a in articles:
            mark = " [草稿]" if a["draft"] else ""
            print(f"{a['id']:46s} | {a['title']}{mark}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
