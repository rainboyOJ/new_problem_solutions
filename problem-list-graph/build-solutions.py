#!/usr/bin/env python3
"""为 problem-list-graph 注入「本站有解析」标记。

只改数据，不改 UI：

1. 扫 `problems/<oj>/<题号>/index.md`，得到「本站有解析」的题号全集。
2. 与 `public/problem-list-graph/problems.json` 里本题单的题目求交。
3. 把 `solutions` / `solGenerated` 写回 `problems.json` 与 `index.html` 内嵌的 `DATA`。
4. 重算两个产物的 sha256 并回写本目录 `README.md` 里记录的 hash。

checkbox、进度条、三态筛选、「解析」chip 的样式与逻辑是手工维护在
`public/problem-list-graph/index.html` 里的，本脚本不碰。

用法：

    python3 problem-list-graph/build-solutions.py
"""

from __future__ import annotations

import datetime
import hashlib
import json
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
PROBLEM_DIR = ROOT / "problems"
ARTIFACT_DIR = ROOT / "public" / "problem-list-graph"
HTML_PATH = ARTIFACT_DIR / "index.html"
JSON_PATH = ARTIFACT_DIR / "problems.json"
README_PATH = Path(__file__).resolve().parent / "README.md"

DATA_PREFIX = "<script>var DATA="
DATA_SUFFIX = ";</script>"

# 产物固定的顶层字段顺序；problems 必须留在最后。
FIELD_ORDER = (
    "generated",
    "solGenerated",
    "total",
    "categories",
    "sources",
    "tierCount",
    "tierName",
    "diffOrder",
    "stageOrder",
    "solutions",
    "problems",
)

# 缺了任何一个就说明产物结构被改过。
REQUIRED_FIELDS = ("generated", "total", "problems")

# 本题单的题号前缀 → 本站 problems/ 下的 oj 目录名。
# 题单覆盖洛谷题号体系：P/SP/UVA 走 luogu，CF 走 codeforces，AT_ 走 atcoder。
AT_PREFIX = "AT_"
CF_PREFIX = "CF"

# 与 index.html 里 /* keyOf:start */ … /* keyOf:end */ 之间的实现一一对应。
# tests/problem-list-graph-solutions.test.js 会把页面里的 keyOf 抽出来做交叉校验。
KEY_SAMPLES = {
    "P1048": "luogu/P1048",
    "SP1716": "luogu/SP1716",
    "UVA10298": "luogu/UVA10298",
    "CF600E": "codeforces/600E",
    "AT_agc001_e": "atcoder/agc001_e",
}


def key_of(problem_id: str) -> str:
    """本题单题号 → 进度键（= 题目单里的 data-problem-key = 本站题目路径尾段）。"""
    if problem_id.startswith(AT_PREFIX):
        return f"atcoder/{problem_id[len(AT_PREFIX):]}"
    if problem_id.startswith(CF_PREFIX):
        return f"codeforces/{problem_id[len(CF_PREFIX):]}"
    match = re.fullmatch(r"(?i)p?(\d+)", problem_id)
    return f"luogu/P{match.group(1)}" if match else f"luogu/{problem_id}"


def normalize_problem_id(oj: str, problem_id: str) -> str:
    """`lib/problem.js` 的 normalizeProblemId：只规范化洛谷的 p?数字 题号。"""
    value = problem_id.strip()
    if oj.lower() != "luogu":
        return value
    match = re.fullmatch(r"(?i)p?(\d+)", value)
    return f"P{match.group(1)}" if match else value


def scan_site_solutions() -> dict[str, str]:
    """扫 problems/，返回 {小写键: 真实键}，只收有 index.md 的题目目录。"""
    found: dict[str, str] = {}
    for oj_dir in sorted(PROBLEM_DIR.iterdir()):
        if not oj_dir.is_dir():
            continue
        oj = oj_dir.name
        for problem in sorted(oj_dir.iterdir()):
            if not problem.is_dir():
                continue
            if not (problem / "index.md").is_file():
                continue
            real_key = f"{oj}/{normalize_problem_id(oj, problem.name)}"
            found[real_key.lower()] = real_key
    return found


def load_artifact_json() -> dict:
    """读 problems.json。index.html 内嵌的 DATA 与它逐字节相同，所以只读一份。"""
    return json.loads(JSON_PATH.read_bytes().decode("utf-8"))


def compact(data: dict) -> str:
    """产物统一的序列化形式：单行紧凑 JSON（与既有问题字节一致）。"""
    return json.dumps(data, ensure_ascii=False, separators=(",", ":"))


def compute_solutions(data: dict, site: dict[str, str]) -> list[str]:
    """本题单 3028 题 ∩ 本站有解析 → 排序后的键列表。"""
    solutions: list[str] = []
    mismatches: list[str] = []
    seen: set[str] = set()

    for problem in data["problems"]:
        want = key_of(problem["id"])
        real = site.get(want.lower())
        if real is None:
            continue
        if real != want:
            # 页面的 keyOf 推不出仓库里的真实大小写：进度键会和题目单错配。
            mismatches.append(f"  {problem['id']}: 页面推导 {want} ≠ 仓库实际 {real}")
            continue
        if real in seen:
            continue
        seen.add(real)
        solutions.append(real)

    if mismatches:
        sys.stderr.write(
            "题号大小写与仓库目录不一致，页面推导的进度键会与题目单错配：\n"
            + "\n".join(mismatches)
            + "\n\n请人工处理（把该题在本题单里的 id 改成仓库的真实写法，或让双方统一）。\n"
        )
        raise SystemExit(1)

    return sorted(solutions)


def build_payload(data: dict, solutions: list[str], sol_generated: str) -> dict:
    """按固定顺序重排顶层字段；solutions 放在 problems 之前，巨大的题目数组仍在末尾。"""
    for field in REQUIRED_FIELDS:
        if field not in data:
            raise SystemExit(f"problems.json 缺了必填字段 {field}，产物结构被改过？")

    unexpected = [key for key in data if key not in FIELD_ORDER]
    if unexpected:
        raise SystemExit(
            f"problems.json 出现了 FIELD_ORDER 未登记的字段：{'、'.join(unexpected)}。"
            "请先把它们加进 FIELD_ORDER，否则会被静默丢掉。"
        )

    merged = dict(data)
    merged["solGenerated"] = sol_generated
    merged["solutions"] = solutions
    return {field: merged[field] for field in FIELD_ORDER if field in merged}


def render_data_line(html: str, payload_text: str) -> str:
    """把内嵌的 DATA 换成 payload_text。只动那一行，index.html 的 CRLF 不受影响。"""
    patched, count = re.subn(
        re.escape(DATA_PREFIX) + r".*?" + re.escape(DATA_SUFFIX),
        lambda _match: DATA_PREFIX + payload_text + DATA_SUFFIX,
        html,
        count=1,
    )
    if count != 1:
        raise SystemExit("index.html 里没找到内嵌的 var DATA={…};，锚点被改过？")
    return patched


def update_readme(sol_generated: str, generated: str, html_hash: str, json_hash: str) -> None:
    readme = README_PATH.read_bytes().decode("utf-8")
    # 沿用文件本身的换行风格，不把 LF 仓库写成混用换行。
    crlf = readme.count("\r\n")
    lf = readme.count("\n") - crlf
    nl = "\r\n" if crlf > lf else "\n"
    block = nl.join(
        [
            f"当前产物（`generated: {generated}`，`solGenerated: {sol_generated}`）：",
            "",
            "```",
            f"{html_hash}  index.html",
            f"{json_hash}  problems.json",
            "```",
        ]
    )
    updated, count = re.subn(
        r"当前产物（[^）]*）：\r?\n\r?\n```\r?\n.*?\r?\n```",
        lambda _match: block,
        readme,
        count=1,
        flags=re.S,
    )
    if count != 1:
        raise SystemExit("README.md 里没找到「当前产物（…）」+ hash 代码块，锚点被改过？")
    README_PATH.write_bytes(updated.encode("utf-8"))


def main() -> None:
    for problem_id, expected in KEY_SAMPLES.items():
        actual = key_of(problem_id)
        if actual != expected:
            raise SystemExit(f"key_of 自检失败：{problem_id} → {actual}，期望 {expected}")

    data = load_artifact_json()
    site = scan_site_solutions()
    solutions = compute_solutions(data, site)

    # solGenerated 只在清单真的变化（或原值无效）时刷新，保证重跑不改字节。
    previous = data.get("solutions") or []
    sol_generated = data.get("solGenerated") or ""
    valid_date = bool(re.fullmatch(r"\d{4}-\d{2}-\d{2}", sol_generated))
    if solutions != previous or not valid_date:
        sol_generated = datetime.date.today().isoformat()

    payload = build_payload(data, solutions, sol_generated)
    payload_text = compact(payload)
    patched_html = render_data_line(HTML_PATH.read_bytes().decode("utf-8"), payload_text)

    # 两个文本都算好再落盘，避免只写一半的中间状态。
    JSON_PATH.write_bytes(payload_text.encode("utf-8"))
    HTML_PATH.write_bytes(patched_html.encode("utf-8"))

    html_hash = hashlib.sha256(HTML_PATH.read_bytes()).hexdigest()
    json_hash = hashlib.sha256(JSON_PATH.read_bytes()).hexdigest()
    update_readme(sol_generated, payload["generated"], html_hash, json_hash)

    by_oj: dict[str, int] = {}
    for key in solutions:
        by_oj[key.split("/")[0]] = by_oj.get(key.split("/")[0], 0) + 1
    detail = "、".join(f"{oj} {count}" for oj, count in sorted(by_oj.items()))
    sample = "、".join(solutions[:2]) + " … " + solutions[-1]
    changed = "有变化，已刷新" if solutions != previous else "无变化，保持原日期"

    print(f"problems/ 里有 index.md 的题目：{len(site)}")
    print(f"本题单命中：{len(solutions)} / {data['total']}（{detail}）")
    print(f"抽样：{sample}")
    print(f"solGenerated={sol_generated}（solutions {changed}）")
    print(f"index.html     {html_hash}")
    print(f"problems.json  {json_hash}")


if __name__ == "__main__":
    main()
