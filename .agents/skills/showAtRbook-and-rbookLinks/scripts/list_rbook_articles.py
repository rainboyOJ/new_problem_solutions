#!/usr/bin/env python3
"""列出 rbook 书里可用于 showAtRbook / rbookLinks 的文章 id。

两本书：rbook2 = rbook_nunjucks（rbook2.roj.ac.cn，有 /api/catalog，本地 `book/pages`
下有 frontmatter id）；rbook1 = newRbook_ejs（rbook.roj.ac.cn，纯静态，目录在
`/catalog.json`，id 由构建期写进 config）。

用法:
    python3 list_rbook_articles.py                      # rbook2 全部可用文章
    python3 list_rbook_articles.py --book rbook1         # rbook1（读线上 catalog.json）
    python3 list_rbook_articles.py --book rbook1 --catalog ./catalog.json   # 读本地快照
    python3 list_rbook_articles.py --grep 线段树 二分     # 按关键词过滤 title/id
    python3 list_rbook_articles.py --json               # 机器可读
    python3 list_rbook_articles.py --verify a,b,c       # 核对 id 是否可用
    python3 list_rbook_articles.py --all                # 连草稿一起列出（仅 rbook2）

输出的第一列已经是可直接写进 frontmatter 的 `rbook1:xxx` / `rbook2:xxx`。
写 `rbookLinks` 时先跑 `--book rbook1`，那边没有这篇再跑默认的 rbook2。

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
import urllib.request
from pathlib import Path

DRAFT_PATTERN = re.compile(r"草稿|todo|draft", re.I)
RBOOK1_CATALOG_URL = "https://rbook.roj.ac.cn/catalog.json"


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


def load_catalog_json(source: str) -> dict:
    """读 rbook1 的 catalog.json：http(s) 地址就联网取，否则当本地文件。"""
    if source.startswith(("http://", "https://")):
        with urllib.request.urlopen(source, timeout=20) as response:
            return json.loads(response.read().decode("utf-8"))
    return json.loads(Path(source).expanduser().read_text(encoding="utf-8"))


def collect_catalog_articles(catalog: dict) -> list[dict]:
    """catalog.json 的条目已经是成品：id/title/url 都齐，没有草稿概念。"""
    articles = []
    seen = set()
    for item in catalog.get("items", []):
        article_id = str(item.get("id", "")).strip()
        if not article_id or article_id in seen:
            continue
        seen.add(article_id)
        articles.append(
            {
                "id": article_id,
                "title": str(item.get("title", "")),
                "url": str(item.get("url", "")),
                "draft": False,
            }
        )
    articles.sort(key=lambda a: a["id"])
    return articles


def main() -> int:
    parser = argparse.ArgumentParser(description="列出 rbook 书中可用于 showAtRbook / rbookLinks 的文章")
    parser.add_argument(
        "--book",
        default="rbook2",
        help="哪本书：rbook2（默认，读本地 book/pages）或 rbook1（读 catalog.json）；"
             "也可直接给 rbook2 的 book 目录（旧用法）",
    )
    parser.add_argument("--book-dir", default="", help="rbook2 的 book 目录，默认读 RBOOK2_CODE_PATH")
    parser.add_argument(
        "--catalog",
        default=RBOOK1_CATALOG_URL,
        help=f"rbook1 的 catalog.json 地址或本地路径，默认 {RBOOK1_CATALOG_URL}",
    )
    parser.add_argument("--grep", nargs="*", default=[], help="按关键词过滤 title 或 id")
    parser.add_argument("--json", action="store_true", help="输出 JSON")
    parser.add_argument("--verify", default="", help="核对 id，逗号分隔")
    parser.add_argument("--all", action="store_true", help="连草稿一起列出")
    args = parser.parse_args()

    # --book 既接受站点名，也接受旧的「目录路径」写法。
    book = args.book.strip()
    if book.lower() in ("rbook1", "rbook2"):
        site = book.lower()
        book_dir = None
    else:
        site = "rbook2"
        book_dir = Path(book).expanduser()

    if site == "rbook1":
        catalog = load_catalog_json(args.catalog)
        articles = collect_catalog_articles(catalog)
        source_label = f"rbook1 catalog: {args.catalog}（site={catalog.get('site', '?')}）"
    else:
        book_dir = book_dir or (Path(args.book_dir).expanduser() if args.book_dir else default_book_dir())
        articles = collect_articles(book_dir, include_drafts=args.all)
        source_label = f"book 目录: {book_dir}"

    for article in articles:
        article["ref"] = f"{site}:{article['id']}"
    known = {a["id"] for a in articles}

    if args.verify:
        wanted = [x.strip() for x in args.verify.split(",") if x.strip()]
        bad = [w for w in wanted if w.split(":", 1)[-1] not in known]
        for article_id in wanted:
            bare = article_id.split(":", 1)[-1]
            print(f"{'OK   ' if bare in known else 'FAIL '} {article_id}")
        print(f"\n{len(wanted) - len(bad)}/{len(wanted)} 个 id 可用")
        if bad:
            hint = (
                "不在 rbook1 的 catalog 里（或被 catalog.yaml 排除、是孤儿 config）"
                if site == "rbook1"
                else "可能是草稿、拼错，或不在 pages 下"
            )
            print(f"不可用（{hint}）:", ", ".join(bad))
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
        drafts = getattr(collect_articles, "draft_count", 0) if site == "rbook2" else 0
        print(source_label)
        draft_note = ""
        if site == "rbook2":
            draft_note = "（另有草稿已排除）" if not args.all else "（含草稿）"
        print(f"可用文章: {len(articles)} 篇{draft_note}")
        print()
        for a in articles:
            mark = " [草稿]" if a["draft"] else ""
            print(f"{a['ref']:48s} | {a['title']}{mark}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
