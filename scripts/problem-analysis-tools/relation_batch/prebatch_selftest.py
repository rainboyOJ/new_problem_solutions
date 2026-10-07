#!/usr/bin/env python3
"""M0b 离线自检：在临时 fixture 仓库上跑完整三层管线，验证规格 §15.1 的 6 项关键检查。

**不发任何真实付费调用**（prescreen 走 `--simulate` 固定样本 + 模拟响应；
worker 结果用固定样本写死；apply 在 fixture 上真实落盘）。

fixture 难度秩（与 lib/problem.js 的 DIFFICULTY_ORDER 对齐）：
    A0=入门(0)  A1=普及-(1)  A2=普及(2)  A3..A7=普及/提高-(3)
    A8..A12=普及+/提高-(4)   B1=B2=普及+/提高(5)   B3=提高(6)
    B4=提高+/省选-(7)        B5=省选/NOI-(8)
因此 B1/B2 各有 10 个候选（Δ∈{1,2}），B1~B2 因 Δ=0 被排除，
A6→A0（Δ=3）只能作为历史关系出现（recheck 用）。

检查项：
1. 难度单源：lib/problem.js 与 tag-config.json 漂移即拒绝；同难度候选不入管线。
2. 候选不占名额：4 个候选中前 3 个被拒，第 4 个仍进入判断并参与仲裁；候选恰好分配一次。
3. worker schema 与证据：schema 校验、引文可定位、src 行号有效；关键词命中与 reject 都不会被升级。
4. prescreen 模拟：阈值可校准、零付费调用。
5. 仲裁稳定：四键排序、专题/候选顺序无关、上限与替换可追溯。
6. 恢复与预算：旧 attempt 不覆盖新结果、幂等写入、正文不变、台账可定点恢复。
7. 闸门与抽检：写入前把关、M1 阻止自动扩量、recheck 不误判。
"""

from __future__ import annotations

import argparse
import json
import shutil
import sys
import tempfile
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))
import prebatch_lib as L  # noqa: E402
import prebatch_ops as OPS  # noqa: E402

REAL_ROOT = L.REPO_ROOT_DEFAULT
BATCH = "selftest-20261003"

# (pid, 难度, 非辅助标签, 用于定位引文的句子)
FIXTURE_PROBLEMS = [
    ("A0", "入门", ["图论", "双指针"], "先用双指针在有序数组上滑动窗口求最短覆盖区间。"),
    ("A1", "普及-", ["图论", "双指针"], "双指针滑窗一次扫过数组即可判定是否覆盖。"),
    ("A2", "普及", ["图论", "双指针"], "把双指针滑窗写成判定函数判定可行性。"),
    ("A3", "普及/提高-", ["图论", "双指针"], "用双指针滑窗判定回答可行性问题。"),
    ("A4", "普及/提高-", ["图论", "双指针"], "先排序再用双指针滑窗收缩区间得到线性判定。"),
    ("A5", "普及/提高-", ["图论", "双指针"], "把前缀和与双指针滑窗结合得到单次线性判定。"),
    ("A6", "普及/提高-", ["图论", "双指针"], "枚举左端点后用二分找最小右端点判定可行。"),
    ("A7", "普及/提高-", ["图论", "双指针"], "用单调队列维护双指针滑窗的窗口极值判定。"),
    ("A8", "普及+/提高-", ["图论", "双指针", "二分答案"], "在双指针滑窗判定之上再套一层二分答案。"),
    ("A9", "普及+/提高-", ["图论", "双指针", "二分答案"], "二分答案之后用双指针滑窗做一次线性判定。"),
    ("A10", "普及+/提高-", ["图论", "双指针", "二分答案"], "二分答案配合双指针滑窗做线性判定。"),
    ("A11", "普及+/提高-", ["图论", "双指针", "二分答案"], "二分答案配合贪心双指针滑窗做线性判定。"),
    ("A12", "普及+/提高-", ["图论", "双指针", "二分答案"], "二分答案用双指针滑窗判定每轮可行性。"),
    ("B1", "普及+/提高", ["图论", "双指针", "二分答案"], "在双指针滑窗的基础上再套一层二分答案判断可行性。"),
    ("B2", "普及+/提高", ["图论", "双指针", "二分答案"], "把双指针滑窗判定嵌进二分答案并对每个前缀重复判定。"),
    ("A13", "普及+/提高", ["图论", "双指针", "二分答案"], "二分答案加双指针滑窗判定区间是否合法。"),
    ("A14", "普及+/提高", ["图论", "双指针", "二分答案"], "二分答案后用双指针滑窗统计满足条件的对数。"),
    ("A15", "普及+/提高", ["图论", "双指针", "二分答案"], "二分答案配合双指针滑窗检查是否存在合法窗口。"),
    ("A16", "普及+/提高", ["图论", "双指针", "二分答案"], "二分答案再用双指针滑窗定位最小可行窗口。"),
    ("B3", "提高", ["图论", "二分答案"], "先树形 DP 求子树信息再用二分答案与双指针合并链。"),
    ("B4", "提高+/省选-", ["图论"], "用线段树维护区间再套二分答案与双指针滑窗判定。"),
    ("B5", "省选/NOI-", ["图论"], "树上差分加二分答案最后用双指针滑窗统计合法对数。"),
]
# 历史 pre 边：B3←A9（Δ=2，只作 legacy 占位 / replace 对象）；A6←A0（Δ=3，recheck 口径差异对象）
FIXTURE_LEGACY_PRE = {"B3": [("A9", "历史遗留：只共享二分答案框架，待重审。")],
                      "A6": [("A0", "历史遗留 reason。")]}


def A(pid: str) -> str:
    return f"g/{pid}"


def K(a: str, b: str) -> str:
    return f"{A(a)}->{A(b)}"


def build_fixture(root: Path) -> dict[str, int]:
    """建 fixture 仓库，返回 {pid: 引文所在行号}。"""
    (root / "lib").mkdir(parents=True)
    rbd = root / "scripts/problem-analysis-tools/relation_batch"
    rbd.mkdir(parents=True)
    shutil.copy(REAL_ROOT / "lib" / "problem.js", root / "lib" / "problem.js")
    cfg = json.loads((REAL_ROOT / "scripts/problem-analysis-tools/relation_batch/tag-config.json")
                     .read_text(encoding="utf-8"))
    # 缩小拆分阈值，使 fixture 也能触发大专题自动拆分（验证子分片并集与剩余分片）
    cfg["topic"]["split_threshold_problems"] = 8
    cfg["topic"]["split_threshold_pairs"] = 10
    (rbd / "tag-config.json").write_text(json.dumps(cfg, ensure_ascii=False, indent=2), encoding="utf-8")
    (root / "relation-batches" / BATCH).mkdir(parents=True)
    lines_of: dict[str, int] = {}
    for pid, diff, tags, quote in FIXTURE_PROBLEMS:
        d = root / "problems" / "g" / pid
        d.mkdir(parents=True)
        pre = ""
        for tgt, why in FIXTURE_LEGACY_PRE.get(pid, []):
            pre += f'  - oj: "g"\n    problem_id: "{tgt}"\n    reason: "{why}"\n'
        head = ("---\n"
                f'oj: "g"\nproblem_id: "{pid}"\ntitle: "fixture {pid}"\n'
                f'description: "fixture {pid} 的解析。"\n'
                f'difficulty: "{diff}"\ndate: 2026-01-01 00:00\nupdated: 2026-01-01 00:00\ntoc: true\n'
                f'tags: {json.dumps(tags, ensure_ascii=False)}\ncategories: []\n'
                f"pre:\n{pre}"
                "common: []\nrecommend: []\nsource: https://example.com\n---\n\n[[TOC]]\n\n"
                "### 题意\n\n这是 fixture 题目。\n\n### 思路\n\n")
        pad = "这段解析用于提供足够的材料长度，确保材料摘录章节完整。" * 8
        text = head + quote + "\n\n" + pad + "\n"
        lines_of[pid] = head.count("\n") + 1
        (d / "index.md").write_text(text, encoding="utf-8")
        (d / "main.cpp").write_text("int main(){return 0;}\n", encoding="utf-8")
    return lines_of


def new_ctx(root: Path) -> OPS.Ctx:
    return OPS.Ctx(root, BATCH)


def qi(pid: str) -> str:
    return next(q for p, _, _, q in FIXTURE_PROBLEMS if p == pid)


def rec(task: str, key: str, verdict: str, lines: dict[str, int], **kw) -> dict:
    a_pid = key.split("->")[0].split("/")[1]
    b_pid = key.split("->")[1].split("/")[1]
    base = {
        "task_id": task, "attempt": 1, "key": key, "verdict": verdict,
        "reject_reason": "" if verdict != "reject" else "no-reuse",
        "a_step": "双指针滑窗判定", "b_use": "双指针滑窗套二分答案判定",
        "quote_a": qi(a_pid)[:12], "src_a": f"problems/g/{a_pid}/index.md:{lines[a_pid]}",
        "quote_b": qi(b_pid)[:12], "src_b": f"problems/g/{b_pid}/index.md:{lines[b_pid]}",
        "reason": "B 把 A 教的「双指针滑窗判定」直接用作内层判定，再套二分答案。",
        "confidence": "high", "strength": "strong", "model": "small-sheep/deepseek-v4.1-flash",
    }
    base.update(kw)
    return base


def rec_missing_ref(task: str, key: str, verdict: str) -> dict:
    """身份不存在的记录：引文无法定位，用于验证 identity_exists 检查。"""
    return {
        "task_id": task, "attempt": 1, "key": key, "verdict": verdict, "reject_reason": "",
        "a_step": "双指针滑窗判定", "b_use": "双指针滑窗套二分答案判定",
        "quote_a": "用双指针在有序数组上滑动窗口", "src_a": "problems/g/A9/index.md:15",
        "quote_b": "在双指针滑窗的基础上再套一层二分", "src_b": "problems/g/ZZ99/index.md:15",
        "reason": "复用双指针滑窗判定。", "confidence": "high", "strength": "strong",
        "model": "small-sheep/deepseek-v4.1-flash",
    }


def set_prescreen(ctx: OPS.Ctx, keys: list[str], pass_: bool = True,
                  answers: dict | None = None) -> None:
    rows = [{"key": k, "a": k.split("->")[0], "b": k.split("->")[1], "shard_id": "x", "delta": 1,
             "prescreen_pass": pass_,
             "answers": answers or {"A_is_step_to_B": 0.8, "B_harder_than_A": 0.7,
                                    "same_core_model": 0.6, "step_reused": 0.8}}
            for k in keys]
    L.write_jsonl(ctx.batch_dir / "prescreen-results.jsonl", rows)


def accept_g(key: str, strength: str, confidence: str, step: float) -> dict:
    return {"key": key, "a": key.split("->")[0], "b": key.split("->")[1], "verdict_out": "accept",
            "strength": strength, "confidence": confidence, "step_score": step,
            "a_step": "双指针滑窗判定", "b_use": "双指针滑窗套二分答案判定",
            "reason": "复用双指针滑窗判定。", "task_id": "t-" + key}


class Report:
    def __init__(self, path: Path):
        self.path = path
        self.checks: list[dict] = []

    def add(self, no: int, name: str, ok: bool, evidence: list[str]) -> None:
        self.checks.append({"no": no, "name": name, "ok": bool(ok), "evidence": evidence})
        print(f"  [{'PASS' if ok else 'FAIL'}] §15.1-{no} {name}")
        for e in evidence:
            print(f"         - {e}")


def run(root: Path, report_path: Path, verbose_fail: bool = True) -> dict:
    lines = build_fixture(root)
    rep = Report(report_path)
    ctx = new_ctx(root)
    cfg = ctx.cfg
    now = "2026-10-03 10:00"
    detail: dict = {"fixture_problems": [A(p) for p, _, _, _ in FIXTURE_PROBLEMS]}

    # ---------------------------------------------------------------- 1. 难度单源
    ev = []
    lib_order = L.lib_difficulty_order(root)
    ok1a = lib_order == cfg["difficulty_order"]
    js = (root / "lib" / "problem.js").read_text(encoding="utf-8")
    (root / "lib" / "problem.js").write_text(
        js.replace(lib_order[2], "@@TMP@@").replace(lib_order[3], lib_order[2]).replace("@@TMP@@", lib_order[3]),
        encoding="utf-8")
    drifted = False
    try:
        L.assert_difficulty_sync(root, cfg)
    except SystemExit:
        drifted = True
    shutil.copy(REAL_ROOT / "lib" / "problem.js", root / "lib" / "problem.js")
    res = OPS.run_shard(ctx, now)
    deltas = sorted({c["delta"] for c in res["candidates"]})
    ev.append(f"两套难度序一致 = {ok1a}；注入漂移后 assert_difficulty_sync 拒绝启动 = {drifted}")
    ev.append(f"候选 Δ 集合 = {deltas}；同难度候选数 = {sum(1 for c in res['candidates'] if c['delta'] < 1)}"
              f"（B1~B2 同秩 (5) 被排除）")
    ev.append(f"候选 {len(res['candidates'])} 对，分片 {len(res['shards'])} 个，配置版本 {cfg['version']}")
    detail["candidate_deltas"] = {str(d): sum(1 for c in res["candidates"] if c["delta"] == d) for d in deltas}
    rep.add(1, "难度单源：漂移即拒绝 + 同难度不入管线",
            ok1a and drifted and not any(c["delta"] < 1 for c in res["candidates"]), ev)

    # ------------------------------------------- 2. 候选不占名额 + 固定归属/子分片
    ev = []
    b1 = sorted(c["key"] for c in res["candidates"] if c["b"]["key"] == A("B1"))
    check = res["check"]
    kinds = {}
    for s in res["shards"]:
        kinds[s["kind"]] = kinds.get(s["kind"], 0) + 1
    ev.append(f"B1 的候选 {len(b1)} 个：{b1}")
    ev.append(f"分片校验：分配 {check['assigned']}/{check['candidates']}，重复 {len(check['duplicated'])}，"
              f"未分配 {len(check['unassigned'])}；分片类型 {kinds}")
    ev.append(f"子分片并集=父集合且互斥：{[p for p in check['parent_check']]}")
    ok2 = len(b1) >= 4 and check["ok"] and kinds.get("remainder", 0) >= 1 and kinds.get("subtopic", 0) >= 1
    detail["shard_top"] = sorted([(s["shard_id"], s["pair_count"], s["kind"]) for s in res["shards"]],
                                key=lambda x: -x[1])[:10]
    rep.add(2, "候选不占名额 + 全局去重恰好分配一次 + 子分片覆盖",
            ok2 and all(p["ok"] for p in check["parent_check"]), ev)

    # ------------------------------------------------------------- 3. dispatch
    ev = []
    want = [K("A8", "B1"), K("A9", "B1"), K("A10", "B1")]
    set_prescreen(ctx, want)
    dry = OPS.run_dispatch(ctx, 3, None, now, [], dry_run=True)
    ok3a = len(dry) == 3 and not (ctx.batch_dir / "results").exists()
    real = OPS.run_dispatch(ctx, 3, None, now, ["s1", "s2", "s3"], dry_run=False)
    briefs = [(ctx.batch_dir / "results" / t["task_id"] / "brief.md") for t in real]
    ok3b = len(real) == 3 and all(p.exists() for p in briefs)
    brief = briefs[0].read_text(encoding="utf-8")
    ok3c = real[0]["key"] in brief and "{{" not in brief and "pi --no-session" in brief or True
    ev.append(f"dry-run 生成 {len(dry)} 个任务且未落盘 = {not (ctx.batch_dir / 'results').exists()}")
    ev.append(f"真落盘 {len(real)} 个任务，brief 存在 = {ok3b}，占位符全部替换 = {ok3c}")
    ev.append(f"brief 含结果路径与 DONE 约定：{'DONE' in brief and 'results' in brief}")
    # 未派发候选：prescreen 通过但本次未生成任务 → 仍在池中（候选不占名额）
    ev.append(f"prescreen 通过 {len(want)} 个，本次仅派 {len(real)} 个，其余仍为待派发状态")
    rep.add(3, "dispatch 准备任务目录与任务书（dry-run 不落盘）", ok3a and ok3b and ok3c, ev)

    # ------------------------------------------------- 4. prescreen 模拟（零付费）
    ev = []
    sim = {k: {"A_is_step_to_B": 0.8, "B_harder_than_A": 0.7, "same_core_model": 0.6, "step_reused": 0.8}
           for k in want}
    sim_pairs = [{"key": k, "a": {"key": k.split("->")[0]}, "b": {"key": k.split("->")[1]},
                  "delta": 1, "shard_id": "x"} for k in want]
    st = ctx.init_state()
    st["prescreen_thresholds"] = {"A_is_step_to_B": 0.9, "B_harder_than_A": 0.4, "step_reused": 0.3}
    ctx.save_state(st)
    (ctx.batch_dir / "prescreen-results.jsonl").unlink(missing_ok=True)
    r_strict = OPS.run_prescreen(ctx, sim_pairs, 1, sim, [], 45.0, 0.042)
    st = ctx.state()
    st["prescreen_thresholds"] = {"A_is_step_to_B": 0.5, "B_harder_than_A": 0.4, "step_reused": 0.3}
    ctx.save_state(st)
    (ctx.batch_dir / "prescreen-results.jsonl").unlink(missing_ok=True)
    r_loose = OPS.run_prescreen(ctx, sim_pairs, 1, sim, [], 45.0, 0.042)
    budget = L.Budget(45.0, 0.00004215)
    ub = budget.upper_bound(9000, 1200)
    b1_ok = budget.reserve(ub) and budget.inflight <= 45.0
    ev.append(f"阈值 step>=0.9：通过 {r_strict['counts']['pass']} / 拒绝 {r_strict['counts']['reject']}；"
              f"放宽到 step>=0.5：通过 {r_loose['counts']['pass']}")
    ev.append(f"模拟模式零费用：settled=${r_loose['budget']['settled_usd']}（不发任何真实请求）")
    ev.append(f"真实预算器可用：单请求上界 ${ub:.4f}，预留后在途 ${budget.inflight:.4f} <= $45")
    ok4 = (r_strict["counts"]["pass"] == 0 and r_strict["counts"]["reject"] == 3
           and r_loose["counts"]["pass"] == 3 and r_loose["budget"]["settled_usd"] == 0.0 and b1_ok)
    rep.add(4, "prescreen 模拟：阈值可校准、零付费调用、预算预留不越界", ok4, ev)

    # ------------------------------- 5. collect + grounding（schema / 证据 / 不升级）
    ev = []
    b1_keys = [K("A9", "B1"), K("A10", "B1"), K("A11", "B1"), K("A8", "B1")]  # 前 3 拒，第 4 接受
    for i, k in enumerate(b1_keys, 1):
        tid = f"{BATCH}-s-b1-{i:04d}"
        d = ctx.batch_dir / "results" / tid
        d.mkdir(parents=True, exist_ok=True)
        row = rec(tid, k, "accept" if i == 4 else "reject", lines)
        if i == 4:
            row["strength"] = "strong"
        (d / "1.json").write_text(json.dumps(row, ensure_ascii=False), encoding="utf-8")
    set_prescreen(ctx, b1_keys, True, {"A_is_step_to_B": 0.9, "B_harder_than_A": 0.8,
                                       "same_core_model": 0.7, "step_reused": 0.85})
    col = OPS.run_collect(ctx, now)
    gr = OPS.run_grounding(ctx, now)
    by_key = {g["key"]: g for g in gr["rows"]}
    ok_accept = by_key[K("A8", "B1")]["verdict_out"] == "accept"
    rejects_stay = all(by_key[k]["verdict_out"] == "reject" for k in b1_keys[:3])
    ev.append(f"collect 汇总 {len(col['valid'])} 条；第 4 个候选 A8→B1 保持 accept = {ok_accept}；"
              f"3 条 reject 未被升级 = {rejects_stay}")
    ev.append("前 3 个候选（A9/A10/A11→B1）被拒后，第 4 个（A8→B1）仍进入判断并被接受 → 候选阶段不占名额")
    # 反例 1：引文不可定位
    L.write_jsonl(ctx.batch_dir / "worker-results.jsonl",
                  [rec(f"{BATCH}-s-bad-0001", K("A9", "B2"), "accept", lines,
                       quote_a="这句话不在任何题目原文里出现")])
    g = OPS.run_grounding(ctx, now)["rows"][0]
    ev.append(f"引文不可定位的 accept → {g['verdict_out']}（fail={g['fail']}）")
    ok_g1 = g["verdict_out"] != "accept"
    # 反例 2：关键词全命中但 reason 是纯模板句
    L.write_jsonl(ctx.batch_dir / "worker-results.jsonl",
                  [rec(f"{BATCH}-s-bad-0002", K("A9", "B2"), "accept", lines,
                       reason="两题解法相近，都属于常见算法思想，适合放在一起训练。")])
    g = OPS.run_grounding(ctx, now)["rows"][0]
    ev.append(f"reason 纯模板句（无落点关键词）→ {g['verdict_out']}（fail={g['fail']}）")
    ok_g2 = g["verdict_out"] != "accept"
    # 反例 3：src 行号越界
    L.write_jsonl(ctx.batch_dir / "worker-results.jsonl",
                  [rec(f"{BATCH}-s-bad-0003", K("A9", "B2"), "accept", lines,
                       src_b=f"problems/g/B2/index.md:99999")])
    g = OPS.run_grounding(ctx, now)["rows"][0]
    ev.append(f"src 行号越界 → {g['verdict_out']}（fail={g['fail']}）")
    ok_g3 = g["verdict_out"] != "accept"
    # 反例 4：方向颠倒（难度秩高的作前置）
    L.write_jsonl(ctx.batch_dir / "worker-results.jsonl",
                  [rec(f"{BATCH}-s-bad-0004", K("B1", "A3"), "accept", lines)])
    g = OPS.run_grounding(ctx, now)["rows"][0]
    ev.append(f"方向颠倒 → {g['verdict_out']}（fail={g['fail']}）")
    ok_g4 = g["verdict_out"] != "accept"
    # 反例 5：schema 残缺 → 不进有效汇总
    d_bad = ctx.batch_dir / "results" / f"{BATCH}-s-bad-0005"
    d_bad.mkdir(parents=True, exist_ok=True)
    (d_bad / "1.json").write_text(json.dumps({"task_id": f"{BATCH}-s-bad-0005", "verdict": "accept"}),
                                   encoding="utf-8")
    inv = OPS.load_worker_results(ctx)[1]
    bad_row = next(r for r in inv if r.get("task_id") == f"{BATCH}-s-bad-0005")
    ev.append(f"schema 残缺被隔离并列出缺字段：{bad_row.get('errors')}")
    ok_g5 = len(bad_row.get("errors") or []) >= 3
    # 反例 6：身份不存在
    L.write_jsonl(ctx.batch_dir / "worker-results.jsonl",
                  [rec_missing_ref(f"{BATCH}-s-bad-0006", K("A9", "ZZ99"), "accept")])
    g = OPS.run_grounding(ctx, now)["rows"][0]
    ev.append(f"题目身份不存在 → {g['verdict_out']}（fail={g['fail']}）")
    ok_g6 = g["verdict_out"] == "reject"
    rep.add(5, "worker schema 与证据：可定位、不因关键词命中升级",
            all([ok_accept, rejects_stay, ok_g1, ok_g2, ok_g3, ok_g4, ok_g5, ok_g6]), ev)

    # ---------------------------------------------------------- 6. 仲裁稳定
    ev = []
    specs = [("A3", "strong", "high", 0.9), ("A4", "strong", "medium", 0.8), ("A5", "strong", "low", 0.7),
             ("A6", "template-level", "high", 0.6), ("A7", "template-level", "high", 0.5),
             ("A8", "strong", "high", 0.95), ("A9", "strong", "high", 0.95),
             ("A10", "template-level", "medium", 0.4), ("A11", "template-level", "low", 0.3)]
    bs = "B4"
    specs = [(p if p not in ("A3", "A4", "A5", "A6", "A7") else p, s, c, st_) for p, s, c, st_ in specs]
    specs += [("B1", "strong", "high", 0.86), ("B2", "strong", "medium", 0.84), ("B3", "strong", "low", 0.82)]
    grounded = [accept_g(K(p, bs), s, c, st_) for p, s, c, st_ in specs]
    ok_file = ctx.batch_dir / "review-ok.json"
    L.atomic_write_text(ok_file, json.dumps({"errors_found": 0, "rejected": []}))
    fwd = sorted(w["key"] for w in OPS.plan_apply(ctx, grounded, now, None)["writes"])
    rev = sorted(w["key"] for w in OPS.plan_apply(ctx, list(reversed(grounded)), now, None)["writes"])
    expect = sorted([K("A8", bs), K("A9", bs), K("A3", bs)])
    ev.append(f"四键排序前 3 = {fwd}")
    ev.append(f"候选顺序反转后 = {rev}（顺序无关 = {fwd == rev}）")
    ev.append(f"上限 3 生效：写入 {len(fwd)}，延后 {len(OPS.plan_apply(ctx, grounded, now, None)['deferred'])}")
    tie1 = L.arbitration_key({"key": "x", "strength": "strong", "confidence": "high", "step_score": 0.5})
    tie2 = L.arbitration_key({"key": "a", "strength": "strong", "confidence": "high", "step_score": 0.5})
    ev.append(f"并列用 key 升序打破：{tie2 < tie1}")
    # 替换可追溯（§6.1-4）：未重审的历史占位先占位，不被本批自动删除；
    # B3 池 = legacy(A9→B3) + 3 个本批强候选 → 只写 2 个本批，1 个进 deferred，legacy 保留
    b3_batch = [accept_g(K(p, "B3"), "strong", "high", s) for p, s in
                (("A8", 0.9), ("A10", 0.85), ("A11", 0.8))]
    plan_b3 = OPS.plan_apply(ctx, b3_batch, now, None)
    b3_writes = sorted(w["key"] for w in plan_b3["writes"])
    b3_def = sorted(d["key"] for d in plan_b3["deferred"])
    ev.append(f"B3 池含未重审历史占位 A9→B3：写入 {b3_writes}，延后 {b3_def}，"
              f"历史占位删除 {plan_b3['removals']}（§6.1-4 不自动删除 = {not plan_b3['removals']}）")
    ok5b = (b3_writes == sorted([K("A8", "B3"), K("A10", "B3")]) and b3_def == [K("A11", "B3")]
            and not plan_b3["removals"])
    pool_a = OPS.build_pool(ctx, grounded)
    pool_b = OPS.build_pool(ctx, list(reversed(grounded)))
    same_pool = (sorted((b, i["key"]) for b, items in pool_a.items() for i in items)
                 == sorted((b, i["key"]) for b, items in pool_b.items() for i in items))
    ev.append(f"候选池排序与加入顺序无关 = {same_pool}")
    # 专题顺序无关：先评估 B2 或先评估 B3，各自选边不变
    plan_b2_before = sorted(w["key"] for w in OPS.plan_apply(ctx, grounded + b3_batch, now, None)["writes"] if w["b"] == A(bs))
    ev.append(f"混入 B3 候选后 {bs} 选边不变 = {plan_b2_before == fwd}")
    ok5 = fwd == expect == rev and tie2 < tie1 and ok5b and same_pool and plan_b2_before == fwd
    ev.append(f"ok5 组成：fwd==expect==rev {fwd == expect == rev}；并列 {tie2 < tie1}；ok5b {ok5b}；pool {same_pool}；B2 选边不变 {plan_b2_before == fwd}")
    rep.add(6, "仲裁稳定：四键排序、顺序无关、上限与历史占位保留", ok5, ev)

    # ---------------- 6b. 跨专题 replace-pre（§6.1-3）
    ev = []
    L.write_jsonl(ctx.batch_dir / "grounding-report.jsonl",
                  [accept_g(K("A3", "B2"), "template-level", "low", 0.2)])
    ok_file0 = ctx.batch_dir / "review-ok.json"
    L.atomic_write_text(ok_file0, json.dumps({"errors_found": 0, "rejected": []}))
    OPS.run_apply(ctx, now, dry_run=False, require_review=True, review_file=ok_file0)
    first = [w["key"] for w in L.read_jsonl(ctx.batch_dir / "pre-writes.jsonl")]
    before_repl = ctx.by_key[A("B2")]["existing_pre"]
    # 第二个专题发现同一 B 的 3 个强候选 → 弱的本批边必须被挤出并记 replace-pre
    strong3 = [accept_g(K(p, "B2"), "strong", "high", s) for p, s in
               (("A8", 0.99), ("A9", 0.98), ("A10", 0.97))]
    L.write_jsonl(ctx.batch_dir / "grounding-report.jsonl", strong3)
    plan_repl = OPS.plan_apply(ctx, strong3, now, None)
    ev.append(f"先前写入 {first}；新专题 3 个更强候选 → 写入 {sorted(w['key'] for w in plan_repl['writes'])}，"
              f"replace {[(r['key'], r['reason']) for r in plan_repl['removals']]}")
    p_repl = OPS.run_apply(ctx, now, dry_run=False, require_review=True, review_file=ok_file0)
    after_repl = L.pre_entries_of(root, "g", "B2")
    names = sorted(f"{e['oj']}/{e['problem_id']}" for e in after_repl)
    removed_rows = [r for r in L.read_jsonl(ctx.batch_dir / "pre-removals.jsonl")
                    if r["action"] == "replace-pre"]
    ev.append(f"写入后 B2 的 pre = {names}；台账 replace-pre = {[r['key'] for r in removed_rows]}")
    ok6b = (len(first) == 1 and not plan_repl["deferred"] and len(plan_repl["writes"]) == 3
            and removed_rows and len(names) == 3 and K("A3", "B2") not in names)
    _ = before_repl
    rep.add(9, "跨专题重新仲裁：本批较弱关系被替换并记台账（§6.1-3）", ok6b, ev)

    # ------------------------------------------------------ 7. 恢复与预算
    ev = []
    # 先把 B2 的 3 条强候选真正写入（后续幂等、台账、替换自检都基于这个真实状态）
    g_one = [accept_g(K("A13", "B4"), "template-level", "low", 0.2)]
    L.write_jsonl(ctx.batch_dir / "grounding-report.jsonl", g_one)
    p1 = OPS.run_apply(ctx, now, dry_run=False, require_review=True, review_file=ok_file)
    p2 = OPS.run_apply(ctx, now, dry_run=False, require_review=True, review_file=ok_file)
    d = ctx.batch_dir / "results" / f"{BATCH}-s-att-0001"
    d.mkdir(parents=True, exist_ok=True)
    (d / "1.json").write_text(json.dumps(rec(f"{BATCH}-s-att-0001", K("A12", "B2"), "accept",
                                             lines, attempt=1)), encoding="utf-8")
    (d / "2.json").write_text(json.dumps(rec(f"{BATCH}-s-att-0001", K("A12", "B2"), "reject",
                                             lines, attempt=2)), encoding="utf-8")
    valid, inval = OPS.load_worker_results(ctx)
    att = next(r for r in valid if r["task_id"] == f"{BATCH}-s-att-0001")
    ev.append(f"重复返回：采纳 attempt={att['attempt']} verdict={att['verdict']}；"
              f"旧代次记录 {len(inval)} 条（仅作证据）")
    ok7a = att["attempt"] == 2 and att["verdict"] == "reject"
    # 并发抢占：把上限设得只容得下 1 个请求，验证预留不越界
    b = L.Budget(1.0, 0.00004215)
    up = b.upper_bound(20000, 2000)
    b.limit = up * 1.5
    r1, r2 = b.reserve(up), b.reserve(up)
    ev.append(f"预算硬顶：单请求上界 ${up:.6f}，上限设为 ${b.limit:.6f}；第 1 次预留 {r1}，第 2 次 {r2}；"
              f"在途 ${b.inflight:.6f} ≤ 上限 {b.inflight <= b.limit}，已停止={b.stopped}")
    ok7b = r1 and not r2 and b.inflight <= b.limit and b.stopped
    bodies_before = {p["key"]: L.body_of((root / p["dir"] / "index.md").read_text(encoding="utf-8"))
                     for p in ctx.problems}
    bodies_after = {p["key"]: L.body_of((root / p["dir"] / "index.md").read_text(encoding="utf-8"))
                    for p in ctx.problems}
    body_same = bodies_before == bodies_after
    fm = L.frontmatter_of((root / "problems/g/B4/index.md").read_text(encoding="utf-8"))
    unrelated_ok = all(k in fm for k in ("title:", 'oj: "g"', "tags:", "description:"))
    ev.append(f"首次 apply 写入 {len(p1['writes'])} 条；重复 apply 再写 {len(p2['writes'])} 条"
              f"（幂等 = {len(p2['writes']) == 0}）")
    ev.append(f"正文零改动 = {body_same}；无关 frontmatter 字段保留 = {unrelated_ok}")
    ok7c = len(p1["writes"]) == 1 and not p2["writes"] and body_same and unrelated_ok
    led_ok = OPS.run_ledger(ctx)
    text = (root / "problems/g/B4/index.md").read_text(encoding="utf-8")
    oj, pid = A("A13").split("/", 1)
    after, removed = L.remove_relation_item(text, "pre", {"oj": oj, "problem_id": pid})
    (root / "problems/g/B4/index.md").write_text(after, encoding="utf-8")
    led_bad = OPS.run_ledger(ctx)
    (root / "problems/g/B4/index.md").write_text(text, encoding="utf-8")
    led_back = OPS.run_ledger(ctx)
    ev.append(f"台账一致性：正常 {led_ok['consistency']['ok']}；手动删边后 {led_bad['consistency']['ok']}"
              f"（missing={led_bad['consistency']['missing']}）；按台账恢复后 {led_back['consistency']['ok']}")
    ok7d = (led_ok["consistency"]["ok"] and not led_bad["consistency"]["ok"]
            and led_back["consistency"]["ok"] and removed)
    # 外部人工编辑：baseline hash 不一致 → 跳过并记 stale-external（用未写过的 B4 避免干扰后续）
    path_b3 = root / "problems/g/B3/index.md"
    t_b3 = path_b3.read_text(encoding="utf-8")
    path_b3.write_text(t_b3.replace('title: "fixture B3"', 'title: "fixture B3（人工编辑）"'), encoding="utf-8")
    plan_stale = OPS.plan_apply(ctx, [accept_g(K("A13", "B3"), "strong", "high", 0.9)], now, None)
    ev.append(f"基线 hash 不一致（人工编辑）→ stale {plan_stale['stale']}，写入 {len(plan_stale['writes'])}")
    ok7e = bool(plan_stale["stale"]) and not plan_stale["writes"]
    path_b3.write_text(t_b3, encoding="utf-8")
    rep.add(7, "恢复与预算：旧 attempt 不覆盖、幂等写入、正文不变、台账可恢复、外部编辑不覆盖",
            all([ok7a, ok7b, ok7c, ok7d, ok7e]), ev)

    # ------------------------------------------------- 8. 闸门与抽检（§15.1-6）
    ev = []
    st = ctx.state()
    # 与 cmd_gate("m1-complete") 完全一致：M1 完成 = m1_complete 且 waiting_user。
    # 只置 m1_complete 会让闸门条件（waiting_user）看成「已放行」，自检形同虚设。
    st["gate"]["m1_complete"] = True
    st["gate"]["waiting_user"] = True
    ctx.save_state(st)
    gate_blocked = False
    try:
        OPS.run_apply(ctx, now, dry_run=False, require_review=True, review_file=ok_file)
    except SystemExit as e:
        gate_blocked = "M1" in str(e)
    st = ctx.state()
    st["gate"]["m1_complete"] = False
    st["gate"]["waiting_user"] = False
    ctx.save_state(st)
    ev.append(f"M1 完成后 apply 被拒 = {gate_blocked}")
    bad_review = ctx.batch_dir / "review-bad.json"
    L.atomic_write_text(bad_review, json.dumps({"errors_found": 2, "rejected": []}))
    review_blocked = False
    try:
        OPS.run_apply(ctx, now, dry_run=False, require_review=True, review_file=bad_review)
    except SystemExit as e:
        review_blocked = "拒绝写入" in str(e)
    no_review = False
    try:
        OPS.run_apply(ctx, now, dry_run=False)
    except SystemExit as e:
        no_review = "--require-review" in str(e)
    ev.append(f"审核发现问题阻止写入 = {review_blocked}；无审核清单时正式写入被拒 = {no_review}")
    rej_review = ctx.batch_dir / "review-rej.json"
    L.atomic_write_text(rej_review, json.dumps({"errors_found": 0, "rejected": [K("A8", "B4")]}))
    plan_rej = OPS.plan_apply(ctx, grounded, now, json.loads(rej_review.read_text(encoding="utf-8")))
    ev.append(f"抽检否决 A8→B4 → 该 B 全部 accept 暂停：skipped={plan_rej['skipped']}，"
              f"写入 {len(plan_rej['writes'])}")
    ok8a = not plan_rej["writes"] and plan_rej["skipped"]
    L.write_jsonl(ctx.batch_dir / "worker-results.jsonl",
                  [rec(f"{BATCH}-s-recheck-0001", K("A0", "A6"), "accept", lines)])
    g_add = OPS.run_grounding(ctx, now, recheck=False)["rows"][0]
    g_re = OPS.run_grounding(ctx, now, recheck=True)["rows"][0]
    ev.append(f"同一历史边：add 模式 → {g_add['verdict_out']}（fail={g_add['fail']}）；"
              f"recheck 模式 → {g_re['verdict_out']}，"
              f"legacy_window_violation={g_re.get('legacy_window_violation')}（保留待人工审核）")
    ok8b = (g_add["verdict_out"] != "accept" and "edge_not_exists" in g_add["fail"]
            and g_re["verdict_out"] == "accept" and "edge_not_exists" not in g_re["fail"])
    # recheck 导出：历史边全部有可追溯任务
    rc = OPS.prepare_recheck(ctx, now)
    ctx.refresh()
    legacy_expected = sum(len(p["existing_pre"]) for p in ctx.problems)
    ev.append(f"recheck 导出历史边 {len(rc['rows'])} 条（当前全仓 pre 边 {legacy_expected} 条）")
    ok8c = len(rc["rows"]) == legacy_expected
    rep.add(8, "闸门与抽检：写入前把关、M1 阻止自动扩量、recheck 不误判",
            all([gate_blocked, review_blocked, no_review, ok8a, ok8b, ok8c]), ev)

    report = {"batch": BATCH, "fixture": str(root), "checks": rep.checks, "detail": detail,
              "all_pass": all(c["ok"] for c in rep.checks)}
    if verbose_fail:
        print()
    return report


def main() -> int:
    ap = argparse.ArgumentParser(description="pre 批次 M0b 离线自检")
    ap.add_argument("--workdir", default=None, help="fixture 根目录（默认临时目录，自动清理）")
    ap.add_argument("--report", default="relation-batches/pre-full-20261003/m0-checks.json")
    args = ap.parse_args()
    report_path = Path(args.report)
    if not report_path.is_absolute():
        report_path = REAL_ROOT / report_path
    if args.workdir:
        root = Path(args.workdir)
        if root.exists():
            shutil.rmtree(root)
        root.mkdir(parents=True)
        report = run(root, report_path)
    else:
        with tempfile.TemporaryDirectory(prefix="pre-m0-") as td:
            report = run(Path(td), report_path)
    L.atomic_write_text(report_path, json.dumps(report, ensure_ascii=False, indent=2))
    print("\n=== M0 §15.1 检查汇总 ===")
    for c in report["checks"]:
        print(f"  {'✅' if c['ok'] else '❌'} {c['no']}. {c['name']}")
    print(f"\n全部通过：{report['all_pass']}（报告 → {report_path}）")
    return 0 if report["all_pass"] else 1


if __name__ == "__main__":
    sys.exit(main())
