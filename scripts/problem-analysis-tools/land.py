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
    python3 scripts/problem-analysis-tools/land.py 3058 --index-only   # 只落 index.md

## `--index-only` 是为什么

两轮制流水线里，第 1 轮专家写的 `main.cpp` / `main.py` 会被验证 worker
**按项目风格改写**。第 2 轮专家只重写 `index.md`，此时：

- **题目目录里的代码才是最终版**（worker 改过的）
- 暂存目录里的还是专家的初稿

若不用 `--index-only`，本脚本会把初稿覆盖回去，**把 worker 的修正全部冲掉**。
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
    ap.add_argument("pids", nargs="+")
    ap.add_argument("--stage", default=None)
    ap.add_argument("--index-only", action="store_true",
                    help="只落 index.md，不动题目目录里已有的 main.cpp/main.py")
    ap.add_argument("--dry-run", action="store_true")
    args = ap.parse_args()

    # 支持一次落多道：单道失败不影响其余（便于批量收口）
    ok, bad = 0, []
    for pid in args.pids:
        if len(args.pids) > 1:
            print(f"\n{'─' * 60}")
        try:
            land_one(pid, args)
            ok += 1
        except SystemExit as e:
            print(f"⛔ {pid} 落盘失败：{e}")
            bad.append(pid)
    if len(args.pids) > 1:
        print(f"\n合计 {len(args.pids)} 道：成功 {ok}，失败 {len(bad)}"
              + (f"（失败：{' '.join(bad)}）" if bad else ""))
    if bad:
        raise SystemExit(1)


def land_one(pid: str, args) -> None:
    row = load_row(pid)
    stage = pathlib.Path(args.stage) if args.stage else STAGE / pid
    src = NEW_ROJ / "problems" / pid
    dst = REPO_ROOT / "problems" / "roj" / pid

    # ── 前置检查：专家的产物齐不齐 ──
    need = ("index.md",) if args.index_only else ("index.md", "main.cpp", "main.py")
    missing = [f for f in need if not (stage / f).is_file()]
    if missing:
        raise SystemExit(f"⛔ 暂存目录缺文件 {missing}（{stage}）")
    # ── 题面：content.md 或 content.pdf（D 组等）──
    #   大部分题有 content.md；少数（如 10005/10012…10019）只有 content.pdf
    #   ⇒ 用 extract_pdf.py 提取为文本，作为 problem.md 的内容
    #     ★ 否则 land.py 会报「素材源没有 content.md」而阻断落盘。
    src_md = src / "content.md"
    src_pdf = src / "content.pdf"
    if not src_md.is_file() and not src_pdf.is_file():
        raise SystemExit(f"⛔ 素材源既无 content.md 也无 content.pdf：{src}")

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
    if src_md.is_file():
        shutil.copyfile(src_md, dst / "problem.md")
    else:
        # 从 PDF 提取（复用 extract_pdf.py 的 extract()）
        sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
        import extract_pdf  # noqa: PLC0415

        ok, msg = extract_pdf.extract(str(pid), dst)
        if not ok:
            raise SystemExit(f"⛔ content.pdf 提取失败：{msg}")
        (dst / "problem.md").write_text(
            (dst / f"{pid}.txt").read_text(encoding="utf-8"), encoding="utf-8"
        )
        (dst / f"{pid}.txt").unlink(missing_ok=True)
        print(f"  ℹ 题面来自 content.pdf（{msg.split(' → ')[0]}）")
    if args.index_only:
        for f in ("main.cpp", "main.py"):
            if not (dst / f).is_file():
                raise SystemExit(f"⛔ --index-only 要求题目目录已有 {f}（应由 worker 改好）")
        print("\nℹ --index-only：保留题目目录里已有的 main.cpp / main.py（worker 的最终版）")
    else:
        for f in ("main.cpp", "main.py"):
            shutil.copyfile(stage / f, dst / f)
    (dst / "index.md").write_text(out_index, encoding="utf-8")

    got = sorted(p.name for p in dst.iterdir() if p.is_file())
    print(f"\n✅ 已落盘，目录内容：{got}")
    if got != ["index.md", "main.cpp", "main.py", "problem.md"]:
        print("⚠️ 目录内容不是恰好四个文件 —— 请检查是否有测试数据/编译产物混入")


if __name__ == "__main__":
    main()
