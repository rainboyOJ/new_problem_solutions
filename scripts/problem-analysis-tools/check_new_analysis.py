#!/usr/bin/env python3
"""验收「新建题解」批次的产出契约（配套 docs/plans/roj-missing-analysis-283-batch.md）。

对每个题目目录检查：
  1. 恰好 4 个必需文件：problem.md / main.cpp / main.py / index.md
  2. problem.md 与素材源 new_ROJ/problems/<id>/content.md 逐字节一致
  3. index.md frontmatter 字段齐全、date/updated 格式合法、description 非空
  4. index.md 同时引用 main.py 与 main.cpp（本仓库「两种都展示」规范）
  5. index.md 有 [[TOC]] 与 ## 总结
  6. 题目目录里没有混进测试数据（*.in / *.out）
  7. include-code 指向的文件真实存在

用法：
    python3 scripts/problem-analysis-tools/check_new_analysis.py 1125 1222
    python3 scripts/problem-analysis-tools/check_new_analysis.py --manifest .tmp/roj283-manifest.json
    python3 scripts/problem-analysis-tools/check_new_analysis.py --manifest .tmp/roj283-manifest.json --json
"""

from __future__ import annotations

import argparse
import hashlib
import json
import pathlib
import re
import sys

REPO_ROOT = pathlib.Path(__file__).resolve().parents[2]
SOURCE_ROOT = REPO_ROOT.parent / "new_ROJ" / "problems"

REQUIRED_FILES = ("problem.md", "main.cpp", "main.py", "index.md")
REQUIRED_FM = (
    "oj", "problem_id", "title", "description", "difficulty", "date", "updated",
    "toc", "tags", "favorite", "favorite_reason", "categories", "showAtRbook",
    "pre", "common", "recommend", "source",
)
STAMP_RE = re.compile(r"^\d{4}-\d{2}-\d{2} \d{2}:\d{2}$")
DIFFICULTIES = {
    "入门", "普及-", "普及", "普及+/提高-", "提高", "提高+/省选-", "省选/NOI-", "未知",
}


def frontmatter_field(text: str, name: str) -> str | None:
    block = re.match(r"^---\n(.*?)\n---\n", text, re.S)
    if not block:
        return None
    match = re.search(rf"^{name}:[ \t]*(.*)$", block.group(1), re.M)
    return match.group(1).strip() if match else None


def md5(path: pathlib.Path) -> str:
    return hashlib.md5(path.read_bytes()).hexdigest()


def check_one(pid: str) -> dict:
    problems: list[str] = []
    d = REPO_ROOT / "problems" / "roj" / pid

    if not d.is_dir():
        return {"pid": pid, "ok": False, "problems": ["题目目录不存在"]}

    present = {f for f in REQUIRED_FILES if (d / f).is_file()}
    for f in REQUIRED_FILES:
        if f not in present:
            problems.append(f"缺文件 {f}")
    if not present:
        return {"pid": pid, "ok": False, "problems": problems}

    # 1. problem.md 与素材源一致
    src = SOURCE_ROOT / pid / "content.md"
    if (d / "problem.md").is_file():
        if not src.is_file():
            problems.append(f"素材源缺 content.md，problem.md 无法比对（{src}）")
        elif md5(d / "problem.md") != md5(src):
            problems.append("problem.md 与 new_ROJ/problems/%s/content.md 不一致" % pid)

    # 2. 没有混进测试数据
    strays = sorted(p.name for p in d.glob("*.in")) + sorted(p.name for p in d.glob("*.out"))
    if strays:
        problems.append(f"题目目录混进测试数据: {strays[:5]}")
    if (d / "data").is_dir():
        problems.append("题目目录不该有 data/ 子目录")

    index = d / "index.md"
    if index.is_file():
        text = index.read_text(encoding="utf-8")

        # 3. frontmatter
        block = re.match(r"^---\n(.*?)\n---\n", text, re.S)
        if not block:
            problems.append("index.md 缺 frontmatter")
        else:
            for name in REQUIRED_FM:
                if frontmatter_field(text, name) is None:
                    problems.append(f"frontmatter 缺字段 {name}")
            for name in ("date", "updated"):
                value = frontmatter_field(text, name)
                if value is not None and not STAMP_RE.match(value.strip('"\'')):
                    problems.append(f"{name} 格式不是 YYYY-MM-DD HH:MM: {value!r}")
            if frontmatter_field(text, "date") and frontmatter_field(text, "date") != frontmatter_field(text, "updated"):
                problems.append("date 与 updated 不相等（新建题解应相等）")
            desc = (frontmatter_field(text, "description") or "").strip('"\'')
            if not desc:
                problems.append("description 为空")
            diff = (frontmatter_field(text, "difficulty") or "").strip('"\'')
            if diff and diff not in DIFFICULTIES:
                problems.append(f"difficulty 取值非法: {diff!r}")
            if frontmatter_field(text, "toc") not in ("true", "True"):
                problems.append("toc 不是 true")

        # 4. 两种代码都引用
        if "include-code(./main.py" not in text:
            problems.append("index.md 没有引用 main.py")
        if "include-code(./main.cpp" not in text:
            problems.append("index.md 没有引用 main.cpp")

        # 5. 骨架
        if "[[TOC]]" not in text:
            problems.append("index.md 缺 [[TOC]]")
        if not re.search(r"^## 总结", text, re.M):
            problems.append("index.md 缺 ## 总结")
        if not re.search(r"^## (形式化题目|题目描述)", text, re.M):
            problems.append("index.md 缺 ## 形式化题目 / ## 题目描述")

        # 6. include-code 目标存在
        for target in re.findall(r"@include-code\(([^,)]+)", text):
            target = target.strip()
            if not (d / target).is_file():
                problems.append(f"include-code 指向不存在的文件: {target}")

    return {"pid": pid, "ok": not problems, "problems": problems}


def main() -> int:
    parser = argparse.ArgumentParser(description="验收新建题解的产出契约")
    parser.add_argument("pids", nargs="*")
    parser.add_argument("--manifest", help="manifest JSON，取其中所有 pid")
    parser.add_argument("--json", action="store_true")
    parser.add_argument("--quiet-ok", action="store_true", help="只打印失败的题")
    args = parser.parse_args()

    pids = list(args.pids)
    if args.manifest:
        payload = json.loads((REPO_ROOT / args.manifest).read_text(encoding="utf-8"))
        pids += [str(r["pid"]) for r in payload]
    if not pids:
        parser.error("需要 pid 或 --manifest")

    results = [check_one(pid) for pid in dict.fromkeys(pids)]
    failed = [r for r in results if not r["ok"]]

    if args.json:
        print(json.dumps({"total": len(results), "failed": len(failed), "results": results},
                         ensure_ascii=False, indent=1))
        return 1 if failed else 0

    for r in results:
        if r["ok"] and args.quiet_ok:
            continue
        mark = "✅" if r["ok"] else "❌"
        print(f"{mark} {r['pid']}")
        for p in r["problems"]:
            print(f"     - {p}")
    print(f"\n合计 {len(results)} 道：通过 {len(results) - len(failed)}，失败 {len(failed)}")
    return 1 if failed else 0


if __name__ == "__main__":
    sys.exit(main())
