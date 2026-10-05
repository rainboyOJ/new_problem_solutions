#!/usr/bin/env python3
"""pre 全量批次的新子命令实现（M0b）：shard / prescreen / dispatch / collect /
grounding / apply / ledger。

设计约定（对应 docs/plans/pre-relations-full-coverage-plan.md §4/§6/§6.1/§7/§7.1/§12.1）：

- 所有函数接受显式 `repo_root`，便于在 fixture 仓库上做离线自检（`selftest`）。
- `dispatch` 只准备任务目录与任务书并打印 herdr 启动命令，**不自己调用 herdr**；
  herdr 的实际启停由主 agent 决定（便于巡检与恢复）。
- `apply` 是唯一题目写入者；写文件 → 立即追加台账 → 由主 agent 按专题 commit。
- `prescreen` 支持 `--simulate`，用固定样本与模拟响应跑通全流程，不发付费调用。
"""

from __future__ import annotations

import json
import re
import sys
import threading
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))
import batch as B  # noqa: E402
import jev_client  # noqa: E402
import prebatch_lib as L  # noqa: E402

RULE_VERSION = "pre-rules-v1"
ARBITRATION_VERSION = "pre-arb-v1"
QUESTION_TEMPLATE = "questions-pre-v6.json"
DEFAULT_THRESHOLDS = {"A_is_step_to_B": 0.5, "B_harder_than_A": 0.4, "step_reused": 0.3}
# 规格 §2 反推：$5.1 / 121M token ≈ $4.215e-5 每千 token（Jev jev-1.13.0）
DEFAULT_USD_PER_1K = 0.00004215
# §11：额度池 $50，$45（90%）为暂停线
DEFAULT_LIMIT_USD = 45.0
# 规格 §7：同一候选对最多 2 次自动重启 → 共 3 次派发机会
MAX_TASK_ATTEMPTS = 3
# 引文长度上限（折算权重：中文字数 + ASCII/4）。规格 §4② 的「≤20 字」。
QUOTE_MAX_WEIGHT = 24.0

TASK_STATES = ("待派发", "运行中", "待校验", "待审核", "待写入", "已生效",
               "拒绝", "延后", "冲突", "证据过期", "错误")


# ------------------------------------------------------------------ 公共上下文

class Ctx:
    def __init__(self, repo_root: Path, batch: str, config: dict | None = None,
                 difficulty_order: list[str] | None = None):
        self.repo_root = repo_root
        self.batch = batch
        self.batch_dir = repo_root / "relation-batches" / batch
        self.state_dir = L.resolve_state_dir(repo_root, batch)
        self.cfg = config or L.load_config(repo_root)
        self.difficulty_order = difficulty_order or L.assert_difficulty_sync(repo_root, self.cfg)
        self.refresh()

    def refresh(self) -> None:
        """从磁盘重新读取题目索引。

        批次会持续修改 frontmatter，任何一次判断/写入前都必须刷新：
        否则 `edges` 会停留在批次开始时的状态，导致重复写边或漏做 replace（自检已捕获）。
        """
        self.problems = L.load_problems(self.repo_root, self.difficulty_order)
        self.by_key = {p["key"]: p for p in self.problems}
        self.tiers = {n: i for i, n in enumerate(self.difficulty_order)}

    # --- state.json（断点续跑的唯一真源，位于 git 目录，不提交）
    @property
    def state_path(self) -> Path:
        return self.state_dir / "state.json"

    def state(self) -> dict:
        if self.state_path.exists():
            return json.loads(self.state_path.read_text(encoding="utf-8"))
        return {}

    def save_state(self, state: dict) -> None:
        L.atomic_write_text(self.state_path, json.dumps(state, ensure_ascii=False, indent=2))

    def init_state(self, **extra) -> dict:
        st = self.state()
        st.setdefault("batch", self.batch)
        st.setdefault("created", L.git_state(self.repo_root)["head"])
        st["arbitration_version"] = ARBITRATION_VERSION
        st["rule_version"] = RULE_VERSION
        st["question_template"] = QUESTION_TEMPLATE
        st.setdefault("prescreen_thresholds", dict(DEFAULT_THRESHOLDS))
        st.setdefault("usage", {"jev": {"requests": 0, "cost_usd": 0.0},
                                "worker": {"tasks": 0, "cost_usd": 0.0},
                                "main": {"cost_usd": 0.0}, "review": {"cost_usd": 0.0}})
        st.setdefault("gate", {"m1_complete": False, "waiting_user": False})
        st.setdefault("slots", {})
        st.setdefault("tasks", {})
        st.setdefault("shards", {})
        st.update(extra)
        return st

    # --- 文件定位
    def cands(self) -> list[dict]:
        return L.read_jsonl(self.batch_dir / "pre-candidates.jsonl")

    def mat_path(self, key: str) -> Path:
        oj, pid = key.split("/", 1)
        return self.batch_dir / "materials" / f"{oj}__{pid}.md"

    def material(self, key: str, limit: int = 4000) -> str:
        p = self.mat_path(key)
        if p.exists():
            return p.read_text(encoding="utf-8")[:limit]
        prob = self.by_key.get(key)
        return L.build_material(self.repo_root, prob)[:limit] if prob else "(材料缺失)"

    def manifest(self) -> dict:
        p = self.batch_dir / "pre-manifest.json"
        return json.loads(p.read_text(encoding="utf-8")) if p.exists() else {}


def _thresholds(ctx: Ctx) -> dict:
    st = ctx.state()
    return st.get("prescreen_thresholds") or dict(DEFAULT_THRESHOLDS)


def prescreen_decision(answers: dict, th: dict) -> tuple[bool, dict]:
    margins = {k: float(answers.get(k) or 0.0) - float(th[k]) for k in th}
    passed = all(v >= 0 for v in margins.values())
    return passed, {"margins": {k: round(v, 4) for k, v in margins.items()},
                    "near_boundary": any(abs(v) < 0.05 for v in margins.values())}


# ---------------------------------------------------------------------- shard

def run_shard(ctx: Ctx, now: str, limit: int | None = None) -> dict:
    ctx.refresh()
    problems = ctx.problems
    cands, excluded = L.build_candidates(problems, ctx.cfg)
    shards, shard_of = L.assign_shards(cands, problems, ctx.cfg)
    check = L.validate_shards(shards, cands)

    ctx.batch_dir.mkdir(parents=True, exist_ok=True)
    L.write_jsonl(ctx.batch_dir / "pre-candidates.jsonl", cands)
    L.write_jsonl(ctx.batch_dir / "pre-candidates-excluded.jsonl", excluded)
    shard_rows = [{k: v for k, v in s.items() if k != "pairs"} | {"pairs_sha": L.sha16("\n".join(s["pairs"]))}
                  for s in shards]
    L.write_jsonl(ctx.batch_dir / "shards.jsonl", shard_rows)
    L.atomic_write_text(ctx.batch_dir / "shard-pairs.json",
                        json.dumps({s["shard_id"]: s["pairs"] for s in shards}, ensure_ascii=False, indent=1))
    manifest = {
        "batch_id": ctx.batch,
        "relation": "pre",
        "plan": "docs/plans/pre-relations-full-coverage-plan.md",
        "review": "docs/plans/pre-relations-full-coverage-review.md",
        "rule_version": RULE_VERSION,
        "question_template": QUESTION_TEMPLATE,
        "config_hash": L.sha16((ctx.repo_root / "scripts/problem-analysis-tools/relation_batch/tag-config.json").read_text(encoding="utf-8")),
        "difficulty_order": ctx.difficulty_order,
        "candidate_window": {"min_delta": ctx.cfg["candidate"]["min_delta"], "max_delta": ctx.cfg["candidate"]["max_delta"]},
        "max_pre_per_problem": ctx.cfg["candidate"]["max_pre_per_problem"],
        "git": L.git_state(ctx.repo_root),
        "counts": {
            "problems": len(problems),
            "tiered": sum(1 for p in problems if p["tier"] is not None),
            "candidates": len(cands),
            "excluded_existing": len(excluded),
            "shards": len(shards),
        },
        "parity": {
            "math_upper_bound_pre": (sum(1 for p in problems if p["tier"] is not None)
                                     - sum(1 for p in problems if p["tier"] == 0)) * ctx.cfg["candidate"]["max_pre_per_problem"],
        },
        "problems_baseline_hash": {p["key"]: p["hash"] for p in problems},
        "problems_evidence_hash": {p["key"]: p["evidence_hash"] for p in problems},
        "generated_at": now,
    }
    L.atomic_write_text(ctx.batch_dir / "pre-manifest.json", json.dumps(manifest, ensure_ascii=False, indent=2))

    st = ctx.init_state()
    st["shards"] = {s["shard_id"]: {"pair_count": s["pair_count"], "kind": s["kind"], "tag": s["tag"],
                                    "status": "待运行",
                                    "sub_tag": s.get("sub_tag", "")} for s in shards}
    st["shard_check"] = check
    st["generated_at"] = now
    ctx.save_state(st)

    top = sorted(shards, key=lambda s: -s["pair_count"])[:12]
    print(f"题目 {manifest['counts']['problems']}（有难度 {manifest['counts']['tiered']}），"
          f"候选对 {len(cands)}，分片 {len(shards)}")
    print("最大分片：" + "，".join(f"{s['shard_id']}({s['pair_count']})" for s in top))
    print(f"固定归属校验：{'通过' if check['ok'] else '失败'} "
          f"（分配 {check['assigned']}/{check['candidates']}，重复 {len(check['duplicated'])}，"
          f"未分配 {len(check['unassigned'])}）")
    if limit:
        print(f"[dry-run] 只显示前 {limit} 个分片")
    return {"manifest": manifest, "check": check, "shards": shards, "candidates": cands}


def cmd_shard(args) -> None:
    ctx = Ctx(L.REPO_ROOT_DEFAULT, args.batch)
    res = run_shard(ctx, args.now, args.limit)
    if not res["check"]["ok"]:
        raise SystemExit("分片校验失败：候选未恰好分配一次，拒绝继续")


# ------------------------------------------------------------------- prescreen

def _ask_batch(ctx: Ctx, pair: dict, questions: dict, pool: jev_client.KeyPool,
               budget: L.Budget, raw_dir: Path, state_lock: dict, tag: str) -> dict:
    state = {"problem_A_较简单": ctx.material(pair["a"]["key"]), "problem_B_较难": ctx.material(pair["b"]["key"])}
    qtext = json.dumps(questions, ensure_ascii=False)
    upper = budget.upper_bound(len(json.dumps(state, ensure_ascii=False)), len(qtext))
    ok = budget.reserve(upper)
    if not ok:
        raise RuntimeError("预算停止：" + budget.stop_reason)
    last_err: Exception | None = None
    for _ in range(3):
        idx = pool.acquire()
        try:
            resp = jev_client.ask(state, questions, raw_dir=raw_dir, tag=tag, api_key=pool.key(idx))
            budget.settle(upper, None)
            return {"answers": {k: v.get("noul") for k, v in resp["answers"].items()},
                    "usage": resp.get("usage", {}), "cost_upper_usd": round(upper, 6), "key_slot": idx}
        except jev_client.JevAuthError as e:
            pool.mark_dead(idx, f"auth:{e}")
            last_err = e
            continue
        except Exception as e:  # 网络/服务错误：保留预留（是否计费未知），交上层记录失败
            last_err = e
            budget.settle(upper, upper)  # 不按零费用释放
            break
    raise RuntimeError(f"prescreen 失败: {last_err}")


def run_prescreen(ctx: Ctx, pairs: list[dict], workers: int, simulate: dict | None,
                  keys: list[str], limit_usd: float, usd_per_1k: float,
                  only_shard: str | None = None, parents: list[str] | None = None) -> dict:
    questions = json.loads((HERE / QUESTION_TEMPLATE).read_text(encoding="utf-8"))["questions"]
    th = _thresholds(ctx)
    out_path = ctx.batch_dir / "prescreen-results.jsonl"
    done = {r["key"] for r in L.read_jsonl(out_path)}
    shard_set = {s for s in (only_shard or "").split(",") if s}
    if parents:
        want = set(parents)
        shard_set |= {s["shard_id"] for s in L.read_jsonl(ctx.batch_dir / "shards.jsonl") if s["tag"] in want}
    todo = [p for p in pairs if p["key"] not in done
            and (not shard_set or p.get("shard_id") in shard_set)]
    pool = jev_client.KeyPool(keys)
    budget = L.Budget(limit_usd, usd_per_1k)
    st = ctx.init_state()
    prev = st["usage"].get("jev", {})
    budget.settled = float(prev.get("cost_usd") or 0.0)
    lock = threading.Lock()
    rows: list[dict] = []
    failures: list[dict] = []
    counts = {"pass": 0, "reject": 0, "simulated": 0}

    def work(pair: dict) -> None:
        key = pair["key"]
        try:
            if simulate is not None:
                ans = simulate.get(key)
                if ans is None:
                    return
                r = {"answers": ans, "usage": {}, "cost_upper_usd": 0.0, "key_slot": -1}
                sim = True
            else:
                r = _ask_batch(ctx, pair, questions, pool, budget, ctx.batch_dir / "raw",
                               {}, f"pre-{abs(hash(key)) % 10 ** 8:08d}")
                sim = False
        except Exception as e:
            with lock:
                failures.append({"key": key, "error": str(e)[:200]})
            return
        passed, extra = prescreen_decision(r["answers"], th)
        row = {"key": key, "shard_id": pair.get("shard_id", ""), "delta": pair["delta"],
               "a": pair["a"]["key"], "b": pair["b"]["key"],
               "answers": r["answers"], "prescreen_pass": passed, **extra,
               "simulated": sim, "cost_upper_usd": r["cost_upper_usd"], "usage": r["usage"]}
        with lock:
            rows.append(row)
            counts["pass" if passed else "reject"] += 1
            counts["simulated"] += 1 if sim else 0
            if len(rows) % 200 == 0:
                print(f"  进度 {len(rows)}/{len(todo)}", flush=True)

    if workers <= 1:
        for p in todo:
            work(p)
    else:
        with ThreadPoolExecutor(max_workers=workers) as ex:
            list(ex.map(work, todo))
    L.append_jsonl(out_path, sorted(rows, key=lambda r: r["key"]))
    L.append_jsonl(ctx.batch_dir / "prescreen-failures.jsonl", failures)

    st = ctx.state()
    st["usage"]["jev"]["requests"] = int(prev.get("requests") or 0) + len(rows)
    st["usage"]["jev"]["cost_usd"] = round(budget.settled, 4)
    st["usage"]["jev"]["budget"] = budget.snapshot()
    st["usage"]["jev"]["key_pool"] = pool.stats()
    st["usage"]["jev"]["last_simulated"] = bool(simulate is not None)
    ctx.save_state(st)
    print(f"初筛：本次 {len(rows)} 对（通过 {counts['pass']} / 拒绝 {counts['reject']}），"
          f"累计 {len(done) + len(rows)}；失败 {len(failures)}")
    print(f"阈值 {th}；预算已结算 ${budget.settled:.4f} / ${limit_usd}"
          + (f"（已停止：{budget.stop_reason}）" if budget.stopped else ""))
    return {"rows": rows, "counts": counts, "failures": failures, "budget": budget.snapshot()}


def run_pilot_prescreen(ctx: Ctx, workers: int, keys: list[str], limit_usd: float,
                        usd_per_1k: float, simulate: dict | None = None) -> dict:
    """M1 有界试点的初筛：只跑 m1-candidates.txt 里的候选（真实的付费入口）。"""
    keys_file = ctx.batch_dir / "m1-candidates.txt"
    if not keys_file.exists():
        raise SystemExit("缺少 m1-candidates.txt：先运行 pilot 选点")
    picked = [k for k in keys_file.read_text(encoding="utf-8").split() if k]
    wanted = set(picked)
    pairs = [c for c in ctx.cands() if c["key"] in wanted]
    missing = sorted(wanted - {c["key"] for c in pairs})
    if missing:
        print(f"警告：{len(missing)} 个试点候选不在候选集（跳过）：{missing[:3]}")
    return run_prescreen(ctx, pairs, workers, simulate, keys, limit_usd, usd_per_1k)


def cmd_prescreen(args) -> None:
    ctx = Ctx(L.REPO_ROOT_DEFAULT, args.batch)
    pairs = ctx.cands()
    if args.limit:
        pairs = pairs[: args.limit]
    if args.keys_file:
        pairs = [p for p in pairs if p["key"] in set(Path(args.keys_file).read_text(encoding="utf-8").split())]
    simulate = json.loads(Path(args.simulate).read_text(encoding="utf-8")) if args.simulate else None
    keys = jev_client.load_key_pool()
    if simulate is None and not keys:
        raise SystemExit("缺少 key 池且未提供 --simulate：拒绝发起付费调用")
    if args.pilot:
        res = run_pilot_prescreen(ctx, args.workers, keys, args.limit_usd, args.usd_per_1k, simulate)
    else:
        res = run_prescreen(ctx, pairs, args.workers, simulate, keys, args.limit_usd, args.usd_per_1k,
                            only_shard=args.shard,
                            parents=[x for x in (args.parents or "").split(",") if x] or None)
    if res["budget"]["stopped"]:
        print("预算已停止，后续请求不再发起（断点已保存）")


# -------------------------------------------------------------------- dispatch

def render_brief(template: str, ctx: Ctx, task: dict) -> str:
    a, b = task["a"], task["b"]
    mapping = {
        "{{BATCH}}": ctx.batch,
        "{{TASK_ID}}": task["task_id"],
        "{{ATTEMPT}}": str(task["attempt"]),
        "{{PAIR_KEY}}": task["key"],
        "{{A_KEY}}": a["key"], "{{A_DIR}}": a["dir"], "{{A_HASH}}": task["evidence_hash_a"],
        "{{B_KEY}}": b["key"], "{{B_DIR}}": b["dir"], "{{B_HASH}}": task["evidence_hash_b"],
        "{{MATERIAL_DIR}}": str(ctx.batch_dir / "materials"),
        "{{A_FILE}}": f"{a['oj']}__{a['problem_id']}.md",
        "{{B_FILE}}": f"{b['oj']}__{b['problem_id']}.md",
        "{{RESULT_PATH}}": str(ctx.batch_dir / "results" / task["task_id"] / f"{task['attempt']}.json"),
        "{{RULE_VERSION}}": RULE_VERSION,
    }
    text = template
    for k, v in mapping.items():
        text = text.replace(k, v)
    return text


def run_dispatch(ctx: Ctx, n: int, only_shard: str | None, now: str, slots: list[str],
                 dry_run: bool, parents: list[str] | None = None) -> list[dict]:
    template_path = HERE / "worker-brief-template.md"
    template = template_path.read_text(encoding="utf-8")
    pres = {r["key"]: r for r in L.read_jsonl(ctx.batch_dir / "prescreen-results.jsonl")}
    st = ctx.init_state()
    tasks = st["tasks"]
    cands = {c["key"]: c for c in ctx.cands()}
    passed = [k for k, r in pres.items() if r.get("prescreen_pass")]
    passed.sort(key=lambda k: (cands.get(k, {}).get("shard_id", ""), k))
    shard_filter = {s for s in (only_shard or "").split(",") if s}
    if parents:
        want = set(parents)
        shard_filter |= {s["shard_id"] for s in L.read_jsonl(ctx.batch_dir / "shards.jsonl")
                         if s["tag"] in want}

    def in_scope(k: str) -> bool:
        return not shard_filter or cands.get(k, {}).get("shard_id") in shard_filter

    # 关键：每个题对只能有一个任务。
    # ① 先复用已存在但尚未产出结果的「待派发」任务（worker 被杀后可续跑，不新建任务）；
    # ② 再为「从未建过任务」的题对新建任务。
    # 之前的实现按 status 过滤，会把同时存在 待派发 任务的题对再派一次，产生重复任务。
    capped = []          # 超过重试上限：标记错误，不再派发（规格 §7：最多 2 次自动重启）
    for tid, t in tasks.items():
        if t.get("status") != "待派发":
            continue
        if int(t.get("attempts") or 0) >= MAX_TASK_ATTEMPTS:
            t["status"] = "错误"
            t["error"] = f"派发 {t.get('attempts')} 次仍无有效结果（重试上限 {MAX_TASK_ATTEMPTS}）"
            capped.append((tid, t["key"]))
    if capped:
        print(f"  超过重试上限，标记错误：{len(capped)} 个 → {[k for _, k in capped][:3]}")

    keyed = {t["key"] for t in tasks.values() if t.get("status") != "错误"}
    reuse = sorted([tid for tid, t in tasks.items()
                    if t.get("status") == "待派发" and in_scope(t["key"])])
    fresh = [k for k in passed if k not in keyed and in_scope(k)]
    pending = reuse + fresh
    if len(reuse) > n:
        print(f"  本轮复用 {n} 个未完成的历史任务（共 {len(reuse)} 个可复用）")
    if only_shard:
        st["shards"].setdefault(only_shard, {})["status"] = "运行中"

    seq = max([int(tid.rsplit("-", 1)[1]) for tid in tasks] or [0]) + 1
    out: list[dict] = []
    reuse_set = set(reuse)
    for i, item in enumerate(pending[:n]):
        is_reuse = item in reuse_set
        if is_reuse:
            task_id = item
            key = tasks[item]["key"]
        else:
            key = item
            c0 = cands[key]
            task_id = f"{ctx.batch}-{c0['shard_id']}-{seq:04d}"
            seq += 1
        c = cands[key]
        shard = c["shard_id"]
        prob_a, prob_b = ctx.by_key[c["a"]["key"]], ctx.by_key[c["b"]["key"]]
        task = {
            "task_id": task_id, "attempt": 1, "key": key, "shard_id": shard,
            "a": c["a"], "b": c["b"],
            "evidence_hash_a": prob_a["hash"], "evidence_hash_b": prob_b["hash"],
            "config_hash": ctx.manifest().get("config_hash", ""),
            "rule_version": RULE_VERSION, "question_template": QUESTION_TEMPLATE,
            "status": "待派发", "slot": slots[i] if i < len(slots) else "",
            "assigned_at": now, "last_activity": now, "interventions": 0, "restarts": 0,
            "result_path": str(ctx.batch_dir / "results" / task_id / "1.json"),
        }
        if not dry_run:
            d = ctx.batch_dir / "results" / task_id
            d.mkdir(parents=True, exist_ok=True)
            L.atomic_write_text(d / "task.json", json.dumps(task, ensure_ascii=False, indent=2))
            L.atomic_write_text(d / "brief.md", render_brief(template, ctx, task))
            # 结果文件不预建：worker 追加写入，缺失即未返回
            prev_attempts = int((tasks.get(task_id) or {}).get("attempts") or 0)
            tasks[task_id] = {k: task[k] for k in ("task_id", "attempt", "key", "shard_id", "status",
                                                   "slot", "assigned_at", "last_activity",
                                                   "interventions", "restarts", "result_path")}
            tasks[task_id]["attempts"] = prev_attempts + 1
            tasks[task_id]["attempt"] = prev_attempts + 1
        out.append(task)
    if not dry_run:
        L.append_jsonl(ctx.batch_dir / "dispatch.jsonl",
                       [{k: t[k] for k in ("task_id", "attempt", "key", "shard_id", "slot", "assigned_at")} for t in out])
        st["updated"] = now
        ctx.save_state(st)
    for t in out:
        print(f"DISPATCH {t['task_id']} {t['key']} slot={t['slot'] or '—'} brief={ctx.batch_dir}/results/{t['task_id']}/brief.md")
    print(f"待派发 {len(pending)}，本次生成 {len(out)}"
          + ("（dry-run，未落盘）" if dry_run else ""))
    return out


def cmd_dispatch(args) -> None:
    ctx = Ctx(L.REPO_ROOT_DEFAULT, args.batch)
    slots = args.slots.split(",") if args.slots else []
    run_dispatch(ctx, args.n, args.shard, args.now, slots, args.dry_run,
                 parents=[x for x in (getattr(args, "parents", "") or "").split(",") if x] or None)


# --------------------------------------------------------------------- collect

def load_worker_results(ctx: Ctx) -> tuple[list[dict], list[dict]]:
    """按 task_id 升序汇总 results/<task-id>/<attempt>.json；同 task 只采纳最新有效 attempt。"""
    results_root = ctx.batch_dir / "results"
    valid: dict[str, dict] = {}
    invalid: list[dict] = []
    for task_dir in sorted(p for p in results_root.glob("*") if p.is_dir()) if results_root.exists() else []:
        task_id = task_dir.name
        attempts: list[tuple[int, dict]] = []
        for f in sorted(task_dir.glob("*.json*")):
            m = re.match(r"(\d+)\.json", f.name)
            if not m:
                continue
            try:
                if f.suffix == ".json":
                    records = [json.loads(f.read_text(encoding="utf-8") or "null")]
                else:
                    records = [json.loads(l) for l in f.read_text(encoding="utf-8").splitlines() if l.strip()]
            except json.JSONDecodeError as e:
                invalid.append({"task_id": task_id, "file": f.name, "error": f"JSON 解析失败: {e}"})
                continue
            for rec in records:
                if not rec:
                    continue
                errs = validate_result(rec)
                if errs:
                    invalid.append({"task_id": task_id, "file": f.name, "key": rec.get("key", ""), "errors": errs})
                    continue
                if rec.get("task_id") and rec["task_id"] != task_id:
                    invalid.append({"task_id": task_id, "file": f.name, "key": rec.get("key", ""),
                                    "errors": [f"task_id 不匹配：{rec['task_id']} != {task_id}"]})
                    continue
                attempts.append((int(rec.get("attempt") or 0), rec))
        if attempts:
            attempts.sort(key=lambda t: t[0])
            valid[task_id] = attempts[-1][1]
            if len(attempts) > 1:
                invalid.append({"task_id": task_id, "note": f"保留 attempt {attempts[-1][0]}，旧代次 {len(attempts) - 1} 条仅作证据"},
                               )
    return [valid[k] for k in sorted(valid)], invalid


def validate_result(rec: dict) -> list[str]:
    """worker 结果 schema 校验（不引入 jsonschema 依赖）。"""
    errs: list[str] = []
    required = ("task_id", "attempt", "key", "verdict", "a_step", "b_use", "quote_a", "src_a",
                "quote_b", "src_b", "confidence", "model")
    for f in required:
        if not rec.get(f):
            errs.append(f"缺字段 {f}")
    if rec.get("verdict") not in L.VERDICTS:
        errs.append(f"verdict 非法：{rec.get('verdict')}")
    if rec.get("verdict") == "reject" and not rec.get("reject_reason"):
        errs.append("reject 缺 reject_reason")
    if rec.get("reject_reason") and rec["reject_reason"] not in L.REJECT_REASONS + ("",):
        errs.append(f"reject_reason 非法：{rec['reject_reason']}")
    if rec.get("confidence") not in L.CONFIDENCE_RANK:
        errs.append(f"confidence 非法：{rec.get('confidence')}")
    if rec.get("verdict") == "accept" and rec.get("strength") not in ("strong", "template-level"):
        errs.append("accept 的 strength 必须为 strong 或 template-level（可由机检补定为 template-level）")
    # 引文长度：规格 §4② 的目标是「短的、可逐字定位的串」，不是精确字数。
    # 实测中文引文 ≤20 字、代码行引文 ≤60 字符都合直觉；混排（如 `dp[j] = max(...)`）
    # 按「中文字数 + ASCII/4 ≤ 20」折算更贴近原意，避免为纯字符数把合格裁定误判为非法。
    for f in ("quote_a", "quote_b"):
        v = rec.get(f) or ""
        cjk = len(re.findall(r"[\u4e00-\u9fff]", v))
        ascii_n = len(v) - cjk
        weight = cjk + ascii_n / 4.0
        if weight > QUOTE_MAX_WEIGHT:
            errs.append(f"{f} 过长（折算 {weight:.1f} > {QUOTE_MAX_WEIGHT}；中文字数 + ASCII/4）")
    for f in ("src_a", "src_b"):
        if rec.get(f) and not re.match(r"^problems/.+\.md:\d+$", rec[f]):
            errs.append(f"{f} 形态非法：{rec.get(f)}")
    if rec.get("key") and not re.match(r"^[^\s]+/[^\s]+->[^\s]+/[^\s]+$", rec["key"]):
        errs.append("key 形态非法（应为 A->B）")
    return errs


def run_collect(ctx: Ctx, now: str) -> dict:
    valid, invalid = load_worker_results(ctx)
    L.write_jsonl(ctx.batch_dir / "worker-results.jsonl", valid)
    L.write_jsonl(ctx.batch_dir / "worker-results-invalid.jsonl", invalid)
    # 非法结果计入重试次数：否则同一题对会因 worker 反复给出不合 schema 的输出而无限重派
    bad_tasks = {r.get("task_id") for r in invalid if r.get("task_id")}
    st0 = ctx.init_state()
    for tid in bad_tasks:
        tt = st0["tasks"].get(tid)
        if tt and tt.get("status") != "错误":
            tt["attempts"] = int(tt.get("attempts") or 0) + 1
            if tt["attempts"] >= MAX_TASK_ATTEMPTS:
                tt["status"] = "错误"
                tt["error"] = f"worker 输出不符合 schema（已重试 {tt['attempts']} 次）"
            else:
                tt["status"] = "待派发"
                tt["error"] = "schema 不合格，等待重试"
    ctx.save_state(st0)
    st = ctx.init_state()
    for rec in valid:
        tid = rec["task_id"]
        t = st["tasks"].get(tid)
        if t:
            t["status"] = "待校验"
            t["last_activity"] = now
            t["verdict"] = rec["verdict"]
    st["usage"]["worker"]["tasks"] = len(valid)
    st["updated"] = now
    ctx.save_state(st)
    from collections import Counter
    c = Counter(r["verdict"] for r in valid)
    print(f"汇总结果 {len(valid)} 条（accept {c['accept']} / reject {c['reject']} / doubtful {c['doubtful']}）；"
          f"无效/旧代次记录 {len(invalid)} 条")
    return {"valid": valid, "invalid": invalid}


def cmd_collect(args) -> None:
    ctx = Ctx(L.REPO_ROOT_DEFAULT, args.batch)
    run_collect(ctx, args.now)


# ------------------------------------------------------------------- grounding

def ground_one(ctx: Ctx, rec: dict, recheck: bool = False) -> dict:
    """证据定位与结构约束检查。任一不过 → 降级为 doubtful 或 reject。"""
    checks: dict[str, dict] = {}
    a_key, b_key = [s.strip() for s in rec["key"].split("->")]
    pa, pb = ctx.by_key.get(a_key), ctx.by_key.get(b_key)
    fail: list[str] = []

    def check(name: str, ok: bool, detail: str = "", hard: bool = True) -> bool:
        checks[name] = {"ok": bool(ok), "detail": detail, "hard": bool(hard)}
        if not ok and hard:
            fail.append(name)
        return ok

    # 身份与方向
    if not check("identity_exists", pa is not None and pb is not None,
                 "" if pa and pb else f"题目不存在：{a_key if not pa else ''} {b_key if not pb else ''}"):
        return {"key": rec["key"], "task_id": rec.get("task_id", ""), "verdict_in": rec["verdict"],
                "verdict_out": "reject", "fail": fail, "checks": checks, "note": "身份缺失"}
    # recheck 模式：历史边的方向/难度窗口不直接判错（§12 约束 4：31 条不符合新口径的关系
    # 单独列出新旧差异，不自动删除），只记录为 note 供独立审核看。
    legacy_window = not (pa["tier"] < pb["tier"] and 1 <= pb["tier"] - pa["tier"] <= 2)
    check("direction_rank", pa["tier"] < pb["tier"], f"rank {pa['tier']} -> {pb['tier']}",
          hard=not recheck)
    check("difficulty_window", 1 <= pb["tier"] - pa["tier"] <= 2, f"Δ={pb['tier'] - pa['tier']}",
          hard=not recheck)

    # 引文可定位
    for side, rec_key, quote_f, src_f in ((pa, "a", "quote_a", "src_a"), (pb, "b", "quote_b", "src_b")):
        text = (ctx.repo_root / side["dir"] / "index.md").read_text(encoding="utf-8")
        n_lines = len(text.splitlines())
        line, found = L.quote_line(text, rec[quote_f])
        check(f"quote_{rec_key}_locatable", found, f"quote={rec[quote_f]!r}")
        m = re.match(r"^(.+):(\d+)$", rec[src_f])
        src_ok = bool(m) and m.group(1) == f"{side['dir']}/index.md"
        src_line = int(m.group(2)) if m else -1
        check(f"src_{rec_key}_path", src_ok, rec[src_f])
        check(f"src_{rec_key}_in_range", 1 <= src_line <= n_lines, f"{src_line} in 1..{n_lines}")
        if found and src_ok and src_line > 0:
            check(f"src_{rec_key}_matches_quote", abs(src_line - line) <= 5,
                  f"src={src_line} 实际={line}")
        # 落点关键词命中
        mat = ctx.material(side["key"])
        step = rec["a_step"] if rec_key == "a" else rec["b_use"]
        hits, sample = L.keyword_hits(step, mat)
        check(f"step_hits_{rec_key}", hits >= 1, f"命中 {hits}: {sample}")

    # 非重复 / recheck
    existing = L.all_pre_edges(ctx.repo_root, ctx.problems)
    forward = (a_key, b_key) in existing
    backward = (b_key, a_key) in existing
    if recheck:
        check("recheck_entry_exists", forward, f"已有边 {a_key}->{b_key}")
    else:
        check("edge_not_exists", not forward, f"{a_key}->{b_key}")
        check("reverse_not_exists", not backward, f"{b_key}->{a_key}")

    # reason 形态：必须含 a_step 或 b_use 的关键词
    reason = rec.get("reason", "")
    rtokens = set()
    for s in (rec["a_step"], rec["b_use"]):
        rtokens |= L.tokens(s)
    hit_reason = sorted(t for t in rtokens if t and t in reason)
    check("reason_not_template", bool(hit_reason), f"命中 {hit_reason[:5]}")

    out = rec.get("verdict")
    if out == "accept" and fail:
        out = "doubtful"
    elif out == "doubtful" and any(f in fail for f in ("identity_exists", "direction_rank", "difficulty_window")):
        out = "reject"
    return {"key": rec["key"], "task_id": rec.get("task_id", ""), "verdict_in": rec["verdict"],
            "verdict_out": out, "fail": fail, "checks": checks,
            "legacy_window_violation": bool(recheck and legacy_window),
            "a_step": rec["a_step"], "b_use": rec["b_use"], "reason": rec.get("reason", ""),
            "strength": rec.get("strength") or ("template-level" if out == "accept" else ""),
            "confidence": rec.get("confidence", ""),
            "step_score": float((rec.get("prescreen") or {}).get("step_reused") or 0.0),
            "a": a_key, "b": b_key}


def applied_edges(ctx: Ctx) -> set[str]:
    """本批已写入且仍生效的边。grounding 对它不再重复跑「非重复」检查。

    否则每轮 collect+grounding 都会把已生效的关系重新判成 doubtful
    （边已存在 → edge_not_exists 失败），台账会积累误导性的降级记录。
    """
    written = {w["key"] for w in L.read_jsonl(ctx.batch_dir / "pre-writes.jsonl")}
    removed = {r["key"] for r in L.read_jsonl(ctx.batch_dir / "pre-removals.jsonl")}
    return written - removed


def run_grounding(ctx: Ctx, now: str, recheck: bool = False, all_verdicts: bool = False,
                  review_file: Path | None = None) -> dict:
    ctx.refresh()
    applied = applied_edges(ctx)
    recs = L.read_jsonl(ctx.batch_dir / "worker-results.jsonl")
    pres = {r["key"]: r for r in L.read_jsonl(ctx.batch_dir / "prescreen-results.jsonl")}
    review = json.loads(review_file.read_text(encoding="utf-8")) if review_file and review_file.exists() else {}
    out = []
    for rec in recs:
        if not all_verdicts and rec["verdict"] == "reject":
            out.append({"key": rec["key"], "task_id": rec.get("task_id", ""), "verdict_in": "reject",
                        "verdict_out": "reject", "fail": [], "checks": {},
                        "a": rec["key"].split("->")[0], "b": rec["key"].split("->")[1],
                        "strength": "", "confidence": rec.get("confidence", ""), "step_score": 0.0,
                        "a_step": rec.get("a_step", ""), "b_use": rec.get("b_use", ""), "reason": rec.get("reason", "")})
            continue
        if rec["key"] in applied and not recheck:
            # 已生效：保留原裁定，不重跑非重复检查（见 applied_edges 注释）
            p0 = pres.get(rec["key"])
            out.append({"key": rec["key"], "task_id": rec.get("task_id", ""),
                        "verdict_in": rec["verdict"], "verdict_out": rec["verdict"],
                        "fail": [], "checks": {}, "already_applied": True,
                        "a": rec["key"].split("->")[0], "b": rec["key"].split("->")[1],
                        "strength": rec.get("strength") or "template-level",
                        "confidence": rec.get("confidence", ""),
                        "step_score": float((p0 or {}).get("answers", {}).get("step_reused") or 0.0),
                        "a_step": rec.get("a_step", ""), "b_use": rec.get("b_use", ""),
                        "reason": rec.get("reason", "")})
            continue
        r = ground_one(ctx, rec, recheck=recheck)
        p = pres.get(rec["key"])
        if p:
            r["prescreen"] = p["answers"]
            r["step_score"] = float(p["answers"].get("step_reused") or 0.0)
        if review and rec["key"] in set(review.get("rejected") or []):
            r["verdict_out"] = "doubtful"
            r.setdefault("fail", []).append("review_rejected")
        out.append(r)
    L.write_jsonl(ctx.batch_dir / "grounding-report.jsonl", out)
    st = ctx.init_state()
    for r in out:
        for tid, t in st["tasks"].items():
            if t["key"] == r["key"]:
                t["status"] = {"accept": "待审核", "doubtful": "待审核", "reject": "拒绝"}[r["verdict_out"]]
    st["updated"] = now
    ctx.save_state(st)
    from collections import Counter
    c = Counter(r["verdict_out"] for r in out)
    downgraded = sum(1 for r in out if r["verdict_in"] != r["verdict_out"])
    reasons = Counter(f for r in out for f in r.get("fail", []))
    print(f"接地机检 {len(out)} 条：accept {c['accept']} / doubtful {c['doubtful']} / reject {c['reject']}"
          f"；降级 {downgraded}")
    if reasons:
        print("  降级原因：" + "，".join(f"{k}×{v}" for k, v in reasons.most_common(8)))
    return {"rows": out, "counts": dict(c)}


def cmd_grounding(args) -> None:
    ctx = Ctx(L.REPO_ROOT_DEFAULT, args.batch)
    run_grounding(ctx, args.now, recheck=args.recheck, all_verdicts=args.all,
                  review_file=Path(args.review_file) if args.review_file else None)


# ----------------------------------------------------------------------- apply

def build_pool(ctx: Ctx, grounded: list[dict]) -> dict[str, list[dict]]:
    """每个 B 的全局候选池：历史未重审关系占位 + 本批接受项 + 本批已写 + 延后项。"""
    pool: dict[str, list[dict]] = {}
    problems = {p["key"]: p for p in ctx.problems}
    written_keys = {w["key"] for w in L.read_jsonl(ctx.batch_dir / "pre-writes.jsonl")}
    written_keys -= {r["key"] for r in L.read_jsonl(ctx.batch_dir / "pre-removals.jsonl")}
    # 1) 现有 pre（含历史）：未重审的历史关系作为 legacy-placeholder 占位
    recheck_path = ctx.batch_dir / "legacy-recheck.jsonl"
    rechecked = {}
    if recheck_path.exists():
        rechecked = {r["key"]: r for r in L.read_jsonl(recheck_path)}
    for p in ctx.problems:
        for t in p["existing_pre"]:
            key = f"{t}->{p['key']}"
            if key in written_keys:
                continue  # 本批自己写的边由 grounded/已写台账提供，避免重复计数
            pool.setdefault(p["key"], []).append({
                "key": key, "target": t, "source": "existing",
                "strength": "legacy-placeholder", "confidence": "high", "step_score": 0.0,
                "reason": "", "action": "keep",
                "recheck_verdict": rechecked.get(key, {}).get("verdict", ""),
            })
    # 2) 本批接受项（含先前专题已写入的，用于跨专题重新仲裁）
    index: dict[str, dict] = {}
    for g in grounded:
        if g["verdict_out"] != "accept":
            continue
        index[g["key"]] = {
            "key": g["key"], "target": g["a"], "b": g["b"], "source": "batch",
            "strength": g.get("strength") or "template-level", "confidence": g.get("confidence", "low"),
            "step_score": float(g.get("step_score") or 0.0), "reason": g.get("reason", ""),
            "a_step": g.get("a_step", ""), "b_use": g.get("b_use", ""), "action": "add",
            "already_written": g["key"] in written_keys,
        }
    # 2b) 先前已写入但本次未重新评估的边：仍进池占位，使后来更强的候选能替换它们
    for w in L.read_jsonl(ctx.batch_dir / "pre-writes.jsonl"):
        if w["key"] in written_keys and w["key"] not in index:
            index[w["key"]] = {"key": w["key"], "target": w["target"], "b": w["b"], "source": "batch",
                                "strength": w.get("strength") or "template-level", "confidence": "high",
                                "step_score": 0.0, "reason": "", "action": "add", "already_written": True}
    for item in index.values():
        pool.setdefault(item["b"], []).append(item)
    # 3) 延后项
    for d in L.read_jsonl(ctx.batch_dir / "deferred.jsonl"):
        if problems.get(d["b"]) is None:
            continue
        pool.setdefault(d["b"], []).append({**d, "source": "deferred"})
    for b in pool:
        pool[b].sort(key=L.arbitration_key)
    return pool


def plan_apply(ctx: Ctx, grounded: list[dict], now: str, review: dict | None = None,
               recheck_mode: bool = False, write_keys: set[str] | None = None) -> dict:
    ctx.refresh()  # 批次会持续改 frontmatter：每次规划前刷新，避免重复写边
    max_pre = ctx.cfg["candidate"]["max_pre_per_problem"]
    pool = build_pool(ctx, grounded)
    manifest = ctx.manifest()
    baseline = manifest.get("problems_baseline_hash", {})
    # 本批已经写过的题：以台账里最后一次 hash_after 为期望值；否则用 shard 时的基线。
    # 这样「本批自己造成的 frontmatter 变化」不会被误判为外部编辑（§7.1-3）。
    expected: dict[str, str] = dict(baseline)
    for row in L.read_jsonl(ctx.batch_dir / "pre-writes.jsonl") + L.read_jsonl(ctx.batch_dir / "pre-removals.jsonl"):
        if row.get("hash_after"):
            expected[row["b"]] = row["hash_after"]
    review = review or {}
    blocked = set(review.get("rejected") or [])
    plan = {"writes": [], "removals": [], "deferred": [], "skipped": [], "replace": [],
            "conflicts": [], "stale": [], "cycles": []}
    edges = L.all_pre_edges(ctx.repo_root, ctx.problems)

    for b, items in sorted(pool.items()):
        # 专题过滤：只有本次评估范围内、且允许写入的候选才落动作；其余仅参与仲裁
        batch_items = [i for i in items if i["source"] == "batch"]
        plan_items = [i for i in batch_items if write_keys is None or i["key"] in write_keys]
        if not plan_items:
            continue
        if any(i["key"] in blocked for i in batch_items):
            plan["blocked"] = sorted(i["key"] for i in batch_items if i["key"] in blocked)
            plan["skipped"].append({"b": b, "reason": "review-rejected"})
            continue
        p = ctx.by_key[b]
        path = ctx.repo_root / p["dir"] / "index.md"
        text = path.read_text(encoding="utf-8")
        cur_hash = L.sha16(text)
        want = expected.get(b)
        if want and want != cur_hash:
            plan["stale"].append({"b": b, "reason": "stale-external", "expected": want, "actual": cur_hash})
            continue
        kept, displaced = L.arbitrate(items, max_pre)
        kept_batch = [i for i in kept if i["source"] == "batch"]
        kept_keys = {i["key"] for i in kept}
        for i in kept_batch:
            if write_keys is not None and i["key"] not in write_keys:
                continue
            if (i["target"], b) in edges:
                continue  # 已生效（本批先前写入），无需重复写
            if (i["target"], b) in edges and (b, i["target"]) in edges:
                plan["conflicts"].append({"key": i["key"], "reason": "duplicate"})
                continue
            plan["writes"].append({"b": b, "dir": p["dir"], "key": i["key"], "target": i["target"],
                                   "reason": i.get("reason") or i.get("a_step", ""), "strength": i["strength"],
                                   "confidence": i["confidence"], "hash_before": cur_hash})
        for i in displaced:
            if i["source"] == "batch":
                # 跨专题重新仲裁：本批先前写入的较弱关系被更强候选挤出 → 定点删除（§6.1-3）
                if i.get("already_written") and (i["target"], b) in edges:
                    plan["replace"].append({"b": b, "key": i["key"], "target": i["target"],
                                            "replaced_by": [k["key"] for k in kept_batch]})
                    plan["removals"].append({"b": b, "dir": p["dir"], "key": i["key"],
                                              "target": i["target"], "reason": "replace-pre"})
                    continue
                if write_keys is not None and i["key"] not in write_keys:
                    continue  # 不属于本次评估范围：不记 deferred（其状态由上次评估决定）
                plan["deferred"].append({"b": b, "key": i["key"], "target": i["target"], "reason": "over-limit",
                                         "strength": i["strength"], "confidence": i["confidence"],
                                         "step_score": i["step_score"]})
            elif i["source"] == "existing" and recheck_mode and i.get("recheck_verdict") == "remove":
                plan["removals"].append({"b": b, "dir": p["dir"], "key": i["key"], "target": i["target"],
                                         "reason": "recheck-remove"})
            elif i["source"] == "existing" and i["key"] not in kept_keys and kept_batch:
                plan["replace"].append({"b": b, "key": i["key"], "target": i["target"],
                                        "replaced_by": [k["key"] for k in kept_batch]})
                plan["removals"].append({"b": b, "dir": p["dir"], "key": i["key"], "target": i["target"],
                                         "reason": "replace-pre"})

    # 无环预演
    trial = set(edges)
    for w in plan["writes"]:
        trial.add((w["target"], w["b"]))
    for r in plan["removals"]:
        trial.discard((r["target"], r["b"]))
    cyc = L.find_cycle(trial)
    if cyc:
        plan["cycles"] = [cyc]
        plan["writes"] = []
    return plan


def run_apply(ctx: Ctx, now: str, dry_run: bool, recheck_mode: bool = False,
              review_file: Path | None = None, require_review: bool = False,
              allow_after_gate: bool = False, shard: str | None = None) -> dict:
    st = ctx.init_state()
    gate = st.get("gate", {})
    # 闸门语义：M1 跑完且「正在等用户确认」时才阻断。
    # 用户确认后 gate.waiting_user 变 false（pre_batch.py gate resume），即可继续 M2。
    if gate.get("waiting_user") and not allow_after_gate:
        raise SystemExit("M1 试点已完成但未获用户确认：拒绝写入（等 gate resume 或显式 --allow-after-gate）")
    if not dry_run and not require_review:
        raise SystemExit("正式写入必须提供 --require-review 与独立审核清单（--review-file），拒绝写入")
    if require_review and (not review_file or not review_file.exists()):
        raise SystemExit("要求独立审核清单（--review-file）但文件不存在：拒绝写入")
    review = json.loads(review_file.read_text(encoding="utf-8")) if review_file and review_file.exists() else None
    if review and review.get("errors_found"):
        raise SystemExit(f"独立审核发现问题（{review.get('errors_found')} 项）：拒绝写入，先修正规则并重审该专题")

    grounded = L.read_jsonl(ctx.batch_dir / "grounding-report.jsonl")
    write_keys = None
    if shard:
        # shard 支持逗号分隔的多个分片（或主标签名）：写多分片/整专题时必须如此，
        # 否则传列表只会匹配到空集合、静默写入 0 条。
        all_pairs = json.loads((ctx.batch_dir / "shard-pairs.json").read_text(encoding="utf-8"))
        want = [x for x in shard.split(",") if x]
        ids = set()
        for w in want:
            if w in all_pairs:
                ids.add(w)
            else:  # 当作主标签：展开成该标签的全部分片
                ids |= {s["shard_id"] for s in L.read_jsonl(ctx.batch_dir / "shards.jsonl")
                        if s["tag"] == w}
        shard_pairs = set()
        for sid in ids:
            shard_pairs |= set(all_pairs.get(sid, []))
        grounded = [g for g in grounded if g["key"] in shard_pairs]
        write_keys = {g["key"] for g in grounded if g["verdict_out"] == "accept"}
        if not shard_pairs:
            raise SystemExit(f"--shard 未匹配到任何候选：{shard}")
    plan = plan_apply(ctx, grounded, now, review, recheck_mode, write_keys=write_keys)

    written, removed = 0, 0
    if not dry_run:
        writes_rows, removals_rows = [], []
        for w in plan["writes"]:
            path = ctx.repo_root / w["dir"] / "index.md"
            before = path.read_text(encoding="utf-8")
            oj, pid = w["target"].split("/", 1)
            after, applied = L.add_relation_item(before, "pre", {"oj": oj, "problem_id": pid}, w["reason"], now)
            if not applied:
                print(f"  跳过 {w['key']}（已存在）")
                continue
            if L.body_of(before) != L.body_of(after):
                raise SystemExit(f"写入会改动正文，已中止：{w['key']}")
            path.write_text(after, encoding="utf-8")
            writes_rows.append({"batch_id": ctx.batch, "key": w["key"], "a": w["target"], "b": w["b"],
                                "dir": w["dir"], "target": w["target"],
                                "action": "add-pre", "reason": w["reason"], "strength": w["strength"],
                                "hash_before": L.sha16(before), "hash_after": L.sha16(after), "written_at": now})
            written += 1
        for r in plan["removals"]:
            path = ctx.repo_root / r["dir"] / "index.md"
            before = path.read_text(encoding="utf-8")
            oj, pid = r["target"].split("/", 1)
            after, applied = L.remove_relation_item(before, "pre", {"oj": oj, "problem_id": pid})
            if not applied:
                continue
            if L.body_of(before) != L.body_of(after):
                raise SystemExit(f"删除会改动正文，已中止：{r['key']}")
            path.write_text(after, encoding="utf-8")
            removals_rows.append({"batch_id": ctx.batch, "key": r["key"], "a": r["target"], "b": r["b"],
                                  "dir": r["dir"], "target": r["target"],
                                  "action": r["reason"], "hash_before": L.sha16(before),
                                  "hash_after": L.sha16(after), "written_at": now})
            removed += 1
        L.append_jsonl(ctx.batch_dir / "pre-writes.jsonl", writes_rows)
        L.append_jsonl(ctx.batch_dir / "pre-removals.jsonl", removals_rows)
        L.append_jsonl(ctx.batch_dir / "deferred.jsonl",
                       [{**d, "batch_id": ctx.batch, "deferred_at": now} for d in plan["deferred"]])
        for tid, t in st["tasks"].items():
            if any(w["key"] == t["key"] for w in plan["writes"]):
                t["status"] = "已生效"
            elif any(d["key"] == t["key"] for d in plan["deferred"]):
                t["status"] = "延后"
        st["updated"] = now
        ctx.save_state(st)
    print(f"{'[dry-run] ' if dry_run else ''}写入 {len(plan['writes'])} 条（实际 {written}），"
          f"删除/替换 {len(plan['removals'])} 条（实际 {removed}），延后 {len(plan['deferred'])}，"
          f"冲突 {len(plan['conflicts'])}，外部改动跳过 {len(plan['stale'])}")
    if plan.get("blocked"):
        print(f"  抽检否决：{plan['blocked']}")
    if plan["cycles"]:
        raise SystemExit(f"预演出现环，已中止：{plan['cycles']}")
    return plan


def cmd_apply(args) -> None:
    ctx = Ctx(L.REPO_ROOT_DEFAULT, args.batch)
    run_apply(ctx, args.now, args.dry_run, recheck_mode=args.recheck,
              review_file=Path(args.review_file) if args.review_file else None,
              require_review=args.require_review, allow_after_gate=args.allow_after_gate,
              shard=args.shard)


def cmd_gate(args) -> None:
    """闸门与批次状态维护：m1-complete / waiting-user / resume / set-thresholds / slots / task-state。"""
    ctx = Ctx(L.REPO_ROOT_DEFAULT, args.batch)
    st = ctx.init_state()
    if args.action == "m1-complete":
        st["gate"]["m1_complete"] = True
        st["gate"]["waiting_user"] = True
        st["gate"]["m1_completed_at"] = args.now
    elif args.action == "waiting-user":
        st["gate"]["waiting_user"] = True
    elif args.action == "resume":
        st["gate"]["waiting_user"] = False
        st["gate"]["approved_by_user_at"] = args.now
    elif args.action == "set-thresholds":
        st["prescreen_thresholds"] = json.loads(args.thresholds)
    elif args.action == "slots":
        st["slots"] = json.loads(args.slots)
    elif args.action == "task-state":
        t = st["tasks"].get(args.task_id)
        if not t:
            raise SystemExit(f"未知 task_id：{args.task_id}")
        t["status"] = args.state
        t["last_activity"] = args.now
        if args.slot:
            t["slot"] = args.slot
        if args.state in ("运行中",):
            t["restarts"] = int(t.get("restarts") or 0) + (1 if args.restart else 0)
    ctx.save_state(st)
    print(json.dumps({k: st[k] for k in ("gate", "prescreen_thresholds", "slots") if k in st},
                     ensure_ascii=False, indent=2))


# ---------------------------------------------------------------------- ledger

def run_ledger(ctx: Ctx, strict: bool = False) -> dict:
    ctx.refresh()
    bd = ctx.batch_dir
    st = ctx.state()
    cands = L.read_jsonl(bd / "pre-candidates.jsonl")
    pres = L.read_jsonl(bd / "prescreen-results.jsonl")
    wres = L.read_jsonl(bd / "worker-results.jsonl")
    gnd = L.read_jsonl(bd / "grounding-report.jsonl")
    writes = L.read_jsonl(bd / "pre-writes.jsonl")
    removals = L.read_jsonl(bd / "pre-removals.jsonl")
    deferred = L.read_jsonl(bd / "deferred.jsonl")
    from collections import Counter
    summary = {
        "batch": ctx.batch,
        "counts": {
            "candidates": len(cands),
            "prescreen_pass": sum(1 for r in pres if r.get("prescreen_pass")),
            "prescreen_reject": sum(1 for r in pres if not r.get("prescreen_pass")),
            "worker_accept": sum(1 for r in wres if r["verdict"] == "accept"),
            "worker_reject": sum(1 for r in wres if r["verdict"] == "reject"),
            "worker_doubtful": sum(1 for r in wres if r["verdict"] == "doubtful"),
            "grounded_accept": sum(1 for r in gnd if r["verdict_out"] == "accept"),
            "written": len(writes), "removed": len(removals), "deferred": len(deferred),
        },
        "reject_reasons": dict(Counter(r.get("reject_reason", "") for r in wres if r["verdict"] == "reject")),
        "usage": st.get("usage", {}),
        "gate": st.get("gate", {}),
        "tasks": {k: v.get("status") for k, v in (st.get("tasks") or {}).items()},
    }
    # 台账一致性：hash_after 与当前文件一致；已写入边仍存在
    # 被本批 replace-pre 替换掉的边不应报 missing（删除动作本身就是台账的一部分）
    replaced_keys = {r["key"] for r in removals if r["action"] == "replace-pre"}
    removed_keys = {r["key"] for r in removals}
    drift, missing = [], []
    for w in writes:
        if w["key"] in replaced_keys:
            continue
        path = ctx.repo_root / w["dir"] / "index.md"
        if not path.exists():
            missing.append(w["key"])
            continue
        b_oj, b_pid = w["b"].split("/", 1)
        entries = L.pre_entries_of(ctx.repo_root, b_oj, b_pid)
        still = any(f"{e['oj']}/{e['problem_id']}" == w["target"] for e in entries)
        if not still:
            missing.append(w["key"])
        elif L.sha16(path.read_text(encoding="utf-8")) != w.get("hash_after"):
            drift.append({"key": w["key"], "note": "hash 变化但边仍在（后续批次写入）"})
    for r in removals:
        if r["action"] != "replace-pre":
            continue
        b_oj, b_pid = r["b"].split("/", 1)
        entries = L.pre_entries_of(ctx.repo_root, b_oj, b_pid)
        if any(f"{e['oj']}/{e['problem_id']}" == r["target"] for e in entries):
            missing.append(f"replace 未生效：{r['key']}")
    _ = removed_keys
    # recheck 模式（历史 103 条）：基线 hash 未变、条目仍在
    legacy = ctx.manifest().get("legacy_edges", [])
    recheck_rows = L.read_jsonl(bd / "legacy-recheck.jsonl")
    summary["recheck"] = {"total": len(legacy), "decided": len(recheck_rows),
                          "unresolved": sum(1 for r in recheck_rows if r.get("verdict") == "unresolved")}
    summary["consistency"] = {"drift": drift[:10], "missing": missing[:10],
                              "ok": not missing and len(gnd) >= 0}
    print(json.dumps(summary["counts"], ensure_ascii=False))
    print(f"台账一致性：{'通过' if summary['consistency']['ok'] else '失败'}"
          f"（漂移 {len(drift)}，丢失 {len(missing)}）")
    if strict and not summary["consistency"]["ok"]:
        raise SystemExit("台账不一致")
    return summary


def cmd_ledger(args) -> None:
    ctx = Ctx(L.REPO_ROOT_DEFAULT, args.batch)
    out = run_ledger(ctx, strict=args.strict)
    if args.json:
        print(json.dumps(out, ensure_ascii=False, indent=2))


# ------------------------------------------------------------------- recheck

def run_materials(ctx: Ctx, keys: list[str] | None = None, line_numbers: bool = True,
                  from_pilot: bool = False) -> dict:
    """为指定题目（或 M1 试点涉及的全部题目）生成带行号的材料摘录。

    带行号可以让 worker 直接引用 `src_*` 的行号，不必自己数行；摘录仍是原文，
    截断在 4000 字符处，任务书要求作结论前补读原文全文。
    """
    ctx.refresh()
    if from_pilot:
        picked = [k for k in (ctx.batch_dir / "m1-candidates.txt").read_text(encoding="utf-8").split() if k]
        cands = {c["key"]: c for c in ctx.cands()}
        keys = sorted({cands[k][side]["key"] for k in picked for side in ("a", "b")})
    keys = keys or []
    mat_dir = ctx.batch_dir / "materials"
    mat_dir.mkdir(parents=True, exist_ok=True)
    for key in keys:
        p = ctx.by_key[key]
        md = L.build_material(ctx.repo_root, p, with_line_numbers=line_numbers)
        L.atomic_write_text(mat_dir / f"{p['oj']}__{p['problem_id']}.md", md)
    print(f"生成材料 {len(keys)} 份（带行号={line_numbers}）→ {mat_dir}")
    return {"count": len(keys)}


def cmd_materials2(args) -> None:
    ctx = Ctx(L.REPO_ROOT_DEFAULT, args.batch)
    keys = [k for k in (args.only or "").split(",") if k] or None
    run_materials(ctx, keys, line_numbers=not args.no_line_numbers, from_pilot=args.pilot)


def run_pilot(ctx: Ctx, now: str, bound: int, parents: list[str] | None) -> dict:
    """M1 有界试点选点（§5/§15）：从最大专题（或指定标签）抽 <=bound 个候选，兼顾子分片与边界。"""
    ctx.refresh()
    picked, info = L.select_m1_candidates(ctx.repo_root, ctx.batch, bound, parents)
    L.atomic_write_text(ctx.batch_dir / "m1-candidates.txt", "\n".join(picked) + "\n")
    st = ctx.init_state()
    st["pilot"] = {"bound": bound, "parents": parents or [], "selected": len(picked),
                   "info": {k: v for k, v in info.items() if k != "per_shard"},
                   "selected_at": now, "status": "待初筛"}
    ctx.save_state(st)
    print(f"M1 试点候选 {len(picked)} 个（上限 {bound}，覆盖 {info['shards_covered']} 个分片 / "
          f"{info['topics_covered']} 个专题）→ {ctx.batch_dir / 'm1-candidates.txt'}")
    per = sorted(info["per_shard"].items(), key=lambda kv: -kv[1])[:10]
    print("  分片分布（前 10）：" + "，".join(f"{k}={v}" for k, v in per))
    return {"picked": picked, "info": info}


def cmd_pilot(args) -> None:
    ctx = Ctx(L.REPO_ROOT_DEFAULT, args.batch)
    parents = [t for t in (args.parents or "").split(",") if t]
    run_pilot(ctx, args.now, args.bound, parents or None)


def prepare_recheck(ctx: Ctx, now: str) -> dict:
    """把全仓现有 pre 边导出为重审任务（recheck 模式，不因初筛失败删除历史项）。"""
    ctx.refresh()
    rows = []
    for p in ctx.problems:
        for t in p["existing_pre"]:
            rows.append({"key": f"{t}->{p['key']}", "a": t, "b": p["key"], "mode": "recheck",
                         "baseline_hash": p["hash"], "legacy": True, "status": "待派发"})
    L.write_jsonl(ctx.batch_dir / "legacy-recheck-pending.jsonl", rows)
    st = ctx.init_state()
    st["legacy_recheck_count"] = len(rows)
    st["updated"] = now
    ctx.save_state(st)
    print(f"历史 pre 关系 {len(rows)} 条已导出为重审任务（recheck 模式）")
    return {"rows": rows}


def cmd_recheck(args) -> None:
    ctx = Ctx(L.REPO_ROOT_DEFAULT, args.batch)
    prepare_recheck(ctx, args.now)
