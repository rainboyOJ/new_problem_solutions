"""素材侧目录卫生检查：确认 new_ROJ/problems/<pid>/ 没有多余文件。

⚠ 为什么要检查
------------
子 agent 与父会话共享同一个工作区（`worktree: false`），且子 agent 对素材目录
**有 write 权限**（虽然任务书要求它们只写 /tmp）。互相污染的风险是真实的：

2026-10-08 实例：
  · 父会话自己修 1762 数据时编译出的 Mach-O 二进制 `problems/1762/std`，
    误留在题目目录（已删除）
  · `-12` 号专家自述「I accidentally created a stray placeholder file」（未落盘即被终止）
  · `problems/1378/data/shopth.txt` 是 0 字节残留文件，混在 SHOPTH*.IN/OUT 之间

而**素材侧目录从来没有人检查过** —— 产出侧（pcs2-roj-py/problems/roj/<pid>/）
有 land.py/accept.py 强制恰好 4 个文件，素材侧完全裸奔。

用法
----
    python3 check_source_hygiene.py                 # 扫全部
    python3 check_source_hygiene.py 1374 3161       # 扫指定题
    python3 check_source_hygiene.py --json          # 机器可读

退出码：0 = 干净；1 = 发现多余文件/异常
"""

from __future__ import annotations

import argparse
import json
import pathlib
import sys

REPO_ROOT = pathlib.Path(__file__).resolve().parents[2]
SOURCE_ROOT = REPO_ROOT.parent / "new_ROJ" / "problems"

# 允许出现在题目录顶层的名字（新素材形态）
ALLOWED_FILES = {
    "config.json",
    "content.md",
    "content.pdf",
    "std.cpp",
    "data.json",
    "data.py",
    "tag-report.md",
    "gen-report.md",
    "solution.md",
}
# 允许出现在题目录顶层的目录
ALLOWED_DIRS = {"data", "pic", "down", "images", "img", "assets"}

# 允许出现在 data/ 下的非数据文件（少数题目这样放）
ALLOWED_IN_DATA = {"shopth.txt", "ENTER"}  # 实测存在的历史残留，不报警但会在报告里列出


def scan(pid: str) -> dict:
    d = SOURCE_ROOT / pid
    if not d.is_dir():
        return {"pid": pid, "error": "目录不存在"}

    extras = []
    for p in sorted(d.iterdir()):
        if p.name.startswith("."):
            continue
        if p.is_file():
            if p.name not in ALLOWED_FILES:
                extras.append(f"{p.name} ({p.stat().st_size}B)")
        elif p.is_dir():
            if p.name not in ALLOWED_DIRS:
                extras.append(f"{p.name}/ (目录)")

    dd = d / "data"
    data_stray: list[str] = []   # 真正的异常：data/ 里的非数据文件
    data_empty: list[str] = []   # 仅信息：0 字节的 .in/.out，多半合法
    if dd.is_dir():
        for p in sorted(dd.iterdir()):
            if not p.is_file():
                continue
            if p.suffix.lower() in (".in", ".out", ".ans"):
                # 0 字节的数据文件**通常是合法的**：
                #   · 0 字节 .in  ⇒ 题面「无输入」（如 5027 体操队、5021 类）
                #   · 0 字节 .out ⇒ 答案是空集（如 5019 输出偶数 n=1）
                # 所以只当信息上报，**不当异常**。
                if p.stat().st_size == 0:
                    data_empty.append(p.name)
            elif p.name in ALLOWED_IN_DATA:
                pass
            else:
                data_stray.append(f"{p.name} ({p.stat().st_size}B)")

    return {"pid": pid, "extras": extras, "data_stray": data_stray, "data_empty": data_empty}


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("pids", nargs="*")
    ap.add_argument("--json", action="store_true")
    args = ap.parse_args()

    if args.pids:
        pids = args.pids
    else:
        pids = sorted(p.name for p in SOURCE_ROOT.iterdir() if p.is_dir())

    def is_bad(r: dict) -> bool:
        return bool(r.get("extras") or r.get("data_stray") or r.get("error"))

    results = [r for r in (scan(p) for p in pids) if is_bad(r)]
    empty_info = [(r["pid"], r.get("data_empty") or [])
                  for r in (scan(p) for p in pids) if r.get("data_empty")]

    if args.json:
        print(json.dumps({"problems": results, "empty_data_info": empty_info},
                         ensure_ascii=False, indent=2))
        return 1 if results else 0

    if not results:
        print(f"✅ 素材侧目录干净（扫了 {len(pids)} 道）")
        if empty_info:
            print(f"ℹ️ 另有 {len(empty_info)} 道含 0 字节数据文件（**通常是合法的**："
                  f"无输入题的 .in / 空答案的 .out）：")
            for pid, names in empty_info[:12]:
                print(f"     {pid:<8} {names[:4]}{'…' if len(names) > 4 else ''}")
            if len(empty_info) > 12:
                print(f"     … 共 {len(empty_info)} 道")
        return 0

    print(f"⚠️ {len(results)} 道题目的素材目录有异常（扫了 {len(pids)} 道）：\n")
    for r in results:
        if r.get("error"):
            print(f"  {r['pid']}: {r['error']}")
            continue
        for e in r["extras"]:
            print(f"  {r['pid']:<8} 多余项: {e}")
        for e in r["data_stray"]:
            print(f"  {r['pid']:<8} data/ 非数据文件: {e}")
    print()
    print("提示：多余文件多是历史残留（如误编译的二进制、误建的目录）。")
    print("     删除前请先确认不是某道题刻意依赖的文件。")
    return 1


if __name__ == "__main__":
    sys.exit(main())
