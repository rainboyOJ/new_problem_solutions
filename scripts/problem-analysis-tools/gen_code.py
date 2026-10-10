#!/usr/bin/env python3
"""用 pi -ne -p 按思路文档先落一遍代码，再交给 subagent 收尾。

## 流程（用户 2026-10-08 提出的升级版）

  1. `gen_solution.py <pid>`        产出 /tmp/roj283-cards/<pid>-solution.md
                                    （思路 + **代码**，gemini 写）
  2. `gen_code.py <pid>`            调 `pi -ne -p` 按思路文档写出 main.cpp / main.py
  3. `subagent` 读思路文档 + 已落的代码，补 index.md 并跑真实数据验证

为什么要有第 2 步：子代理最容易在「推算法」上撞单轮推理输出上限
（已发生 12+ 次，deepseek 系的墙在 10 万字符附近）。把「推 + 写」这两步
挪到独立的 `pi` 调用里做掉，子代理就只负责收尾，单轮推理短得多。

## 用法

    python3 scripts/problem-analysis-tools/gen_code.py 1738
    python3 scripts/problem-analysis-tools/gen_code.py 1738 --force
    python3 scripts/problem-analysis-tools/gen_code.py 1738 --dry-run   # 只打印 prompt

输出写到 problems/roj/<pid>/main.cpp 与 main.py（若已存在则跳过，--force 覆盖）。
"""

from __future__ import annotations

import argparse
import pathlib
import re
import subprocess
import sys

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
from datafiles import count_points  # noqa: E402

REPO_ROOT = pathlib.Path(__file__).resolve().parents[2]
NEW_ROJ = REPO_ROOT.parent / "new_ROJ"
CARDS = pathlib.Path("/tmp/roj283-cards")

DEFAULT_MODEL = "s2a-gemini/gemini-3.6-flash-high"
TIMEOUT_SEC = 1500

PROMPT_TEMPLATE = """\
你是一名算法竞赛选手。下面是一份已经写好的题解思路文档（含代码草稿）。
请**照着它**把 main.cpp 与 main.py 两个文件的完整内容写出来，然后编译/运行一遍
真实数据做验证。

# 题号 {pid}，标题《{title}》

# 思路文档（含代码草稿）

{solution}

# 素材源（只读）

{src}

真实数据在 {src}/data/，共 {n_points} 个 .in 测试点，每个 .in 有同名 .out。
验证命令：
  cd {repo_root} && python3 scripts/problem-analysis-tools/check_new_analysis.py --realdata {pid}

# 要求

1. **符合选手的思路、人类的思路**：代码结构要像人写出来的，函数命名是算法概念，
   中文注释解释「为什么」而不复述代码。
2. `main.cpp` 按 oj-cpp-competitive-style：作者头注释块、全局数组、
   `typedef long long ll`、不用 lambda / auto / 强制转换 / 平行数组。
3. `main.py` 只用标准库（python-oj-short 明确「不用第三方库」，numpy 一律不行）。
   算法与 C++ 同阶，速度慢了可以（该 skill 允许 Python TLE），
   **但绝不许把算法换成暴力**。
4. 真实数据 10/10 才算数。如果实现与真实数据对不上，回头质疑思路文档，别硬套。
5. 验证通过后，把两个文件的完整内容输出（用代码块，标注文件名），
   我会直接落盘。

不要输出除了代码与必要说明之外的任何话。
"""


def read_solution(pid: str) -> str:
    p = CARDS / f"{pid}-solution.md"
    if not p.is_file():
        raise SystemExit(f"[gen_code] 思路文档不存在：{p}（先跑 gen_solution.py）")
    return p.read_text(encoding="utf-8")


def generate(pid: str, model: str, force: bool, dry_run: bool) -> None:
    src = NEW_ROJ / "problems" / pid
    title = ""
    if (src / "config.json").is_file():
        import json

        try:
            title = str(json.loads((src / "config.json").read_text(encoding="utf-8")).get("title") or "")
        except (json.JSONDecodeError, OSError):
            title = ""
    n_points = count_points(src / "data")

    prompt = PROMPT_TEMPLATE.format(
        pid=pid, title=title or "(见题面)",
        solution=read_solution(pid), src=src,
        n_points=n_points, repo_root=REPO_ROOT,
    )

    if dry_run:
        print(prompt)
        return

    target = REPO_ROOT / "problems" / "roj" / pid
    target.mkdir(parents=True, exist_ok=True)
    for name in ("main.cpp", "main.py"):
        out = target / name
        if out.exists() and not force:
            print(f"[gen_code] {out} 已存在，跳过（--force 覆盖）", file=sys.stderr)

    # pi 是带 write 工具的 agent：它会直接把 main.cpp / main.py 写进题目目录，
    # 而不是以文本形式返回。所以这里不指望 stdout 有内容，只要文件出现了就算成功。
    before = {n: (target / n).stat().st_mtime if (target / n).exists() else None
              for n in ("main.cpp", "main.py")}
    cmd = ["pi", "-ne", "-p", "--no-session", "--model", model, "--thinking", "low", prompt]
    # low：这条 prompt 要的是「照着文档落代码」，不需要长推理
    proc = subprocess.run(cmd, capture_output=True, text=True, timeout=TIMEOUT_SEC)
    text = (proc.stdout or "").strip()

    landed = []
    for name in ("main.cpp", "main.py"):
        out = target / name
        if not out.exists():
            continue
        after = out.stat().st_mtime
        if before[name] is None or after > before[name] or force:
            landed.append(name)

    if text:
        # 少数情况下 pi 会把代码当文本返回（没调用 write），这里也兜住
        blocks = re.findall(r"```(?:cpp|c\+\+|cc|python|py)\n(.*?)```", text, re.S | re.I)
        for block in blocks:
            first = block.lstrip().splitlines()[0] if block.strip() else ""
            name = "main.py" if ("main.py" in first or "python" in first.lower()
                                 or block.lstrip().startswith("#!")) else "main.cpp"
            out = target / name
            if out.exists() and not force:
                continue
            out.write_text(block, encoding="utf-8")
            if name not in landed:
                landed.append(name)
        print(text)

    if not landed:
        raise SystemExit(
            f"[gen_code] pi 没写出任何文件（退出码 {proc.returncode}）\n"
            f"stderr: {(proc.stderr or '')[:600]}"
        )
    print(f"\n[gen_code] pi 已写入 {landed} 到 {target}", file=sys.stderr)
    print(f"[gen_code] ⚠ 代码可能仍不对（1788 首次 4/10），必须靠 subagent 跑真实数据修对。", file=sys.stderr)


def main() -> int:
    ap = argparse.ArgumentParser(description="用 pi -ne -p 按思路文档落代码")
    ap.add_argument("pid")
    ap.add_argument("--model", default=DEFAULT_MODEL)
    ap.add_argument("--force", action="store_true", help="覆盖已存在的 main.cpp/main.py")
    ap.add_argument("--dry-run", action="store_true", help="只打印 prompt")
    args = ap.parse_args()

    generate(args.pid.strip(), args.model, args.force, args.dry_run)
    return 0


if __name__ == "__main__":
    sys.exit(main())
