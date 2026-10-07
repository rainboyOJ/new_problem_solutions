#!/usr/bin/env python3
"""生成 roj-analysis-worker 的单题任务卡（配套 docs/plans/roj-missing-analysis-283-batch.md）。

契约细节（四个产出文件、编译命令、验证命令、回传格式、verdict）都已固化在角色
`~/.pi/agent/agents/roj-analysis-worker.md` 里，所以任务卡只需要给「这道题特有」的信息：
题号、题名、绝对路径、素材清单、frontmatter 三行、参考布局、真实数据命令。

任务卡里显式给出参考布局文件，是为了避免子代理在全库 grep 上烧掉上下文
（2026-10-07 首批 worker 因此在 170–200KB 后触发 context 压缩，worker-3 挂掉）。

用法：
    python3 scripts/problem-analysis-tools/make_task_card.py 1353
    python3 scripts/problem-analysis-tools/make_task_card.py --manifest .tmp/roj283-manifest.json --cohort A --limit 10
    python3 scripts/problem-analysis-tools/make_task_card.py --manifest .tmp/roj283-manifest.json --pids 1682 1683 --format json
"""

from __future__ import annotations

import argparse
import json
import os
import pathlib
import sys

REPO_ROOT = pathlib.Path(__file__).resolve().parents[2]
# 素材源仓库（ROJ 题目原始数据），与本仓库平级
REPO_NEW_ROJ = REPO_ROOT.parent / "new_ROJ"
PCS2 = REPO_ROOT
SOURCE_ROOT = REPO_ROOT.parent / "new_ROJ" / "problems"

REFERENCE_LAYOUTS = ("problems/roj/1213/index.md", "problems/roj/3108/index.md")

COHORT_EXTRA = {
    "B": (
        "【本题额外工作：需造测试数据】\n"
        "素材源的 data/ 为空或不齐。按 content.md 的数据范围写 gen.py，分层造 10 组\n"
        "（边界 / 小 / 中 / 大 / 顶格），用 main.cpp 跑出 .out，再按角色约定的方式验证。\n"
        "gen.py 放在题目目录下，不要放测试数据本身。"
    ),
    "C1": (
        "【本题额外工作：缺参考解 std.cpp】\n"
        "先按题面特征句搜索同源题（博客园 / CSDN / 洛谷），或自行推导出可信参考解，\n"
        "写成 brute.cpp 放题目目录下，用 scripts/problem-analysis-tools/duipai.py\n"
        "固定种子与 main.cpp 对拍 ≥ 200 组（覆盖最小输入、上限、边界）。\n"
        "参考解来源 URL 必须写进 brute.cpp 头注和 index.md 的验证记录。\n"
        "检索 3–4 轮无果就自研，不要反复搜。"
    ),
    "C2": (
        "【本题额外工作：缺参考解 std.cpp + 缺测试数据】\n"
        "两件事都要做：(1) 搜同源题或自研参考解，写成 brute.cpp，用 duipai.py 与 main.cpp\n"
        "固定种子对拍 ≥ 200 组；(2) 按 content.md 的数据范围写 gen.py 分层造 10 组数据。\n"
        "参考解来源 URL 必须写进 brute.cpp 头注和 index.md 的验证记录。检索 3–4 轮无果就自研。"
    ),
    "D": (
        "【本题额外工作：题面只在 PDF 里】\n"
        "素材源没有 content.md，只有 content.pdf。用已安装的 pypdf 提取全文：\n"
        "  python3 -c \"from pypdf import PdfReader; print('\\n'.join(p.extract_text() for p in PdfReader('<pdf>').pages))\"\n"
        "然后按 content.md 的小节结构写入 problem.md：\n"
        "  ### 【题目描述】 / ### 【输入】 / ### 【输出】 / ### 【输入样例】 / ### 【输出样例】\n"
        "并把 config.json 的 source 补成 `### 【来源】` 段。\n"
        "⚠ PDF 里的样例可能用全角冒号（如 `00：00`），写进 problem.md 前必须转成半角 `00:00`，\n"
        "否则样例实跑必错。提取后逐字核对样例数字。\n"
        "注意：本题的 problem.md 不要求与素材源逐字节一致（素材源没有 content.md）。"
    ),
}


def source_inventory(pid: str) -> str:
    src = SOURCE_ROOT / pid
    if not src.is_dir():
        return "（素材源目录不存在，先停下来报告）"
    files = set(os.listdir(src))
    parts = []
    if "content.md" in files:
        parts.append("content.md")
    if "content.pdf" in files:
        parts.append("content.pdf")
    if "std.cpp" in files:
        parts.append("std.cpp")
    if (src / "data").is_dir():
        n = len([f for f in os.listdir(src / "data") if f.endswith(".in")])
        parts.append(f"data/（{n} 个 .in 点）")
    if "data.py" in files:
        parts.append("data.py")
    if "config.json" in files:
        parts.append("config.json")
    if "tag-report.md" in files:
        parts.append("tag-report.md")
    return " / ".join(parts) if parts else "（空目录）"


def build_card(row: dict) -> str:
    pid = str(row["pid"])
    title = row.get("title") or ""
    target = f"/Users/rainboymac/mycode/RBOOK_series/pcs2-roj-py/problems/roj/{pid}/"
    src = f"/Users/rainboymac/mycode/RBOOK_series/new_ROJ/problems/{pid}/"
    refs = "\n".join(f"  {REPO_ROOT}/{r}" for r in REFERENCE_LAYOUTS)

    lines = [
        f"题号 {pid}，题名《{title}》。",
        "",
        f"目标目录（绝对路径）：{target}",
        f"素材源（只读，绝对路径）：{src}",
        f"  包含：{source_inventory(pid)}",
        "",
        "【第一步】先把素材源的 content.md 原样复制成目标目录的 problem.md（纯复制、不需思考），",
        "然后依次写 main.cpp / main.py / index.md，先把四个文件全部落地，再开始验证。",
        "",
        "⛔ 两条硬性顺序约束（本批 1708 就是因此被中止、前功尽弃的）：",
        "   1. **四个文件全部落地后**才允许跑对拍/压测。前一路子代理在 index.md 还没写就去跑",
        "      随机对拍，单条 bash 调用超时被整轮 abort，已写好的三个文件全白费。",
        "   2. 单条 bash 调用控制在几分钟内（点数据循环、小规模随机即可）。",
        "      要跑大规模对拍就分批多次调用，每批先存结果。",
        "   验证的最低要求只有两样：样例对上 + check_sample.py 跑真实 data/ 全过 + main.py 逐点 diff 全过。",
        "   对拍是加分项不是必答题——它确实能发现真 bug，但必须建立在「四文件已齐」的前提上。",
        "",
        "⚠ 不要在单轮推理里把整道题从头推完（已有 3 个子代理因此报废）：",
        "   每轮回复的推理长度有上限（实测约 10 万字符），触顶则整轮作废、一个文件都写不出来。",
        "   一旦发现自己在同一个子问题上反复推翻重写，立即停下、直接输出工具调用",
        "   （写文件或跑命令），把剩下的推导留到下一轮，上下文不会丢。",
        "",
        "⚠ std.cpp 存疑：new_ROJ 里有部分题目的 std.cpp 与题面不符或本身算错",
        "   （1529 的 std.cpp 属于另一道题、1353 在 stack3 上算错、1421 的 data 含负环）。",
        "   用它参考前先编译跑一遍真实 data/ 并与 .out 比对；不一致就忽略它、按题面自己推导，",
        "   并在 index.md 里如实注明。",
        "",
        "skill 目录（绝对路径）：/Users/rainboymac/mycode/RBOOK_series/pcs2-roj-py/.agents/skills/",
        "  读：oj-problem-analysis-writer / oj-problem-format-spec / oj-cpp-competitive-style /",
        "      python-oj-short / rbook-markdown 的 SKILL.md",
        "  以及仓库根的 AGENTS.md、README.md 第 6 节、CONTEXT.md",
        "",
        "参考布局（直接照这两个现成题解的结构，不要去全库 grep 找范例，会烧光上下文）：",
        refs,
        "  结构：[[TOC]] / ## 形式化题目 / ## 正解 / ### 思路 / ### 代码 / ### 复杂度 / ## 总结",
        "",
        "本题 frontmatter 要点：",
        f'  oj="roj"、problem_id="{pid}"、source="https://roj.ac.cn/problem/{pid}"',
        "  description 非空（20-80 字核心解法摘要）",
        "  date 与 updated 相等，格式 YYYY-MM-DD HH:MM（当前本地时间，不加引号）",
        "  favorite: false 与 favorite_reason: \"\" 两个字段必须写全（哪怕为空串）",
        "  difficulty 只能从下面这 8 个里原样挑一个（斜杠是档位名的一部分，不是分隔符）：",
        '      "入门"  "普及-"  "普及"  "普及+/提高-"  "提高"  "提高+/省选-"  "省选/NOI-"  "未知"',
        "  ⚠ 不要写 \"省选-\" 或 \"NOI-\" 这类不在表里的值，检查脚本会判非法。",
        "代码段两种都展示，严格用这两行：",
        "  @include-code(./main.py, python)",
        "  @include-code(./main.cpp, cpp)",
        "",
        "⚠ 三条本批已踩过的坑（验收会拦下，不要返工）：",
        "  1. main.py **只能用标准库**。python-oj-short 明写「不用第三方库」，numpy/pandas 一律不行。",
        "     算法要与 C++ 同阶；速度慢了允许（该 skill：允许 Python TLE/MLE，",
        "     但绝不能因此把算法换成暴力枚举），**算法不许降级**。",
        "  2. difficulty 只能从上面 8 个里原样挑（斜杠是档位名的一部分）。",
        "     已有两道因写成 \"提高+\" / \"省选-\" 被拦下。",
        "  3. frontmatter 必须写全 favorite: false 与 favorite_reason: \"\"。",
        "",
        "交付前自己跑一遍（不过就不要报完成）：",
        f"  cd {REPO_ROOT} && python3 scripts/problem-analysis-tools/accept.py --dry-run {pid}",
        "",
        "真实数据验证（绝对路径）：",
        f"  rm -rf /tmp/verify-{pid} && mkdir -p /tmp/verify-{pid}/data",
        f"  cp {src}data/* /tmp/verify-{pid}/data/",
        f"  cp {target}main.cpp /tmp/verify-{pid}/",
        f"  python3 {REPO_ROOT}/scripts/problem-analysis-tools/check_sample.py /tmp/verify-{pid}",
        f"  main.py 用同样 .in 逐点跑并与 .out 比对。编译用 /opt/homebrew/bin/g++-16 -O2。",
        "",
        f'verdict 行的 "id" 必须是 "{pid}"。',
    ]

    extra = COHORT_EXTRA.get(row.get("cohort", "A"))
    if extra:
        lines += ["", extra]

    # 素材源出现 data.py / gen.cpp 说明这批数据是造的，题面也可能是网络重建的，
    # 出题意图与官方可能有偏差（1420 即为此情形），要求子代理如实注明。
    src_dir = REPO_NEW_ROJ / "problems" / pid
    if (src_dir / "data.py").exists() or (src_dir / "gen.cpp").exists() or (src_dir / "gen.py").exists():
        lines += [
            "",
            "⚠ 本题素材源里带数据生成脚本（data.py / gen.*）—— 说明 data/ 是自造的，",
            "   题面也可能来自网络重建，出题意图与官方原题可能有偏差。请在 index.md 里如实注明。",
        ]
    return "\n".join(lines)


def main() -> int:
    parser = argparse.ArgumentParser(description="生成 roj-analysis-worker 单题任务卡")
    parser.add_argument("pids", nargs="*")
    parser.add_argument("--manifest", help="manifest JSON")
    parser.add_argument("--cohort", help="只取该 cohort")
    parser.add_argument("--limit", type=int, default=0, help="最多生成几张（0 = 不限）")
    parser.add_argument("--format", choices=["text", "json"], default="text")
    args = parser.parse_args()

    rows: list[dict] = []
    if args.manifest:
        payload = json.loads((REPO_ROOT / args.manifest).read_text(encoding="utf-8"))
        rows = list(payload)
        if args.cohort:
            rows = [r for r in rows if r.get("cohort") == args.cohort]
        if args.pids:
            wanted = set(args.pids)
            rows = [r for r in rows if str(r["pid"]) in wanted]
    else:
        rows = [{"pid": p, "title": "", "cohort": "A"} for p in args.pids]
    if not rows:
        parser.error("没有匹配的题目")
    if args.limit:
        rows = rows[: args.limit]

    cards = [{"pid": str(r["pid"]), "cohort": r.get("cohort", "A"), "card": build_card(r)} for r in rows]

    if args.format == "json":
        print(json.dumps(cards, ensure_ascii=False, indent=1))
    else:
        for c in cards:
            print(f"########## {c['pid']}  (cohort {c['cohort']}) ##########")
            print(c["card"])
            print()
    return 0


if __name__ == "__main__":
    sys.exit(main())
