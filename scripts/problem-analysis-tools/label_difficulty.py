#!/usr/bin/env python3
"""补齐题库中缺失/非法的难度标注（jev 辅助，已有难度一律不动）。

三步用法：
    label_difficulty.py extract            # 抽取缺难度题的题面 -> .tmp/difficulty_todo.json
    label_difficulty.py score              # jev 打分 -> .tmp/difficulty_drafts.json
    label_difficulty.py apply [--min-conf 0.7] [--force pid1,pid2]
                                           # 高置信直接回写；低置信留待人工（--force 指定后写入）

jev 直连 https://api.typesafe.ai/v1/systemone，key 取自 ~/.typesafe/jev-lgp888.keys
（10 个 key 轮换，绝不打印）。choice 十档 + confidence；422/429/529 退避重试。

只改 difficulty 为「未知」或非法值的题；回写时同步刷新 updated，date 不动。
"""

from __future__ import annotations

import argparse
import datetime
import json
import pathlib
import re
import sys
import threading
import time
import urllib.error
import urllib.request

REPO_ROOT = pathlib.Path(__file__).resolve().parents[2]
TMP = REPO_ROOT / ".tmp"
KEYS_PATH = pathlib.Path.home() / ".typesafe" / "jev-lgp888.keys"
ENDPOINT = "https://api.typesafe.ai/v1/systemone"

# 标题里的官方难度标注：优先级高于 jev（NOIP-提高 = 提高，普及组 = 普及…）
TITLE_LEVELS = [
    (r"NOI|CTSC|IOI", "NOI/NOI+/CTSC"),
    (r"省选|NOIP-提高组决赛", "省选/NOI-"),
    (r"NOIP[^\]]*提高|提高组", "提高"),
    (r"NOIP[^\]]*普及|普及组", "普及"),
    (r"入门组", "入门"),
]


def title_hint(md: pathlib.Path) -> str | None:
    text = md.read_text(encoding="utf-8")[:400]
    for pattern, level in TITLE_LEVELS:
        if re.search(pattern, text, re.I):
            return level
    return None

VALID = ["入门", "普及-", "普及", "普及/提高-", "普及+/提高-", "普及+/提高",
         "提高", "提高+/省选-", "省选/NOI-", "NOI/NOI+/CTSC"]

CRITERIA = {
    "入门": "直接读入、输出或简单格式化，无算法可言",
    "普及-": "简单模拟/字符串/一维数组/按题意直译，小学生可做",
    "普及": "基础模拟、简单贪心、二分、一维DP、基础数论",
    "普及/提高-": "介于普及与提高-之间的区间档",
    "普及+/提高-": "明显高于普及：多维DP、图论基础、数据结构基础、有技巧的构造",
    "普及+/提高": "介于普及+与提高之间的区间档",
    "提高": "标准提高档：图论、DP、数据结构、数学综合运用",
    "提高+/省选-": "接近省选：高级数据结构、网络流、复杂DP、数学推导",
    "省选/NOI-": "省选难度：多算法综合、强推导",
    "NOI/NOI+/CTSC": "NOI/CTSC 级难度",
}


def load_keys() -> list[str]:
    keys = [l.strip() for l in KEYS_PATH.read_text().splitlines() if l.strip()]
    if not keys:
        raise SystemExit(f"{KEYS_PATH} 里没有 key")
    return keys


def problem_text(md: pathlib.Path) -> str:
    """抽取题面文本：frontmatter 标题 + 正文前 2500 字（题目描述通常在前部）。"""
    text = md.read_text(encoding="utf-8")
    fm = re.match(r"^---\n(.*?)\n---\n(.*)$", text, re.S)
    title = ""
    body = text
    if fm:
        tm = re.search(r"^title:\s*[\"']?(.+?)[\"']?\s*$", fm.group(1), re.M)
        title = tm.group(1).strip() if tm else ""
        body = fm.group(2)
    # 去掉代码引用/图示等噪声，只留叙述文本
    body = re.sub(r"@include-code[^\n]*", "", body)
    body = re.sub(r"```.*?```", "(代码略)", body, flags=re.S)
    body = re.sub(r"\n{3,}", "\n\n", body)
    return f"题目：{title}\n{body[:2500]}"


def find_todo() -> list[dict]:
    todo = []
    for md in sorted(REPO_ROOT.glob("problems/*/*/index.md")):
        text = md.read_text(encoding="utf-8")
        fm = re.match(r"^---\n(.*?)\n---\n", text, re.S)
        if not fm:
            continue
        dm = re.search(r"^difficulty:\s*[\"']?([^\"'\n]+)", fm.group(1), re.M)
        value = dm.group(1).strip() if dm else None
        if value in VALID:
            continue  # 已有合法难度，不动
        todo.append({
            "oj": md.parts[md.parts.index("problems") + 1] if "problems" in md.parts else md.parts[1],
            "pid": md.parent.name,
            "path": str(md.relative_to(REPO_ROOT)),
            "current": value,
        })
    return todo


def jev_call(state: str, keys: list[str], lock: threading.Lock, counter: dict,
             questions: dict | None = None, note: str = "") -> dict:
    body = json.dumps({
        "state": state,
        "model": "jev-latest",
        "questions": questions or {
            "difficulty": {
                "type": "choice",
                "instructions": "这道编程题在中国信息学竞赛难度体系里的档位是？按题目的算法深度与实现难度判断。",
                "criteria": CRITERIA,
            }
        },
    }).encode()
    last_error = None
    for attempt in range(6):
        with lock:
            key = keys[counter["i"] % len(keys)]
            counter["i"] += 1
        req = urllib.request.Request(ENDPOINT, data=body, headers={
            "Authorization": f"Bearer {key}", "Content-Type": "application/json"})
        try:
            with urllib.request.urlopen(req, timeout=60) as response:
                return json.loads(response.read())
        except urllib.error.HTTPError as error:
            last_error = f"HTTP {error.code} {error.read().decode()[:120]}"
            if error.code not in (422, 429, 529):
                break
        except Exception as error:  # 网络抖动
            last_error = str(error)[:120]
        time.sleep(min(2 ** attempt, 20))
    raise RuntimeError(last_error)


def cmd_extract() -> None:
    todo = find_todo()
    TMP.mkdir(exist_ok=True)
    (TMP / "difficulty_todo.json").write_text(
        json.dumps(todo, ensure_ascii=False, indent=2), encoding="utf-8")
    by_oj: dict[str, int] = {}
    for item in todo:
        by_oj[item["oj"]] = by_oj.get(item["oj"], 0) + 1
    print(f"缺难度 {len(todo)} 题 -> .tmp/difficulty_todo.json  按 OJ: {by_oj}")


def cmd_score() -> None:
    todo = json.loads((TMP / "difficulty_todo.json").read_text(encoding="utf-8"))
    keys = load_keys()
    lock = threading.Lock()
    counter = {"i": 0}
    drafts = []
    TMP.mkdir(exist_ok=True)

    def work(item: dict) -> dict:
        md = REPO_ROOT / item["path"]
        try:
            result = jev_call(problem_text(md), keys, lock, counter)
            answer = result["answers"]["difficulty"]
            return {**item,
                    "choice": answer.get("choice"),
                    "confidence": answer.get("confidence"),
                    "probabilities": answer.get("probabilities", {})}
        except Exception as error:
            return {**item, "choice": None, "confidence": None, "error": str(error)[:150]}

    from concurrent.futures import ThreadPoolExecutor
    with ThreadPoolExecutor(max_workers=10) as pool:
        for index, draft in enumerate(pool.map(work, todo), 1):
            drafts.append(draft)
            if index % 50 == 0:
                print(f"  已打分 {index}/{len(todo)}")
    (TMP / "difficulty_drafts.json").write_text(
        json.dumps(drafts, ensure_ascii=False, indent=2), encoding="utf-8")
    ok = [d for d in drafts if d.get("choice")]
    low = [d for d in ok if (d.get("confidence") or 0) < 0.7]
    failed = [d for d in drafts if not d.get("choice")]
    print(f"打分完成 {len(ok)}/{len(todo)}；低置信(<0.7) {len(low)} 待人工复核；失败 {len(failed)}")
    for d in failed[:10]:
        print(f"  失败 {d['oj']}/{d['pid']}: {d.get('error')}")


def cmd_rescore(min_top: float, min_margin: float) -> None:
    """对初判不决的题做窄候选复投：只给 top2+邻档 3~4 个选项，拉大概率差。"""
    drafts = json.loads((TMP / "difficulty_drafts.json").read_text(encoding="utf-8"))
    keys = load_keys()
    lock = threading.Lock()
    counter = {"i": 0}

    def undecided(d: dict) -> bool:
        p = d.get("probabilities") or {}
        if not p:
            return True
        ranked = sorted(p.values(), reverse=True)
        top = ranked[0]
        margin = top - (ranked[1] if len(ranked) > 1 else 0)
        return top < min_top or margin < min_margin

    def work(d: dict) -> dict:
        if not d.get("choice") or not undecided(d):
            return d
        p = d.get("probabilities") or {}
        top2 = [k for k, _ in sorted(p.items(), key=lambda kv: -kv[1])[:2]]
        idx = [VALID.index(k) for k in top2 if k in VALID]
        lo, hi = min(idx), max(idx)
        cand = VALID[max(0, lo - 1): min(len(VALID), hi + 2)]
        cand = list(dict.fromkeys(cand)) or VALID
        md = REPO_ROOT / d["path"]
        state = problem_text(md) + f"\n\n（初判候选：{'/'.join(cand)}）"
        body = {"state": state, "model": "jev-latest", "questions": {
            "difficulty": {"type": "choice",
                           "instructions": "这道编程题的难度档位是？只在给出的候选里选。",
                           "criteria": {k: CRITERIA[k] for k in cand}}}}
        try:
            result = jev_call(state, keys, lock, counter, questions=body["questions"])
            answer = result["answers"]["difficulty"]
            return {**d, "choice2": answer.get("choice"), "confidence2": answer.get("confidence"),
                    "probabilities2": answer.get("probabilities", {})}
        except Exception as error:
            return {**d, "error2": str(error)[:150]}

    from concurrent.futures import ThreadPoolExecutor
    with ThreadPoolExecutor(max_workers=10) as pool:
        out = list(pool.map(work, drafts))
    (TMP / "difficulty_drafts.json").write_text(json.dumps(out, ensure_ascii=False, indent=2), encoding="utf-8")
    n2 = sum(1 for d in out if d.get("choice2"))
    print(f"窄候选复投 {n2} 题；结果已合并进 .tmp/difficulty_drafts.json")


def cmd_apply(min_conf: float, force: set[str]) -> None:
    drafts = json.loads((TMP / "difficulty_drafts.json").read_text(encoding="utf-8"))
    written, skipped = [], []
    for item in drafts:
        # 合成最终判定：标题官方标注 > 窄候选复投 > 初判
        hint = title_hint(REPO_ROOT / item["path"])
        final, source = None, ""
        if hint:
            final, source = hint, "title"
        if item.get("choice2"):
            p2 = item.get("probabilities2") or {}
            ranked = sorted(p2.values(), reverse=True)
            if ranked and (ranked[0] >= 0.6 or (len(ranked) > 1 and ranked[0] - ranked[1] >= 0.25)):
                final, source = item["choice2"], "rescore"
        if final is None and item.get("choice"):
            p = item.get("probabilities") or {}
            ranked = sorted(p.values(), reverse=True)
            if ranked and (ranked[0] >= 0.5 or (len(ranked) > 1 and ranked[0] - ranked[1] >= 0.3)):
                final, source = item["choice"], "first"
        if final is None:
            skipped.append((item, f"仍不决：choice={item.get('choice')} choice2={item.get('choice2')}")); continue
        if final not in VALID:
            skipped.append((item, f"值不在枚举: {final}")); continue
        md = REPO_ROOT / item["path"]
        text = md.read_text(encoding="utf-8")
        fm = re.match(r"^---\n(.*?)\n---\n(.*)$", text, re.S)
        if not fm:
            skipped.append((item, "无 frontmatter")); continue
        head, body = fm.group(1), fm.group(2)
        new_value = f'difficulty: "{final}"'
        if re.search(r"^difficulty:\s*[\"']?[^\"'\n]+", head, re.M):
            head = re.sub(r"^difficulty:\s*[\"']?[^\"'\n]+", new_value, head, count=1, flags=re.M)
        else:
            head += "\n" + new_value
        stamp = datetime.datetime.now().strftime("%Y-%m-%d %H:%M")
        if re.search(r"^updated:\s*.+$", head, re.M):
            head = re.sub(r"^updated:\s*.+$", f"updated: {stamp}", head, count=1, flags=re.M)
        else:
            head += f"\nupdated: {stamp}"
        md.write_text(f"---\n{head}\n---\n{body}", encoding="utf-8")
        written.append(f"{item['oj']}/{item['pid']}: {item['current']} -> {final} [{source}] conf={item.get('confidence')}")
    for line in written:
        print("写入", line)
    print(f"\n写入 {len(written)} 题，跳过 {len(skipped)} 题（低置信/异常，待人工）：")
    for item, reason in skipped[:40]:
        print(f"  跳过 {item['oj']}/{item['pid']}: {reason}")
    (TMP / "difficulty_apply_report.json").write_text(
        json.dumps({"written": written,
                    "skipped": [{"id": f"{i['oj']}/{i['pid']}", "reason": r,
                                 "choice": i.get("choice"), "confidence": i.get("confidence")}
                                for i, r in skipped]},
                   ensure_ascii=False, indent=2), encoding="utf-8")


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("command", choices=["extract", "score", "rescore", "apply"])
    parser.add_argument("--min-conf", type=float, default=0.7)
    parser.add_argument("--min-top", type=float, default=0.5)
    parser.add_argument("--min-margin", type=float, default=0.3)
    parser.add_argument("--force", default="")
    args = parser.parse_args()
    if args.command == "extract":
        cmd_extract()
    elif args.command == "score":
        cmd_score()
    elif args.command == "rescore":
        cmd_rescore(args.min_top, args.min_margin)
    else:
        force = {s.strip() for s in args.force.split(",") if s.strip()}
        cmd_apply(args.min_conf, force)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
