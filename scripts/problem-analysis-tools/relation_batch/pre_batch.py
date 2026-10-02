#!/usr/bin/env python3
"""前置关系（pre）批量补全管线（v3 判断设计）。

与 common 批处理的差异：
- 候选是**有序假设对**（难度低→高），但方向由 Jev 的 Choice 判断确认；
- 判断用 questions-pre-v4.json：relationship(Choice, 4 类) + A_step_used + difficulty_up(诊断)；
- 写入是**单侧**：只在「当前题」（较难的一题）frontmatter 写 pre 项，前置题不反写
  （与仓库现有 87 条 pre 惯例一致）；
- 每题 pre 稀疏（现有分布：2087 题为 0 条，78 题为 1 条，上限 3 条）。

判断设计的三次迭代（校准驱动，原始结果留档）：
- v1（prereq_needed/target_contained/difficulty_up/direction_ok）：difficulty_up 与 prereq_needed
  在反例上反而更高（0.95+/0.91 vs 正例 0.48/0.74），无判别力。
- v2（显式排除通用技巧）：矫枉过正——「A 教通用技巧、B 应用它」被判为不包含，
  而这正是 pre 的本质（与 common 相反）。
- v3（本版）：Choice 直接判关系类型，含 parallel_similar（对应 common 领域）与 unrelated，
  用 A_step_used 交叉验证。

子命令（M0a 已有）：init / candidates / materials / calibrate / judge / decide / write
子命令（M0b 新增，见 docs/plans/pre-relations-full-coverage-plan.md §4）：
    shard / prescreen / dispatch / collect / grounding / apply / ledger / selftest

全量批次的离线实现与自检集中在 `prebatch_lib.py`(共享逻辑) 与 `pre_batch.py selftest`
(在临时 fixture 仓库上跑完整管线，不发真实付费调用)。
"""

from __future__ import annotations

import argparse
import hashlib
import json
import re
import sys
from collections import Counter
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))
import batch as B  # noqa: E402
import jev_client  # noqa: E402
import prebatch_lib as L  # noqa: E402
import prebatch_ops as OPS  # noqa: E402
import prebatch_selftest as SELFTEST  # noqa: E402

BATCHES_ROOT = B.BATCHES_ROOT
PROBLEMS_ROOT = B.PROBLEMS_ROOT
REPO_ROOT = B.REPO_ROOT
CONFIG_PATH = L.CONFIG_NAME
CFG = L.load_config(REPO_ROOT)
DIFFICULTY_ORDER = L.assert_difficulty_sync(REPO_ROOT, CFG)
TIERS = {name: i for i, name in enumerate(DIFFICULTY_ORDER)}
AUX_TAGS = set(CFG["aux_tags"])
QUESTIONS = HERE / "questions-pre-v6.json"


def load_problems() -> list[dict]:
    return L.load_problems(REPO_ROOT, DIFFICULTY_ORDER)


# M0b 纯逻辑与子命令实现集中在 prebatch_ops.py；这里重导出，便于脚本化复用与测试。
run_shard = OPS.run_shard
run_prescreen = OPS.run_prescreen
run_dispatch = OPS.run_dispatch
run_collect = OPS.run_collect
run_grounding = OPS.run_grounding
run_apply = OPS.run_apply
run_ledger = OPS.run_ledger
prepare_recheck = OPS.prepare_recheck
prescreen_decision = OPS.prescreen_decision
build_pool = OPS.build_pool
plan_apply = OPS.plan_apply
ground_one = OPS.ground_one
validate_result = OPS.validate_result
cmd_shard = OPS.cmd_shard
cmd_prescreen = OPS.cmd_prescreen
run_pilot_prescreen = OPS.run_pilot_prescreen
cmd_dispatch = OPS.cmd_dispatch
cmd_collect = OPS.cmd_collect
cmd_grounding = OPS.cmd_grounding
cmd_apply = OPS.cmd_apply
cmd_ledger = OPS.cmd_ledger
cmd_recheck = OPS.cmd_recheck
cmd_pilot = OPS.cmd_pilot
cmd_materials2 = OPS.cmd_materials2
run_materials = OPS.run_materials
run_pilot = OPS.run_pilot
cmd_gate = OPS.cmd_gate
load_worker_results = OPS.load_worker_results
render_brief = OPS.render_brief
Ctx = OPS.Ctx
RULE_VERSION = OPS.RULE_VERSION
ARBITRATION_VERSION = OPS.ARBITRATION_VERSION
DEFAULT_THRESHOLDS = OPS.DEFAULT_THRESHOLDS
DEFAULT_LIMIT_USD = OPS.DEFAULT_LIMIT_USD
DEFAULT_USD_PER_1K = OPS.DEFAULT_USD_PER_1K


def cmd_init(args: argparse.Namespace) -> None:
    batch_dir = BATCHES_ROOT / args.batch
    batch_dir.mkdir(parents=True, exist_ok=True)
    problems = [p for p in load_problems() if any(args.tag in t for t in p["tags"])]
    manifest = {
        "batch_id": args.batch, "relation": "pre", "tag": args.tag,
        "plan": "docs/plans/jev-problem-similarity-batch.md",
        "jev": {"endpoint": jev_client.DEFAULT_ENDPOINT, "model": jev_client.DEFAULT_MODEL},
        "question_template": str(QUESTIONS.relative_to(B.REPO_ROOT)),
        "git": B.git_state(), "problems": problems,
    }
    (batch_dir / "pre-manifest.json").write_text(json.dumps(manifest, ensure_ascii=False, indent=2), encoding="utf-8")
    print(f"批次 {args.batch}（{args.tag} 主题）：{len(problems)} 题，有难度分级 "
          f"{sum(1 for p in problems if p['tier'] is not None)} 题，已有 pre 的 {sum(1 for p in problems if p['existing_pre'])} 题")


def cmd_candidates(args: argparse.Namespace) -> None:
    """同标签交集 + 难度差窗口的假设对；方向按难度排（低→高）。

    修正（依据 2026-10-03 审核）：
    - 严格口径要求 1 <= Δrank <= 2（默认），同难度对不进 pre 管线（应属 common）；
    - 候选阶段**不消耗**每题 pre 写入名额（名额在写入/仲裁阶段按强度竞争）；
    - 排除辅助标签（tag-config.json 的 aux_tags），要求至少一个非辅助共同标签；
    - 导出被排除项及原因。
    """
    batch_dir = BATCHES_ROOT / args.batch
    manifest = json.loads((batch_dir / "pre-manifest.json").read_text(encoding="utf-8"))
    problems = [p for p in manifest["problems"] if p["tier"] is not None]
    min_delta = args.min_delta if args.min_delta is not None else CFG["candidate"]["min_delta"]
    max_delta = args.max_delta if args.max_delta is not None else CFG["candidate"]["max_delta"]
    existing = set()
    for p in problems:
        me = f"{p['oj']}/{p['problem_id']}"
        for t in p["existing_pre"]:
            existing.add((t, me)); existing.add((me, t))

    cands, skipped = [], []
    order = sorted(problems, key=lambda p: (p["tier"], p["oj"], p["problem_id"]))
    for i in range(len(order)):
        for j in range(i + 1, len(order)):
            a, b = order[i], order[j]
            delta = abs(a["tier"] - b["tier"])
            if delta < min_delta or delta > max_delta:
                continue
            shared = (set(a["tags"]) & set(b["tags"])) - AUX_TAGS
            if not shared:
                continue
            ka, kb = f"{a['oj']}/{a['problem_id']}", f"{b['oj']}/{b['problem_id']}"
            if (ka, kb) in existing:
                skipped.append({"a": ka, "b": kb, "reason": "已存在 pre 关系"}); continue
            cands.append({
                "a": {k: a[k] for k in ("oj", "problem_id", "dir", "tier", "difficulty", "title")},
                "b": {k: b[k] for k in ("oj", "problem_id", "dir", "tier", "difficulty", "title")},
                "delta": delta, "shared_tags": sorted(shared), "status": "pending",
            })
    (batch_dir / "pre-candidates.jsonl").write_text("\n".join(json.dumps(c, ensure_ascii=False) for c in cands) + "\n", encoding="utf-8")
    (batch_dir / "pre-candidates-excluded.jsonl").write_text("\n".join(json.dumps(c, ensure_ascii=False) for c in skipped) + "\n", encoding="utf-8")
    print(f"候选 {len(cands)} 对（难度差 {min_delta}~{max_delta}，非辅助共同标签；候选阶段不占名额）；"
          f"排除已存在 {len(skipped)} 对")
    print("难度差分布:", dict(Counter(c["delta"] for c in cands)))


def pair_key(c: dict) -> str:
    return f"{c['a']['oj']}/{c['a']['problem_id']}->{c['b']['oj']}/{c['b']['problem_id']}"


def _answers(ans: dict) -> dict:
    return {
        "A_is_step_to_B": ans["A_is_step_to_B"].get("noul"),
        "B_harder_than_A": ans["B_harder_than_A"].get("noul"),
        "same_core_model": ans["same_core_model"].get("noul"),
        "step_reused": ans["step_reused"].get("noul"),
    }


def cmd_materials(args: argparse.Namespace) -> None:
    batch_dir = BATCHES_ROOT / args.batch
    manifest = json.loads((batch_dir / "pre-manifest.json").read_text(encoding="utf-8"))
    mat_dir = batch_dir / "materials"
    mat_dir.mkdir(parents=True, exist_ok=True)
    if args.out:
        mat_dir = Path(args.out)
        mat_dir.mkdir(parents=True, exist_ok=True)
    n = 0
    for p in manifest["problems"]:
        lines = L.build_material(REPO_ROOT, p, with_line_numbers=args.line_numbers).splitlines()
        (mat_dir / f"{p['oj']}__{p['problem_id']}.md").write_text("\n".join(lines) + "\n", encoding="utf-8")
        n += 1
    print(f"生成材料 {n} 份 → {mat_dir}")


def _ask_pair(batch_dir: Path, a: dict, b: dict, questions: dict, tag: str) -> dict:
    state = {"problem_A_较简单": B.load_materials(batch_dir, a), "problem_B_较难": B.load_materials(batch_dir, b)}
    resp = jev_client.ask(state, questions, raw_dir=batch_dir / "raw", tag=tag)
    return {"answers": _answers(resp["answers"]), "usage": resp.get("usage", {})}


def cmd_calibrate(args: argparse.Namespace) -> None:
    batch_dir = BATCHES_ROOT / args.batch
    spec = json.loads((batch_dir / "pre-calibration.json").read_text(encoding="utf-8"))
    questions = json.loads(QUESTIONS.read_text(encoding="utf-8"))["questions"]
    results = []
    for pair in spec["pairs"]:
        r = _ask_pair(batch_dir, pair["a"], pair["b"], questions, f"precalib-{pair['id']}")
        row = {"pair_id": pair["id"], "expected": pair["expected"], "note": pair.get("note", ""),
               "a": f"{pair['a']['oj']}/{pair['a']['problem_id']}", "b": f"{pair['b']['oj']}/{pair['b']['problem_id']}",
               **r}
        results.append(row)
        a = row["answers"]
        print(f"  {row['pair_id']} expected={row['expected']:8} step={a['A_is_step_to_B']} "
              f"harder={a['B_harder_than_A']} same_core={a['same_core_model']}")
    (batch_dir / "pre-calibration-results.jsonl").write_text(
        "\n".join(json.dumps(r, ensure_ascii=False) for r in results) + "\n", encoding="utf-8")

    print("\n阈值网格（规则：step≥t1 且 harder≥t2 且 same_core≥t3）")
    best = None
    for t1 in (0.5, 0.6, 0.7, 0.75, 0.8, 0.9):
        for t2 in (0.3, 0.4, 0.5, 0.6, 0.7, 0.8):
            for t3 in (0.3, 0.4, 0.5, 0.6):
                fp = fn = 0
                for r in results:
                    a = r["answers"]
                    pred = (a["A_is_step_to_B"] >= t1 and a["B_harder_than_A"] >= t2 and a["same_core_model"] >= t3)
                    exp = r["expected"] == "pre"
                    fp += pred and not exp
                    fn += exp and not pred
                if fp == 0 and fn == 0 and (best is None or (t1, t2, t3) > best[1]):
                    best = ((fp, fn), (t1, t2, t3))
                if fp == 0 and fn <= 1:
                    print(f"  step>={t1} harder>={t2} same_core>={t3}  误连 {fp}  漏连 {fn}")
    if best:
        print(f"\n建议阈值: step>={best[1][0]} 且 harder>={best[1][1]} 且 same_core>={best[1][2]}")
    else:
        print("\n没有零误连零漏连的组合。")


def cmd_judge(args: argparse.Namespace) -> None:
    import threading
    from concurrent.futures import ThreadPoolExecutor

    batch_dir = BATCHES_ROOT / args.batch
    questions = json.loads(QUESTIONS.read_text(encoding="utf-8"))["questions"]
    cands = [json.loads(l) for l in (batch_dir / "pre-candidates.jsonl").read_text(encoding="utf-8").splitlines() if l.strip()]
    out_path = batch_dir / "pre-judge-results.jsonl"
    done = set()
    if out_path.exists():
        done = {json.loads(l)["key"] for l in out_path.read_text(encoding="utf-8").splitlines() if l.strip()}
    todo = [(i, c) for i, c in enumerate(cands) if pair_key(c) not in done]
    print(f"候选 {len(cands)} 对：已完成 {len(done)}，本次判断 {len(todo)}（workers={args.workers}）")
    lock = threading.Lock()
    n = [0]

    def work(item):
        idx, c = item
        try:
            r = _ask_pair(batch_dir, c["a"], c["b"], questions, f"pre-{idx:04d}")
        except Exception as e:
            with lock:
                with (batch_dir / "pre-failures.jsonl").open("a", encoding="utf-8") as f:
                    f.write(json.dumps({"idx": idx, "key": pair_key(c), "error": str(e)[:200]}, ensure_ascii=False) + "\n")
            print(f"  失败 {pair_key(c)}: {str(e)[:70]}", flush=True)
            return
        row = {"idx": idx, "key": pair_key(c), "delta": c["delta"],
               "a": f"{c['a']['oj']}/{c['a']['problem_id']}", "b": f"{c['b']['oj']}/{c['b']['problem_id']}",
               "model": jev_client.DEFAULT_MODEL, **r}
        with lock:
            with out_path.open("a", encoding="utf-8") as f:
                f.write(json.dumps(row, ensure_ascii=False) + "\n")
            n[0] += 1
            if n[0] % 50 == 0:
                print(f"  进度 {n[0]}/{len(todo)}", flush=True)

    with ThreadPoolExecutor(max_workers=args.workers) as ex:
        list(ex.map(work, todo))
    print(f"判断完成：累计 {len(done) + n[0]} 条 → {out_path}")


def cmd_decide(args: argparse.Namespace) -> None:
    batch_dir = BATCHES_ROOT / args.batch
    rows = [json.loads(l) for l in (batch_dir / "pre-judge-results.jsonl").read_text(encoding="utf-8").splitlines() if l.strip()]
    out = []
    for r in rows:
        a = r["answers"]
        p = a.get("rel_prob") or 0
        near = any(abs(a[k] - v) < args.margin for k, v in
                   (("A_is_step_to_B", args.t1), ("B_harder_than_A", args.t2), ("same_core_model", args.t3)))
        passed = a["relationship"] == "A_pre_B" and p >= args.t1 and a["A_step_used"] >= args.t2
        out.append({**r, "decision": "reject" if not passed else ("hold" if near else "write"), "near_boundary": near})
    (batch_dir / "pre-decisions.jsonl").write_text("\n".join(json.dumps(d, ensure_ascii=False) for d in out) + "\n", encoding="utf-8")
    c = Counter(d["decision"] for d in out)
    print(f"规则：relationship==A_pre_B 且 p>={args.t1} 且 A_step_used>={args.t2}（边界带宽 {args.margin}；difficulty_up 仅诊断）")
    print(f"共 {len(out)} 对：write {c['write']} / hold {c['hold']} / reject {c['reject']}")
    for d in out:
        if d["decision"] != "reject":
            a = d["answers"]
            print(f"  [{d['decision']:5}] {d['a']} -> {d['b']}  step={a['A_is_step_to_B']} "
                  f"harder={a['B_harder_than_A']} same_core={a['same_core_model']}")


def cmd_write(args: argparse.Namespace) -> None:
    batch_dir = BATCHES_ROOT / args.batch
    rows = [json.loads(l) for l in (batch_dir / "pre-reasons.jsonl").read_text(encoding="utf-8").splitlines() if l.strip()]
    n = 0
    with (batch_dir / "pre-writes.jsonl").open("a", encoding="utf-8") as wf:
        for r in rows:
            oj, pid = r["a"].split("/", 1)
            path = B.REPO_ROOT / r["b_dir"] / "index.md"
            before = path.read_text(encoding="utf-8")
            if args.dry_run:
                print(f"[dry-run] {r['b']} ← pre {r['a']}")
                continue
            after, applied = B.add_relation_item(before, "pre", {"oj": oj, "problem_id": pid}, r["reason"], args.now)
            if not applied:
                print(f"  跳过 {r['b']} ← {r['a']}（已存在）"); continue
            path.write_text(after, encoding="utf-8")
            wf.write(json.dumps({"batch_id": batch_dir.name, "key": r["key"], "dir": r["b_dir"], "target": r["a"],
                                 "action": "add-pre", "reason": r["reason"],
                                 "hash_before": hashlib.sha256(before.encode()).hexdigest()[:16],
                                 "hash_after": hashlib.sha256(after.encode()).hexdigest()[:16],
                                 "written_at": args.now}, ensure_ascii=False) + "\n")
            n += 1
    print(f"{'[dry-run] ' if args.dry_run else ''}写入完成：{n} 处 pre（单侧）→ pre-writes.jsonl")


def main() -> None:
    ap = argparse.ArgumentParser(description="前置关系(pre)批量补全管线",
                                 epilog="M0b 新增子命令见 docs/plans/pre-relations-full-coverage-plan.md §4")
    sub = ap.add_subparsers(dest="cmd", required=True)
    p = sub.add_parser("init"); p.add_argument("--batch", required=True); p.add_argument("--tag", required=True); p.set_defaults(func=cmd_init)
    p = sub.add_parser("candidates"); p.add_argument("--batch", required=True)
    p.add_argument("--min-delta", type=int, default=None, help="默认取 tag-config.json（1）")
    p.add_argument("--max-delta", type=int, default=None, help="默认取 tag-config.json（2）")
    p.add_argument("--max-pre", type=int, default=None, help="保留参数：候选阶段不再消耗名额")
    p.set_defaults(func=cmd_candidates)
    p = sub.add_parser("materials"); p.add_argument("--batch", required=True)
    p.add_argument("--line-numbers", action="store_true", help="材料带行号，便于 worker 直引 src_*")
    p.add_argument("--out", default=None, help="材料输出目录（默认批次目录/materials）")
    p.set_defaults(func=cmd_materials)
    p = sub.add_parser("calibrate"); p.add_argument("--batch", required=True); p.set_defaults(func=cmd_calibrate)
    p = sub.add_parser("judge"); p.add_argument("--batch", required=True)
    p.add_argument("--workers", type=int, default=4); p.set_defaults(func=cmd_judge)
    p = sub.add_parser("decide"); p.add_argument("--batch", required=True)
    p.add_argument("--t1", type=float, default=0.7, help="A_is_step_to_B 下限")
    p.add_argument("--t2", type=float, default=0.5, help="B_harder_than_A 下限")
    p.add_argument("--t3", type=float, default=0.4, help="same_core_model 下限")
    p.add_argument("--margin", type=float, default=0.05); p.set_defaults(func=cmd_decide)
    p = sub.add_parser("write"); p.add_argument("--batch", required=True)
    p.add_argument("--now", required=True); p.add_argument("--dry-run", action="store_true"); p.set_defaults(func=cmd_write)

    # ---------------- M0b 新增（全量 pre 批次，见规格 §4）
    p = sub.add_parser("shard", help="全仓候选生成 + 专题切分 + 固定归属校验")
    p.add_argument("--batch", required=True); p.add_argument("--now", required=True)
    p.add_argument("--limit", type=int, default=None, help="仅显示前 N 个分片")
    p.set_defaults(func=cmd_shard)

    p = sub.add_parser("prescreen", help="Jev 初筛（key 池并发；--simulate 为离线模拟，不发付费调用）")
    p.add_argument("--batch", required=True); p.add_argument("--workers", type=int, default=24)
    p.add_argument("--shard", default=None, help="只跑指定分片")
    p.add_argument("--limit", type=int, default=None, help="只跑前 N 个候选")
    p.add_argument("--keys-file", default=None, help="候选 key 清单文件（每行一个 key）")
    p.add_argument("--pilot", action="store_true", help="只跑 m1-candidates.txt 的试点候选")
    p.add_argument("--simulate", default=None, help="模拟响应 JSON：{key: {四问: 分数}}")
    p.add_argument("--limit-usd", type=float, default=DEFAULT_LIMIT_USD, help="本期预算上限（90%% 暂停线自动计算）")
    p.add_argument("--usd-per-1k", type=float, default=DEFAULT_USD_PER_1K, help="每千 token 单价（上界估算）")
    p.set_defaults(func=cmd_prescreen)

    p = sub.add_parser("dispatch", help="生成 worker 任务目录与任务书（不调用 herdr）")
    p.add_argument("--batch", required=True); p.add_argument("--now", required=True)
    p.add_argument("--n", type=int, default=1, help="本次派发任务数")
    p.add_argument("--shard", default=None); p.add_argument("--slots", default="", help="逗号分隔的槽位名")
    p.add_argument("--dry-run", action="store_true", help="只打印计划，不落盘")
    p.set_defaults(func=cmd_dispatch)

    p = sub.add_parser("collect", help="按 task-id 升序汇总 results/，只采纳最新有效 attempt")
    p.add_argument("--batch", required=True); p.add_argument("--now", required=True)
    p.set_defaults(func=cmd_collect)

    p = sub.add_parser("grounding", help="接地机检：引文/落点/方向/难度窗口/上限/无环/reason 形态")
    p.add_argument("--batch", required=True); p.add_argument("--now", required=True)
    p.add_argument("--recheck", action="store_true", help="recheck 模式：不因边已存在而拒绝")
    p.add_argument("--all", action="store_true", help="连 reject 一起机检（默认跳过 reject）")
    p.add_argument("--review-file", default=None, help="独立审核清单 JSON；其中 rejected 的题对降级为 doubtful")
    p.set_defaults(func=cmd_grounding)

    p = sub.add_parser("apply", help="全局仲裁 + 唯一写入者 + 台账（不加 --dry-run 时强制独立审核清单）")
    p.add_argument("--batch", required=True); p.add_argument("--now", required=True)
    p.add_argument("--dry-run", action="store_true")
    p.add_argument("--recheck", action="store_true"); p.add_argument("--shard", default=None)
    p.add_argument("--review-file", default=None); p.add_argument("--require-review", action="store_true")
    p.add_argument("--allow-after-gate", action="store_true", help="仅在用户已确认扩量后使用")
    p.set_defaults(func=cmd_apply)

    p = sub.add_parser("ledger", help="台账与一致性（含 recheck 与撤销核对）")
    p.add_argument("--batch", required=True); p.add_argument("--strict", action="store_true")
    p.add_argument("--json", action="store_true"); p.set_defaults(func=cmd_ledger)

    p = sub.add_parser("materials2", help="为指定/试点题目生成带行号的材料摘录")
    p.add_argument("--batch", required=True)
    p.add_argument("--only", default=None, help="逗号分隔的题目 key")
    p.add_argument("--pilot", action="store_true", help="只为 m1-candidates.txt 涉及的题目生成")
    p.add_argument("--no-line-numbers", action="store_true")
    p.set_defaults(func=cmd_materials2)

    p = sub.add_parser("pilot", help="M1 有界试点：从最大专题抽 <=bound 个候选（兼顾子分片与边界）")
    p.add_argument("--batch", required=True); p.add_argument("--now", required=True)
    p.add_argument("--bound", type=int, default=200)
    p.add_argument("--parents", default=None, help="逗号分隔的主标签；默认取最大专题")
    p.set_defaults(func=cmd_pilot)

    p = sub.add_parser("recheck", help="导出历史 pre 为重审任务（recheck 模式准备）")
    p.add_argument("--batch", required=True); p.add_argument("--now", required=True)
    p.set_defaults(func=cmd_recheck)

    p = sub.add_parser("gate", help="闸门与批次状态：m1-complete / resume / set-thresholds / slots / task-state")
    p.add_argument("action", choices=["m1-complete", "waiting-user", "resume", "set-thresholds", "slots", "task-state"])
    p.add_argument("--batch", required=True); p.add_argument("--now", required=True)
    p.add_argument("--thresholds", default=""); p.add_argument("--slots", default="")
    p.add_argument("--task-id", default=""); p.add_argument("--state", default="")
    p.add_argument("--slot", default=""); p.add_argument("--restart", action="store_true")
    p.set_defaults(func=cmd_gate)

    p = sub.add_parser("selftest", help="M0b 离线自检：fixture 仓库跑完整管线，验证 §15.1 六项检查")
    p.add_argument("--workdir", default=None)
    p.add_argument("--report", default="relation-batches/pre-full-20261003/m0-checks.json")
    p.set_defaults(func=cmd_selftest)

    args = ap.parse_args()
    args.func(args)


def cmd_selftest(args) -> None:
    argv = ["prebatch_selftest"]
    if args.workdir:
        argv += ["--workdir", args.workdir]
    argv += ["--report", args.report]
    old = sys.argv
    sys.argv = argv
    try:
        raise SystemExit(SELFTEST.main())
    finally:
        sys.argv = old


if __name__ == "__main__":
    main()
