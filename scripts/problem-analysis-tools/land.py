#!/usr/bin/env python3
"""确定性落盘：把专家的暂存产物装配成题目目录里的四个文件。

## 在流水线中的位置

    专家（出稿到 /tmp/roj-think/<pid>/）→ 本脚本（确定性装配）→ worker 验证

## 为什么要有这一步

专家的产物里有一类字段它**根本无从知道**，必须由脚本确定性地覆盖：

| 字段 | 为什么专家写不对 |
| --- | --- |
| `date` / `updated` | 专家没有 bash、没有时钟，**不知道今天是哪天**（实测写成了 2024-05-24） |
| `problem_id` / `title` | 应以队列（manifest）为准，不以专家的复述为准 |
| `source` | 固定模板 |

这类错**与模型强弱无关**（换更贵的模型也会犯），但可以整类消灭。

## 用法

    python3 scripts/problem-analysis-tools/land.py 3058
    python3 scripts/problem-analysis-tools/land.py 3058 --dry-run
"""

from __future__ import annotations

import argparse
import datetime as dt
import json
import pathlib
import re
import shutil
import sys

REPO_ROOT = pathlib.Path(__file__).resolve().parents[2]
NEW_ROJ = REPO_ROOT.parent / "new_ROJ"
QUEUE = REPO_ROOT / ".tmp" / "roj283-queue.jsonl"
STAGE = pathlib.Path("/tmp/roj-think")

DIFFICULTIES = {"入门", "普及-", "普及", "普及+/提高-", "提高", "提高+/省选-", "省选/NOI-", "未知"}
REQUIRED_MARKERS = ["[[TOC]]", "## 形式化题目", "### 思路", "### 代码", "### 复杂度", "## 总结"]
REQUIRED_INCLUDE = ["@include-code(./main.py, python)", "@include-code(./main.cpp, cpp)"]


def load_row(pid: str) -> dict:
    for line in QUEUE.read_text(encoding="utf-8").splitlines():
        if not line.strip():
            continue
        row = json.loads(line)
        if row["pid"] == pid:
            return row
    raise SystemExit(f"⛔ 队列里没有 {pid}")


def split_frontmatter(text: str) -> tuple[str, str]:
    m = re.match(r"^---\n(.*?)\n---\n?(.*)$", text, re.S)
    if not m:
        raise SystemExit("⛔ index.md 没有合法的 YAML frontmatter（--- 包裹）")
    return m.group(1), m.group(2)


def patch_field(fm: str, key: str, value: str) -> str:
    """把 frontmatter 里 `key:` 那一行替换掉；没有就补一行。"""
    pat = re.compile(rf"^{re.escape(key)}:.*$", re.M)
    line = f'{key}: {value}'
    if pat.search(fm):
        return pat.sub(line, fm, count=1)
    return fm.rstrip("\n") + "\n" + line


def get_field(fm: str, key: str) -> str | None:
    m = re.search(rf"^{re.escape(key)}:\s*(.*)$", fm, re.M)
    return m.group(1).strip() if m else None


def main() -> None:
    ap = argparse.ArgumentParser()
    ap.add_argument("pid")
    ap.add_argument("--stage", default=None)
    ap.add_argument("--dry-run", action="store_true")
    args = ap.parse_args()

    pid = args.pid
    row = load_row(pid)
    stage = pathlib.Path(args.stage) if args.stage else STAGE / pid
    src = NEW_ROJ / "problems" / pid
    dst = REPO_ROOT / "problems" / "roj" / pid

    # ── 前置检查：专家的产物齐不齐 ──
    need = ("index.md", "main.cpp", "main.py")
    missing = [f for f in need if not (stage / f).is_file()]
    if missing:
        raise SystemExit(f"⛔ 暂存目录缺文件 {missing}（{stage}）")
    if not (src / "content.md").is_file():
        raise SystemExit(f"⛔ 素材源没有 content.md：{src}")

    # ── 装配 index.md ──
    fm, body = split_frontmatter((stage / "index.md").read_text(encoding="utf-8"))

    now = dt.datetime.now().strftime("%Y-%m-%d %H:%M")
    fixes = []
    for key, val in (("problem_id", f'"{pid}"'),
                     ("title", json.dumps(row.get("title") or "", ensure_ascii=False)),
                     ("date", now), ("updated", now),
                     ("source", f"https://roj.ac.cn/problem/{pid}")):
        old = get_field(fm, key)
        fm = patch_field(fm, key, val)
        if old != val:
            fixes.append(f"{key}: {old!r} → {val!r}")

    # difficulty 白名单
    diff = (get_field(fm, "difficulty") or "").strip().strip('"')
    if diff not in DIFFICULTIES:
        raise SystemExit(f"⛔ difficulty 非法：{diff!r}\n   合法值：{' '.join(sorted(DIFFICULTIES))}")

    # 必填字段
    for key in ("favorite", "favorite_reason"):
        if get_field(fm, key) is None:
            raise SystemExit(f"⛔ frontmatter 缺必填字段 `{key}`")

    out_index = f"---\n{fm}\n---\n{body}"

    # 正文结构
    for marker in REQUIRED_MARKERS + REQUIRED_INCLUDE:
        if marker not in out_index:
            raise SystemExit(f"⛔ index.md 缺结构标记：{marker!r}")

    # ── 报告 ──
    print(f"题目 {pid}《{row.get('title')}》")
    print(f"  暂存 {stage}")
    print(f"  目标 {dst}")
    if fixes:
        print("  确定性覆盖的字段：")
        for f in fixes:
            print(f"    - {f}")
    else:
        print("  确定性覆盖的字段：（无 —— 专家写对了）")

    if args.dry_run:
        print("\n（--dry-run，未落盘）")
        return

    dst.mkdir(parents=True, exist_ok=True)
    shutil.copyfile(src / "content.md", dst / "problem.md")
    for f in ("main.cpp", "main.py"):
        shutil.copyfile(stage / f, dst / f)
    (dst / "index.md").write_text(out_index, encoding="utf-8")

    got = sorted(p.name for p in dst.iterdir() if p.is_file())
    print(f"\n✅ 已落盘，目录内容：{got}")
    if got != ["index.md", "main.cpp", "main.py", "problem.md"]:
        print("⚠️ 目录内容不是恰好四个文件 —— 请检查是否有测试数据/编译产物混入")


if __name__ == "__main__":
    main()
