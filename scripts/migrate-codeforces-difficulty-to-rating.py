#!/usr/bin/env python3
"""把 problems/codeforces/ 的 difficulty 换成 Codeforces 官方 rating。

背景：Codeforces 题目的难度不该套洛谷档位，官方 rating（800 / 1500 / 2400 …）
才是真值。本脚本一次性把存量题目迁移成数字，以后由 `fetch_problem.py` 抓题时
自动写入（见 fetchers/codeforces.py 的 apply_rating）。

规则：
- 能从官方 problemset.problems 拿到 rating → `difficulty: "<rating>"`；
- 拿不到（未 rated 的场 / Gym / 刚出的题）→ 保留原值不动（含「未知」）；
- 只处理 problems/codeforces/，不碰其它 OJ；
- 改写时同步刷新 `updated`，不动 `date` 和正文。

默认 dry-run，只打印对照表；加 `--apply` 才写文件。
"""

from __future__ import annotations

import argparse
import datetime as dt
import json
import re
import sys
import time
import urllib.error
import urllib.request
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parents[1]
CF_ROOT = REPO_ROOT / "problems" / "codeforces"
API_URL = "https://codeforces.com/api/problemset.problems"
STAMP_FORMAT = "%Y-%m-%d %H:%M"
PID_RE = re.compile(r"^(\d+)([A-Za-z][A-Za-z0-9]*)$")


def fetch_ratings() -> dict[str, int]:
    """一次拉全量题目索引，返回 {"1120D": 2100, ...}。"""

    request = urllib.request.Request(
        API_URL,
        headers={"User-Agent": "rbook-difficulty-migration/1.0"},
    )
    with urllib.request.urlopen(request, timeout=60) as response:
        payload = json.loads(response.read().decode("utf-8"))
    if payload.get("status") != "OK":
        raise SystemExit(f"problemset.problems 返回失败状态：{payload.get('comment')}")
    ratings: dict[str, int] = {}
    for problem in payload.get("result", {}).get("problems", []):
        rating = problem.get("rating")
        contest_id = problem.get("contestId")
        index = problem.get("index")
        if isinstance(rating, bool) or not isinstance(rating, int):
            continue
        if not isinstance(contest_id, int) or not isinstance(index, str):
            continue
        ratings[f"{contest_id}{index}"] = rating
    return ratings


def read_difficulty(index_md: Path) -> str | None:
    text = index_md.read_text(encoding="utf-8")
    fm = re.match(r"^---\n(.*?)\n---\n", text, re.S)
    if not fm:
        return None
    match = re.search(r'^difficulty:\s*(.+)$', fm.group(1), re.M)
    if not match:
        return None
    return match.group(1).strip().strip('"').strip("'").strip() or None


def rewrite(index_md: Path, rating: int) -> None:
    text = index_md.read_text(encoding="utf-8")
    fm = re.match(r"^---\n(.*?)\n---\n(.*)$", text, re.S)
    if not fm:
        raise SystemExit(f"无 frontmatter：{index_md}")
    head, body = fm.group(1), fm.group(2)

    new_value = f'difficulty: "{rating}"'
    if re.search(r"^difficulty:\s*.*$", head, re.M):
        head = re.sub(r"^difficulty:\s*.*$", new_value, head, count=1, flags=re.M)
    else:
        head = head.rstrip("\n") + "\n" + new_value

    stamp = dt.datetime.now().strftime(STAMP_FORMAT)
    if re.search(r"^updated:\s*.+$", head, re.M):
        head = re.sub(r"^updated:\s*.+$", f"updated: {stamp}", head, count=1, flags=re.M)
    else:
        head = head.rstrip("\n") + f"\nupdated: {stamp}"

    index_md.write_text(f"---\n{head}\n---\n{body}", encoding="utf-8")


def collect() -> list[tuple[Path, str, str | None]]:
    """扫描 problems/codeforces/*/index.md，取 (路径, problem_id, 当前难度)。"""

    rows: list[tuple[Path, str, str | None]] = []
    for index_md in sorted(CF_ROOT.glob("*/index.md")):
        text = index_md.read_text(encoding="utf-8")
        fm = re.match(r"^---\n(.*?)\n---\n", text, re.S)
        if not fm:
            continue
        pid_match = re.search(r'^problem_id:\s*["\']?([^"\'\n]+)', fm.group(1), re.M)
        if not pid_match:
            continue
        rows.append((index_md, pid_match.group(1).strip(), read_difficulty(index_md)))
    return rows


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--apply", action="store_true", help="真正写文件（默认只打印对照表）")
    args = parser.parse_args()

    rows = collect()
    if not rows:
        print("没找到任何 problems/codeforces/*/index.md", file=sys.stderr)
        return 1

    print("拉取官方 problemset.problems…", file=sys.stderr)
    ratings = fetch_ratings()
    time.sleep(0.1)

    changed = 0
    missing = 0
    print(f"{'题号':<10}{'旧难度':<18}{'官方rating':<12}{'动作'}")
    print("-" * 60)
    for index_md, pid, current in rows:
        match = PID_RE.match(pid)
        key = f"{int(match.group(1))}{match.group(2)}" if match else pid
        rating = ratings.get(key)
        if rating is None:
            missing += 1
            print(f"{pid:<10}{str(current):<18}{'—':<12}保留原值（无官方 rating）")
            continue
        print(f"{pid:<10}{str(current):<18}{rating:<12}写 {rating}")
        if args.apply:
            rewrite(index_md, rating)
            changed += 1

    print("-" * 60)
    suffix = f"已写 {changed} 道" if args.apply else "dry-run：未改动，加 --apply 生效"
    print(f"共 {len(rows)} 道，有 rating {len(rows) - missing} 道，无 rating {missing} 道；{suffix}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
