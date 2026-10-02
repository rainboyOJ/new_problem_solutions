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

子命令：init / candidates / materials / calibrate / judge / decide / write
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

BATCHES_ROOT = B.BATCHES_ROOT
PROBLEMS_ROOT = B.PROBLEMS_ROOT
TIERS = {
    "入门": 0, "普及-": 1, "普及": 2, "普及/提高-": 2, "普及+/提高-": 3,
    "普及+/提高": 4, "提高": 4, "提高+/省选-": 5, "省选/NOI-": 6,
    "NOI/NOI+/CTSC": 7,
}
QUESTIONS = HERE / "questions-pre-v5.json"


def load_problems() -> list[dict]:
    out = []
    for index_md in sorted(PROBLEMS_ROOT.glob("*/*/index.md")):
        scalars, relations, _ = B.extract_frontmatter(index_md)
        tags = [t for t in re.findall(r'"([^"]+)"', scalars.get("tags", "")) if t]
        out.append({
            "dir": str(index_md.parent.relative_to(B.REPO_ROOT)),
            "oj": scalars.get("oj", ""),
            "problem_id": scalars.get("problem_id", ""),
            "title": scalars.get("title", ""),
            "difficulty": scalars.get("difficulty", ""),
            "tier": TIERS.get(scalars.get("difficulty", "")),
            "tags": tags,
            "existing_pre": [f"{r.get('oj')}/{r.get('problem_id')}" for r in relations if r["field"] == "pre"],
        })
    return out


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
    """同标签交集 + 难度差 0~2 的假设对；方向先按难度排（同难度保持目录序），由 Choice 判定。"""
    batch_dir = BATCHES_ROOT / args.batch
    manifest = json.loads((batch_dir / "pre-manifest.json").read_text(encoding="utf-8"))
    problems = [p for p in manifest["problems"] if p["tier"] is not None]
    existing = set()
    for p in problems:
        me = f"{p['oj']}/{p['problem_id']}"
        for t in p["existing_pre"]:
            existing.add((t, me)); existing.add((me, t))
    counts = Counter(f"{p['oj']}/{p['problem_id']}" for p in problems)
    for p in problems:
        counts[f"{p['oj']}/{p['problem_id']}"] = len(p["existing_pre"])

    cands, skipped = [], []
    order = sorted(problems, key=lambda p: (p["tier"], p["oj"], p["problem_id"]))
    for i in range(len(order)):
        for j in range(i + 1, len(order)):
            a, b = order[i], order[j]
            delta = abs(a["tier"] - b["tier"])
            if delta < args.min_delta or delta > args.max_delta:
                continue
            if not (set(a["tags"]) & set(b["tags"])):
                continue
            ka, kb = f"{a['oj']}/{a['problem_id']}", f"{b['oj']}/{b['problem_id']}"
            if (ka, kb) in existing:
                skipped.append({"a": ka, "b": kb, "reason": "已存在 pre 关系"}); continue
            if counts[kb] >= args.max_pre:
                skipped.append({"a": ka, "b": kb, "reason": f"目标题 pre 已达上限 {args.max_pre}"}); continue
            counts[kb] += 1
            cands.append({
                "a": {k: a[k] for k in ("oj", "problem_id", "dir", "tier", "difficulty", "title")},
                "b": {k: b[k] for k in ("oj", "problem_id", "dir", "tier", "difficulty", "title")},
                "delta": delta, "status": "pending",
            })
    (batch_dir / "pre-candidates.jsonl").write_text("\n".join(json.dumps(c, ensure_ascii=False) for c in cands) + "\n", encoding="utf-8")
    (batch_dir / "pre-candidates-excluded.jsonl").write_text("\n".join(json.dumps(c, ensure_ascii=False) for c in skipped) + "\n", encoding="utf-8")
    print(f"候选 {len(cands)} 对（难度差 {args.min_delta}~{args.max_delta}，标签交集，每题 pre 上限 {args.max_pre}）；排除 {len(skipped)}")
    print("难度差分布:", dict(Counter(c["delta"] for c in cands)))


def pair_key(c: dict) -> str:
    return f"{c['a']['oj']}/{c['a']['problem_id']}->{c['b']['oj']}/{c['b']['problem_id']}"


def _answers(ans: dict) -> dict:
    return {
        "A_is_step_to_B": ans["A_is_step_to_B"].get("noul"),
        "B_harder_than_A": ans["B_harder_than_A"].get("noul"),
        "same_core_model": ans["same_core_model"].get("noul"),
    }


def cmd_materials(args: argparse.Namespace) -> None:
    batch_dir = BATCHES_ROOT / args.batch
    manifest = json.loads((batch_dir / "pre-manifest.json").read_text(encoding="utf-8"))
    mat_dir = batch_dir / "materials"
    mat_dir.mkdir(parents=True, exist_ok=True)
    n = 0
    for p in manifest["problems"]:
        problem_dir = B.REPO_ROOT / p["dir"]
        _, _, body = B.extract_frontmatter(problem_dir / "index.md")
        analysis = ""
        for pat in (r"^##\s*题目解析.*?(?=^##\s|\Z)",
                    r"^###?\s*(?:题意|思路).*?(?=^#{2,3}\s*(?:Python 知识|代码|复杂度|总结|一图流)|\Z)",
                    B.ANALYSIS_HEADING + rf".*?(?={B.STOP_HEADING}|\Z)"):
            m = re.search(pat, body, re.M | re.S)
            if m and len(m.group(0).strip()) >= 300:
                analysis = m.group(0).strip()[:4000]
                break
        if not analysis:
            analysis = body.strip()[:2000]
        code = sorted(f.name for f in problem_dir.iterdir() if f.is_file() and f.suffix in {".cpp", ".py"})
        lines = [f"# {p['oj']} {p['problem_id']} {p['title']}", "",
                 f"> 原文摘录，非模型摘要。来源：`{p['dir']}/index.md`。", "",
                 "## 元信息（frontmatter 摘录）", f"- 难度：{p['difficulty'] or '—'}；标签：{p['tags']}", "",
                 "## 题目解析（原文摘录）", "", analysis, "", "## 代码位置"]
        lines += [f"- `{p['dir']}/{c}`" for c in code] or ["- （无）"]
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
    ap = argparse.ArgumentParser(description="前置关系(pre)批量补全管线")
    sub = ap.add_subparsers(dest="cmd", required=True)
    p = sub.add_parser("init"); p.add_argument("--batch", required=True); p.add_argument("--tag", required=True); p.set_defaults(func=cmd_init)
    p = sub.add_parser("candidates"); p.add_argument("--batch", required=True)
    p.add_argument("--min-delta", type=int, default=0); p.add_argument("--max-delta", type=int, default=2)
    p.add_argument("--max-pre", type=int, default=3); p.set_defaults(func=cmd_candidates)
    p = sub.add_parser("materials"); p.add_argument("--batch", required=True); p.set_defaults(func=cmd_materials)
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
    args = ap.parse_args()
    args.func(args)


if __name__ == "__main__":
    main()
