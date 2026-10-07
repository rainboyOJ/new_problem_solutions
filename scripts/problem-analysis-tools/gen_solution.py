#!/usr/bin/env python3
"""用便宜的 gemini 先把「推算法」这一步做完，产出 md 格式的题解思路。

## 为什么需要它（2026-10-07 观察到的瓶颈）

本批次最大的失败源是子代理**单轮推理撞输出上限**（已发生 8+ 次）：模型想在一轮里
把整道题从头推完，deepseek-v4.1-flash 的推理墙在 10 万字符附近，一撞上就整轮作废、
一个文件都写不出来。

根因不是「想得太多」，而是**把推算法和写代码混在同一个上下文里做**。推算法需要大量
分支试错（正是 10 万字符的来源），而写代码只需要照着已定的思路落地（很短）。

## 做法

派一个便宜的大上下文模型（s2a-gemini/gemini-3.1-pro，`maxTokens` 65 553、ctx 100 万）
**只做推算法这一步**，产出 md：

  - 问题模型 / 关键观察 / 算法步骤 / 复杂度 / 边界与实现坑
  - **不写代码**（连伪代码也只给必要的一两行）

然后子代理读这个 md，只负责把思路落地成 main.cpp / main.py / index.md。
子代理的上下文里没有长推理，就不会撞输出上限。

## 用法

    python3 scripts/problem-analysis-tools/gen_solution.py 1738
    python3 scripts/problem-analysis-tools/gen_solution.py 1738 --model s2a-gemini/gemini-3.1-pro
    python3 scripts/problem-analysis-tools/gen_solution.py 1738 --force     # 覆盖已有

输出写到 /tmp/roj283-cards/<pid>-solution.md，同时打印到 stdout。
"""

from __future__ import annotations

import argparse
import pathlib
import re
import subprocess
import sys

REPO_ROOT = pathlib.Path(__file__).resolve().parents[2]
NEW_ROJ = REPO_ROOT.parent / "new_ROJ"
CARDS = pathlib.Path("/tmp/roj283-cards")

DEFAULT_MODEL = "s2a-gemini/gemini-3.1-pro"
TIMEOUT_SEC = 600

PROMPT_TEMPLATE = """\
你在为一个算法竞赛选手做赛前分析。请读下面这道题，产出一份 **只讲思路、不写代码** 的分析文档。

# 题目（原样粘贴自题面）

{statement}

# 题目补充信息

- 题号：{pid}，标题：{title}
- 时间限制 {time_ms} ms，内存限制 {memory_mb} MB
- 真实数据规模参考：{data_shape}

# 你要产出的内容

写成 markdown，按下面的结构。**全程不要写代码**（不要 c++ / python / 伪代码），
只用文字、数学符号、必要时一两行的公式表达。

## 一、读题与建模
把题面重新表述成一个干净的数学问题。变量含义、约束、求什么。

## 二、朴素做法与它的瓶颈
选手一开始会怎么想？那个做法复杂度多少？卡在哪？

## 三、关键观察
这是整份文档最值钱的部分。把「怎么从朴素想到正解」的**那一步跳跃**写清楚：
- 你注意到了什么性质/不变量/等价关系？
- 为什么这个观察能破局？
- 如果有多种可能的路线，说清为什么选这条、放弃另外几条的理由。

## 四、正解步骤
分步骤讲清楚算法流程。每一步说「做什么、为什么对」。
关键的式子用 LaTeX 写出来（用 $ $ 或 $$ $$ 包裹）。

## 五、复杂度
时间、空间各多少，怎么来的。和时限比留多少余量。

## 六、实现时的坑
- 需要特别小心的边界（n=1、空输入、重复值、溢出、精度……）
- 数据类型要不要 long long / 大整数
- 输入读法有没有讲究
- 容易写错的下标、方向、正负号

## 七、对拍建议
如果要验证，用什么暴力解、什么构造能暴露错误。

# 写法要求

- **符合选手的思路，像人类在思考**：可以用「先……但是……」这样的叙述，
  不要写成教科书式的定义堆砌。让人读完知道「下一步该往哪想」。
- 中文书写。
- 不要复述题面的原文（已经给了），直接进入分析。
- 不要输出除了这份 markdown 之外的任何话（不要「好的，这是……」之类的开场白）。
"""


def read_statement(pid: str) -> tuple[str, str, str, str, str]:
    src = NEW_ROJ / "problems" / pid
    if not src.is_dir():
        raise SystemExit(f"素材源不存在：{src}")

    content = (src / "content.md").read_text(encoding="utf-8", errors="replace")

    cfg = {}
    cfg_path = src / "config.json"
    if cfg_path.is_file():
        import json

        try:
            cfg = json.loads(cfg_path.read_text(encoding="utf-8"))
        except (json.JSONDecodeError, OSError):
            cfg = {}

    title = str(cfg.get("title") or "")
    time_ms = cfg.get("time") or 1000
    memory_mb = cfg.get("memory") or 256

    data_dir = src / "data"
    points = sorted(data_dir.glob("*.in")) if data_dir.is_dir() else []
    if points:
        first = points[0].read_bytes()[:200].decode("utf-8", errors="replace")
        first_line = first.splitlines()[0] if first.splitlines() else ""
        shape = f"{len(points)} 个 .in 测试点，首行样本：{first_line.strip()!r}"
    else:
        shape = "（无 data/）"

    return content, title, str(time_ms), str(memory_mb), shape


def generate(pid: str, model: str, force: bool) -> pathlib.Path:
    CARDS.mkdir(parents=True, exist_ok=True)
    out = CARDS / f"{pid}-solution.md"
    if out.exists() and not force:
        print(f"[gen_solution] {out} 已存在，跳过（--force 覆盖）", file=sys.stderr)
        return out

    statement, title, time_ms, memory_mb, data_shape = read_statement(pid)
    prompt = PROMPT_TEMPLATE.format(
        statement=statement, pid=pid, title=title or "(见题面)",
        time_ms=time_ms, memory_mb=memory_mb, data_shape=data_shape,
    )

    # -ne 关闭扩展（避免子代理类扩展干扰），-p 一次性跑完退出，--no-session 不落会话
    cmd = [
        "pi", "-ne", "-p", "--no-session",
        "--model", model,
        "--thinking", "high",
        prompt,
    ]
    proc = subprocess.run(cmd, capture_output=True, text=True, timeout=TIMEOUT_SEC)

    text = (proc.stdout or "").strip()
    if not text:
        raise SystemExit(
            f"[gen_solution] 模型没产出内容（退出码 {proc.returncode}）\n"
            f"stderr: {(proc.stderr or '')[:600]}"
        )

    # 去掉可能的开场白（「好的，这是……」），从第一个 markdown 标题开始取
    m = re.search(r"(?m)^#{1,3} ", text)
    if m and m.start() > 0 and len(text[:m.start()]) < 200:
        text = text[m.start():]

    out.write_text(text + "\n", encoding="utf-8")
    print(text)
    print(f"\n[gen_solution] 已写入 {out}（{len(text)} 字符）", file=sys.stderr)
    return out


def main() -> int:
    ap = argparse.ArgumentParser(description="用 gemini 先推算法，产出 md 题解思路")
    ap.add_argument("pid")
    ap.add_argument("--model", default=DEFAULT_MODEL)
    ap.add_argument("--force", action="store_true", help="覆盖已有的 solution.md")
    args = ap.parse_args()

    generate(args.pid.strip(), args.model, args.force)
    return 0


if __name__ == "__main__":
    sys.exit(main())
