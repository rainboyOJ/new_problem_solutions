#!/usr/bin/env python3
"""题目关系批量补充（common）批处理工具。

实现 docs/plans/jev-problem-similarity-batch.md 的第 1/3/4 步基础设施：
- init:      专题候选清单与基线（题目身份、内容哈希、已有关系、完整性筛查）
- pairs:     生成并去重无序候选题对（排除自身、重复题对、已有相似关系）
- materials: 为入选题目生成判断材料摘录（原文+位置，非模型摘要）
- calibrate: 用人工标注题对跑 Jev 校准，输出阈值建议（误连/漏连计数）
- report:    批次状态汇总

批次记录目录: relation-batches/<batch-id>/
    manifest.json            批次基线（含 git 状态、题目身份、哈希、筛查结论）
    problems.md              人类可读清单（含待人工确认项）
    pairs.jsonl              待判断题对
    pairs-excluded.jsonl     排除题对及原因
    materials/<oj>__<pid>.md 判断材料摘录
    calibration.json         人工标注校准题对
    calibration-results.jsonl / raw/*.json  校准结果与原始 Jev 返回
"""

from __future__ import annotations

import argparse
import hashlib
import json
import re
import subprocess
import sys
from pathlib import Path

HERE = Path(__file__).resolve().parent
REPO_ROOT = HERE.parents[2]
PROBLEMS_ROOT = REPO_ROOT / "problems"
BATCHES_ROOT = REPO_ROOT / "relation-batches"

sys.path.insert(0, str(HERE))
import jev_client  # noqa: E402


# ---------------------------------------------------------------- frontmatter

def extract_frontmatter(index_md: Path) -> tuple[dict[str, str], list[dict[str, str]], str]:
    """返回 (顶层标量字段, 关系项列表, 正文)。

    关系项形如 {field, oj, problem_id, reason}，跟随本仓库 frontmatter 实际格式解析。
    """
    text = index_md.read_text(encoding="utf-8")
    if not text.startswith("---\n"):
        return {}, [], text
    end = text.find("\n---", 4)
    if end == -1:
        return {}, [], text
    raw_lines = text[4:end].splitlines()
    body = text[end + 4:]
    scalars: dict[str, str] = {}
    relations: list[dict[str, str]] = []
    cur_field = None
    cur_item: dict[str, str] | None = None

    def flush():
        nonlocal cur_item
        if cur_item is not None:
            relations.append(cur_item)
            cur_item = None

    for line in raw_lines:
        m_item = re.match(r'^\s+-\s+(\w+):\s*(.*)$', line)
        if m_item and cur_field in ("pre", "common", "recommend"):
            flush()
            cur_item = {"field": cur_field}
            key, val = m_item.group(1), strip_quotes(m_item.group(2))
            cur_item[key] = val
            continue
        m_cont = re.match(r'^\s+(\w+):\s*(.*)$', line)
        if m_cont and cur_item is not None:
            cur_item[m_cont.group(1)] = strip_quotes(m_cont.group(2))
            continue
        m_kv = re.match(r'^(\w+):\s*(.*)$', line)
        if m_kv:
            flush()
            key, val = m_kv.group(1), m_kv.group(2)
            cur_field = key
            if val.strip() not in ("", "[]"):
                scalars[key] = strip_quotes(val)
            continue
    flush()
    return scalars, relations, body


def strip_quotes(value: str) -> str:
    value = value.strip()
    if len(value) >= 2 and value[0] == value[-1] and value[0] in {"'", '"'}:
        return value[1:-1]
    return value


# -------------------------------------------------------------------- helpers

def problem_identity(problem_dir: Path) -> dict[str, str]:
    """题目身份以 frontmatter 的 oj / problem_id 为准，目录名只做对照。"""
    index_md = problem_dir / "index.md"
    scalars, _, _ = extract_frontmatter(index_md)
    return {
        "dir": str(problem_dir.relative_to(REPO_ROOT)),
        "oj": scalars.get("oj", ""),
        "problem_id": scalars.get("problem_id", ""),
        "title": scalars.get("title", ""),
        "dir_oj": problem_dir.parent.name,
        "dir_problem_id": problem_dir.name,
    }


def content_hash(problem_dir: Path) -> str:
    """index.md + 目录下代码文件的内容哈希，作为批次基线的内容版本。"""
    h = hashlib.sha256()
    files = sorted([p for p in problem_dir.iterdir() if p.is_file() and p.suffix in {".md", ".cpp", ".py", ".txt"}])
    for p in files:
        h.update(p.name.encode("utf-8"))
        h.update(p.read_bytes())
    return h.hexdigest()[:16]


def git_state() -> dict[str, str]:
    def run(*args: str) -> str:
        out = subprocess.run(["git", *args], cwd=REPO_ROOT, capture_output=True, text=True)
        return out.stdout.strip()

    dirty = run("status", "--porcelain")
    return {
        "head": run("rev-parse", "HEAD"),
        "branch": run("rev-parse", "--abbrev-ref", "HEAD"),
        "dirty_files": str(len([l for l in dirty.splitlines() if l.strip()])),
    }


def normalize_pid(problem_id: str) -> str:
    """归一化题号用于跨 OJ 重复题检测，例如 912E 与 cf912e。"""
    s = re.sub(r"[^a-z0-9]", "", problem_id.lower())
    for prefix in ("cf", "luogu", "poj", "hdup"):
        if s.startswith(prefix) and len(s) > len(prefix) + 1:
            s2 = s[len(prefix):]
            if s2 and s2[0].isdigit():
                return s2
    return s


ANALYSIS_HEADING = r"^#{2,3}\s+.*(?:题目解析|解题思路|思路|题意|核心|推导|解题|算法设计|解法)"
STOP_HEADING = r"^#{2,3}\s+.*(?:代码|Python|复杂度|总结|一图流|暴力)"


# ----------------------------------------------------------------------- init

def cmd_init(args: argparse.Namespace) -> None:
    batch_dir = BATCHES_ROOT / args.batch
    if batch_dir.exists() and not args.force:
        sys.exit(f"批次目录已存在: {batch_dir}（用 --force 覆盖 manifest）")

    entries = []
    for index_md in sorted(PROBLEMS_ROOT.glob("*/*/index.md")):
        problem_dir = index_md.parent
        scalars, relations, body = extract_frontmatter(index_md)
        if args.keyword not in index_md.read_text(encoding="utf-8"):
            continue  # 专题关键词检索覆盖全文（正文 + frontmatter 标签/描述），复现方案文档的候选口径
        code_files = sorted(p.name for p in problem_dir.iterdir() if p.is_file() and p.suffix in {".cpp", ".py"})
        # 题解有多套章节布局：「## 题目解析」型 /「### 题意 / ### 思路」型 /「## 解题思路、## 1. 核心推导」等自拟型
        has_analysis = bool(re.search(ANALYSIS_HEADING, body, re.M))
        analysis_len = len(body.strip())
        reasons, notes = [], []
        if not scalars.get("oj") or not scalars.get("problem_id"):
            reasons.append("frontmatter 缺少 oj/problem_id")
        if not has_analysis:
            reasons.append("正文缺少题目解析章节（题目解析/思路/题意）")
        elif analysis_len < 300:
            reasons.append("正文内容过短，材料不足")
        if not code_files:
            reasons.append("目录下没有代码文件")
        ident = problem_identity(problem_dir)
        if ident["dir_oj"].lower() != ident["oj"].lower() or ident["dir_problem_id"].lower() != ident["problem_id"].lower():
            reasons.append(f"目录名与 frontmatter 身份不一致（目录 {ident['dir_oj']}/{ident['dir_problem_id']}，frontmatter {ident['oj']}/{ident['problem_id']}）")
        elif ident["dir_oj"] != ident["oj"] or ident["dir_problem_id"] != ident["problem_id"]:
            notes.append(f"目录名与 frontmatter 大小写不同（以 frontmatter 为准）")
        entries.append({
            **ident,
            "content_hash": content_hash(problem_dir),
            "code_files": code_files,
            "tags": scalars.get("tags", ""),
            "difficulty": scalars.get("difficulty", ""),
            "existing_relations": [
                {"field": r["field"], "oj": r.get("oj", ""), "problem_id": r.get("problem_id", "")}
                for r in relations
            ],
            "screening": {
                "status": "included" if not reasons else "needs_review",
                "reasons": reasons,
                "notes": notes,
                "topic_check": "待人工确认实际解法属于本专题（关键词命中≠入选）",
            },
        })

    # 跨 OJ 重复题检测（同一题号归一化命中）
    by_norm: dict[str, list[str]] = {}
    for e in entries:
        by_norm.setdefault(normalize_pid(e["problem_id"]), []).append(e["dir"])
    duplicates = {k: v for k, v in by_norm.items() if len(v) > 1}
    for e in entries:
        norm = normalize_pid(e["problem_id"])
        if norm in duplicates:
            e["screening"]["duplicate_group"] = duplicates[norm]

    manifest = {
        "batch_id": args.batch,
        "topic": args.topic,
        "keyword": args.keyword,
        "plan": "docs/plans/jev-problem-similarity-batch.md",
        "jev": {"endpoint": jev_client.DEFAULT_ENDPOINT, "model": jev_client.DEFAULT_MODEL},
        "question_template": "scripts/problem-analysis-tools/relation_batch/questions-common-v1.json",
        "git": git_state(),
        "problems": entries,
    }
    batch_dir.mkdir(parents=True, exist_ok=True)
    (batch_dir / "manifest.json").write_text(json.dumps(manifest, ensure_ascii=False, indent=2), encoding="utf-8")
    write_problems_md(batch_dir, manifest)
    n_in = sum(1 for e in entries if e["screening"]["status"] == "included")
    print(f"批次 {args.batch}: 候选 {len(entries)} 题，入选 {n_in} 题，待复核 {len(entries) - n_in} 题")
    print(f"清单: {batch_dir / 'manifest.json'} / {batch_dir / 'problems.md'}")
    if duplicates:
        print("疑似重复题组（生成题对时将排除组内配对）:")
        for k, v in duplicates.items():
            print(f"  {k}: {', '.join(v)}")


def write_problems_md(batch_dir: Path, manifest: dict) -> None:
    lines = [
        f"# 批次 {manifest['batch_id']} 题目清单",
        "",
        f"- 专题：{manifest['topic']}（关键词：`{manifest['keyword']}`）",
        f"- git：`{manifest['git']['branch']}` @ `{manifest['git']['head'][:10]}`（未提交改动 {manifest['git']['dirty_files']} 个文件）",
        f"- 问题模板：`{manifest['question_template']}`",
        "",
        "筛查规则：关键词命中只是候选；正式写入前必须逐题人工确认内容完整性、实际解法与所属专题",
        "（`topic_check` 列）。材料不足或互相矛盾的题目不参与自动写入。",
        "",
        "| 题目 | 标题 | 难度 | 状态 | 已有关系 | 待确认/排除原因 |",
        "| --- | --- | --- | --- | --- | --- |",
    ]
    for e in manifest["problems"]:
        rels = "; ".join(f"{r['field']}→{r['oj']}/{r['problem_id']}" for r in e["existing_relations"]) or "—"
        screen = e["screening"]
        status = screen["status"]
        if screen.get("duplicate_group"):
            status += "（重复题组）"
        reasons = "；".join(screen["reasons"]) or screen["topic_check"]
        lines.append(
            f"| {e['oj']}/{e['problem_id']} | {e['title']} | {e['difficulty'] or '—'} "
            f"| {status} | {rels} | {reasons} |"
        )
    (batch_dir / "problems.md").write_text("\n".join(lines) + "\n", encoding="utf-8")


# ---------------------------------------------------------------------- pairs

def load_excludes(batch_dir: Path) -> dict[str, str]:
    """人工排除清单 excludes.json: [{dir, reason}]。关键词命中≠入选，人工审查可否决。"""
    p = batch_dir / "excludes.json"
    if not p.exists():
        return {}
    data = json.loads(p.read_text(encoding="utf-8"))
    return {item["dir"]: item["reason"] for item in data}


def cmd_pairs(args: argparse.Namespace) -> None:
    batch_dir = BATCHES_ROOT / args.batch
    manifest = json.loads((batch_dir / "manifest.json").read_text(encoding="utf-8"))
    excludes = load_excludes(batch_dir)
    included = [e for e in manifest["problems"]
                if e["screening"]["status"] == "included" and e["dir"] not in excludes]
    pairs, excluded = [], []

    # 已有 common 关系的题对（任一侧）不再生成候选
    existing_common = set()
    for e in manifest["problems"]:
        for r in e["existing_relations"]:
            if r["field"] == "common":
                key = tuple(sorted([f"{e['oj']}/{e['problem_id']}", f"{r['oj']}/{r['problem_id']}"]))
                existing_common.add(key)

    for i in range(len(included)):
        for j in range(i + 1, len(included)):
            a, b = included[i], included[j]
            ka = f"{a['oj']}/{a['problem_id']}"
            kb = f"{b['oj']}/{b['problem_id']}"
            pair = {"a": {"oj": a["oj"], "problem_id": a["problem_id"], "dir": a["dir"], "hash": a["content_hash"]},
                    "b": {"oj": b["oj"], "problem_id": b["problem_id"], "dir": b["dir"], "hash": b["content_hash"]}}
            key = tuple(sorted([ka, kb]))
            norm_a, norm_b = normalize_pid(a["problem_id"]), normalize_pid(b["problem_id"])
            if norm_a == norm_b:
                excluded.append({**pair, "reason": "疑似同一题目（题号归一化相同），不作为相似关系候选"})
            elif key in existing_common:
                excluded.append({**pair, "reason": "已存在 common 关系，只新增不重复"})
            else:
                pairs.append({**pair, "status": "pending"})

    (batch_dir / "pairs.jsonl").write_text(
        "\n".join(json.dumps(p, ensure_ascii=False) for p in pairs) + "\n", encoding="utf-8")
    (batch_dir / "pairs-excluded.jsonl").write_text(
        "\n".join(json.dumps(p, ensure_ascii=False) for p in excluded) + "\n", encoding="utf-8")
    n_in = len(included)
    print(f"入选 {n_in} 题 → 无序题对 {n_in * (n_in - 1) // 2} 个：待判断 {len(pairs)}，排除 {len(excluded)}")
    for p in excluded:
        print(f"  排除 {p['a']['oj']}/{p['a']['problem_id']} ~ {p['b']['oj']}/{p['b']['problem_id']}: {p['reason']}")


# ------------------------------------------------------------------ materials

def cmd_materials(args: argparse.Namespace) -> None:
    """生成判断材料摘录：frontmatter 身份 + 题目解析原文（含行号）+ 代码位置。

    全部为原文摘录并标注来源位置，不是模型摘要，不引入新事实。
    """
    batch_dir = BATCHES_ROOT / args.batch
    manifest = json.loads((batch_dir / "manifest.json").read_text(encoding="utf-8"))
    mat_dir = batch_dir / "materials"
    mat_dir.mkdir(parents=True, exist_ok=True)
    entries = [e for e in manifest["problems"]
               if e["screening"]["status"] == "included" and e["dir"] not in load_excludes(batch_dir)]
    if args.only:
        want = set(args.only)
        entries = [e for e in entries if f"{e['oj']}/{e['problem_id']}" in want]
    for e in entries:
        problem_dir = REPO_ROOT / e["dir"]
        index_md = problem_dir / "index.md"
        scalars, _, body = extract_frontmatter(index_md)
        candidates = [
            r"^##\s*题目解析.*?(?=^##\s|\Z)",
            # 「### 题意 / ### 思路」型布局：截到代码/知识点章节为止
            r"^###?\s*(?:题意|思路).*?(?=^#{2,3}\s*(?:Python 知识|代码|复杂度|总结|一图流)|\Z)",
            # 自拟型布局（## 解题思路 / ## 1. 核心推导 等）：从首个解析类标题截到代码/总结章节
            ANALYSIS_HEADING + rf".*?(?={STOP_HEADING}|\Z)",
        ]
        # 取第一个足够长的匹配，避免「## 题目解析」后紧接子章节时截空
        analysis = ""
        for pat in candidates:
            m = re.search(pat, body, re.M | re.S)
            if m and len(m.group(0).strip()) >= 300:
                analysis = m.group(0).strip()[:4000]
                break
        if not analysis:
            analysis = body.strip()[:2000]
        lines = [
            f"# {e['oj']} {e['problem_id']} {e['title']}",
            "",
            f"> 原文摘录，非模型摘要。来源：`{e['dir']}/index.md`（内容哈希 {e['content_hash']}）。",
            "",
            "## 元信息（frontmatter 摘录）",
            f"- 难度：{e['difficulty'] or '—'}；标签：{e['tags'] or '—'}",
            "",
            "## 题目解析（原文摘录）",
            "",
            analysis,
            "",
            "## 代码位置",
        ]
        lines += [f"- `{e['dir']}/{c}`" for c in e["code_files"]] or ["- （无）"]
        (mat_dir / f"{e['oj']}__{e['problem_id']}.md".replace("/", "_")).write_text(
            "\n".join(lines) + "\n", encoding="utf-8")
    print(f"生成材料 {len(entries)} 份 → {mat_dir}")


# ------------------------------------------------------------------ calibrate

def cmd_calibrate(args: argparse.Namespace) -> None:
    """用人工标注题对跑 Jev 校准：保存原始返回，并网格搜索合并阈值的误连/漏连。"""
    batch_dir = BATCHES_ROOT / args.batch
    spec = json.loads((batch_dir / "calibration.json").read_text(encoding="utf-8"))
    template = json.loads((HERE / "questions-common-v1.json").read_text(encoding="utf-8"))
    questions = template["questions"]
    raw_dir = batch_dir / "raw"
    results = []

    for pair in spec["pairs"]:
        print(f"校准题对 {pair['id']} ({pair['a']} ~ {pair['b']}) ...", flush=True)
        state = pair.get("state") or {
            "problem_A": (batch_dir / "materials" / f"{pair['a']}.md".replace("/", "__")).read_text(encoding="utf-8")[:6000],
            "problem_B": (batch_dir / "materials" / f"{pair['b']}.md".replace("/", "__")).read_text(encoding="utf-8")[:6000],
        }
        resp = jev_client.ask(state, questions, raw_dir=raw_dir, tag=f"calib-{pair['id']}")
        answers = {k: v.get("noul") for k, v in resp["answers"].items()}
        results.append({
            "pair_id": pair["id"],
            "a": pair["a"],
            "b": pair["b"],
            "expected": pair["expected"],
            "note": pair.get("note", ""),
            "answers": answers,
            "usage": resp.get("usage", {}),
        })
        print(f"  expected={pair['expected']} answers={answers}")

    out = batch_dir / "calibration-results.jsonl"
    out.write_text("\n".join(json.dumps(r, ensure_ascii=False) for r in results) + "\n", encoding="utf-8")

    # 阈值网格：写入规则 shared_core >= t1 且 check_similar >= t2 且 only_label <= t3
    print("\n阈值网格（行=误连数，列=漏连数；✅=二者均为 0）")
    print(f"{'t1':>4} {'t2':>4} {'t3':>4}  误连  漏连")
    best = None
    for t1 in (0.5, 0.6, 0.7, 0.8, 0.9):
        for t2 in (0.3, 0.5, 0.7):
            for t3 in (0.2, 0.3, 0.4):
                fp = fn = 0
                for r in results:
                    a = r["answers"]
                    pred = a["shared_core"] >= t1 and a["check_similar"] >= t2 and a["only_label"] <= t3
                    exp = r["expected"] == "common"
                    if pred and not exp:
                        fp += 1
                    if exp and not pred:
                        fn += 1
                mark = " ✅" if fp == 0 and fn == 0 else ""
                # 方案取舍：优先减少错连；零误连零漏连时选更严格的阈值（t1/t2 大、t3 小）
                if fp == 0 and fn == 0:
                    score = (t1, t2, -t3)
                    if best is None or score > best[0]:
                        best = (score, (t1, t2, t3), (fp, fn))
                if mark or (fp == 0):
                    print(f"{t1:>4} {t2:>4} {t3:>4}  {fp:>4}  {fn:>4}{mark}")
    if best:
        _, th, (fp, fn) = best
        print(f"\n建议阈值（零误连零漏连中取最严）: shared_core >= {th[0]} 且 check_similar >= {th[1]} 且 only_label <= {th[2]}"
              f"（误连 {fp} / 漏连 {fn}）")
    else:
        print("\n没有零误连零漏连的阈值组合，需检查标注与问题模板，不扩大批量。")
    print(f"结果已保存: {out}")
    print("注意：阈值只是本批标注集上的观察，不等于模型整体正确率；写入前仍需按方案抽查。")


# ----------------------------------------------------------------------- judge

def pair_key(p: dict) -> str:
    return f"{p['a']['oj']}/{p['a']['problem_id']}~{p['b']['oj']}/{p['b']['problem_id']}"


def load_materials(batch_dir: Path, side: dict) -> str:
    path = batch_dir / "materials" / f"{side['oj']}__{side['problem_id']}.md"
    return path.read_text(encoding="utf-8")[:4000] if path.exists() else "(材料缺失)"


def cmd_judge(args: argparse.Namespace) -> None:
    """对全部候选题对跑 Jev 判断（并行、断点续跑、原始返回落盘）。"""
    import threading
    from concurrent.futures import ThreadPoolExecutor

    batch_dir = BATCHES_ROOT / args.batch
    template = json.loads((HERE / "questions-common-v1.json").read_text(encoding="utf-8"))
    questions = template["questions"]
    pairs = [json.loads(l) for l in (batch_dir / "pairs.jsonl").read_text(encoding="utf-8").splitlines() if l.strip()]
    results_path = batch_dir / "judge-results.jsonl"
    done = set()
    if results_path.exists():
        for line in results_path.read_text(encoding="utf-8").splitlines():
            if line.strip():
                done.add(json.loads(line)["key"])
    todo = [(i, p) for i, p in enumerate(pairs) if pair_key(p) not in done]
    print(f"题对 {len(pairs)} 个：已完成 {len(done)}，本次判断 {len(todo)}（workers={args.workers}）")

    lock = threading.Lock()
    n_ok = [0]

    def work(item):
        idx, p = item
        state = {
            "problem_A": load_materials(batch_dir, p["a"]),
            "problem_B": load_materials(batch_dir, p["b"]),
        }
        try:
            resp = jev_client.ask(state, questions, raw_dir=batch_dir / "raw", tag=f"judge-{idx:04d}")
        except Exception as e:  # 单对失败不拖垮整批：记录后重跑 judge 时自动重试
            with lock:
                with (batch_dir / "judge-failures.jsonl").open("a", encoding="utf-8") as f:
                    f.write(json.dumps({"idx": idx, "key": pair_key(p), "error": str(e)[:200]}, ensure_ascii=False) + "\n")
            print(f"  失败 {pair_key(p)}: {str(e)[:80]}", flush=True)
            return None
        row = {
            "idx": idx,
            "key": pair_key(p),
            "a": f"{p['a']['oj']}/{p['a']['problem_id']}",
            "b": f"{p['b']['oj']}/{p['b']['problem_id']}",
            "model": jev_client.DEFAULT_MODEL,
            "answers": {k: v.get("noul") for k, v in resp["answers"].items()},
            "usage": resp.get("usage", {}),
        }
        with lock:
            with results_path.open("a", encoding="utf-8") as f:
                f.write(json.dumps(row, ensure_ascii=False) + "\n")
            n_ok[0] += 1
            if n_ok[0] % 50 == 0:
                print(f"  进度 {n_ok[0]}/{len(todo)}", flush=True)
        return row

    with ThreadPoolExecutor(max_workers=args.workers) as ex:
        list(ex.map(work, todo))
    print(f"判断完成：累计 {len(done) + n_ok[0]} 条 → {results_path}")


def cmd_decide(args: argparse.Namespace) -> None:
    """按合并规则把判断结果分为 write / hold / reject。"""
    batch_dir = BATCHES_ROOT / args.batch
    t1, t2, t3, margin = args.t1, args.t2, args.t3, args.margin
    rows = [json.loads(l) for l in (batch_dir / "judge-results.jsonl").read_text(encoding="utf-8").splitlines() if l.strip()]
    decisions = []
    for r in rows:
        a = r["answers"]
        near = any(abs(a[k] - th) < margin for k, th in (("shared_core", t1), ("check_similar", t2), ("only_label", t3)))
        passed = a["shared_core"] >= t1 and a["check_similar"] >= t2 and a["only_label"] <= t3
        decision = "reject" if not passed else ("hold" if near else "write")
        decisions.append({**r, "decision": decision, "near_boundary": near})
    out = batch_dir / "decisions.jsonl"
    out.write_text("\n".join(json.dumps(d, ensure_ascii=False) for d in decisions) + "\n", encoding="utf-8")
    from collections import Counter
    c = Counter(d["decision"] for d in decisions)
    print(f"规则：shared_core >= {t1} 且 check_similar >= {t2} 且 only_label <= {t3}（边界带宽 {margin}）")
    print(f"共 {len(decisions)} 对：write {c['write']} / hold {c['hold']} / reject {c['reject']}")
    print(f"→ {out}")


# ----------------------------------------------------------------------- write

def _item_block(target: dict, reason: str, indent: str = "  ") -> list[str]:
    return [
        f"{indent}- oj: \"{target['oj']}\"",
        f"{indent}  problem_id: \"{target['problem_id']}\"",
        f"{indent}  reason: \"{reason}\"",
    ]


def add_common_item(text: str, target: dict, reason: str, now: str) -> tuple[str, bool]:
    """在 frontmatter 的 common 列表追加一项（文本级编辑，其余内容原样保留）。

    返回 (新文本, 是否实际写入)。已存在相同目标或自引用时不写入。
    """
    if not text.startswith("---\n"):
        raise ValueError("缺少 frontmatter")
    end = text.find("\n---", 4)
    if end == -1:
        raise ValueError("frontmatter 未闭合")
    fm_lines = text[4:end].splitlines()
    body = text[end:]  # 以 \n--- 开头，原样拼接
    # 精确去重：查找 common 块内相同 oj + problem_id
    in_common = False
    cur: dict[str, str] = {}
    for l in fm_lines + ["\n"]:
        top = re.match(r"^(\w+):", l)
        if top:
            if in_common and cur.get("oj") == target["oj"] and cur.get("problem_id") == target["problem_id"]:
                return text, False
            in_common = top.group(1) == "common"
            cur = {}
            continue
        m = re.match(r"^\s+-?\s*(oj|problem_id):\s*\"?([^\"\n]+)\"?", l)
        if in_common and m:
            if m.group(1) == "oj":
                cur = {"oj": m.group(2).strip()}
            else:
                cur["problem_id"] = m.group(2).strip()
    if in_common and cur.get("oj") == target["oj"] and cur.get("problem_id") == target["problem_id"]:
        return text, False

    item = _item_block(target, reason)
    out: list[str] = []
    i = 0
    inserted = False
    while i < len(fm_lines):
        l = fm_lines[i]
        m = re.match(r"^(\w+):\s*(.*)$", l)
        if m and m.group(1) == "common":
            # 收集已有列表项（`  - ` 开始，`    ` 为续行），重建整个 common 块
            j = i + 1
            items: list[str] = []
            while j < len(fm_lines):
                cur_line = fm_lines[j]
                if cur_line.startswith("  - ") or (items and cur_line.startswith("    ")):
                    items.append(cur_line)
                    j += 1
                else:
                    break
            out.append("common:")
            out.extend(item)
            out.extend(items)
            i = j
            inserted = True
            continue
        out.append(l)
        i += 1

    if not inserted:
        # 没有 common 字段：插到 source: 之前（格式规范：pre、common 在 categories 后、source 前）
        block = ["common:"] + item
        pos = next((k for k, l in enumerate(out) if re.match(r"^source:\s*", l)), len(out))
        out[pos:pos] = block

    # 同步 updated
    for k, l in enumerate(out):
        if re.match(r"^updated:\s*", l):
            out[k] = f"updated: {now}"
            break
    return "---\n" + "\n".join(out) + body, True


def cmd_write(args: argparse.Namespace) -> None:
    """把 reasons.jsonl 中的关系写入两题 frontmatter（双侧互写，渲染层已去重）。"""
    import hashlib
    batch_dir = BATCHES_ROOT / args.batch
    rows = [json.loads(l) for l in (batch_dir / "reasons.jsonl").read_text(encoding="utf-8").splitlines() if l.strip()]
    now = args.now
    writes_path = batch_dir / "writes.jsonl"
    manifest = json.loads((batch_dir / "manifest.json").read_text(encoding="utf-8"))
    dir_of = {f"{e['oj']}/{e['problem_id']}": e["dir"] for e in manifest["problems"]}
    n_applied = 0
    with writes_path.open("a", encoding="utf-8") as wf:
        for r in rows:
            for me_key, other_key in ((r["a"], r["b"]), (r["b"], r["a"])):
                if args.dry_run:
                    print(f"[dry-run] {me_key} ← common {other_key}")
                    continue
                me_dir = dir_of[me_key]
                oj, pid = other_key.split("/", 1)
                path = REPO_ROOT / me_dir / "index.md"
                before = path.read_text(encoding="utf-8")
                h_before = hashlib.sha256(before.encode("utf-8")).hexdigest()[:16]
                after, applied = add_common_item(before, {"oj": oj, "problem_id": pid}, r["reason"], now)
                if not applied:
                    print(f"  跳过 {me_key} ← {other_key}（已存在）")
                    continue
                path.write_text(after, encoding="utf-8")
                h_after = hashlib.sha256(after.encode("utf-8")).hexdigest()[:16]
                wf.write(json.dumps({
                    "batch_id": batch_dir.name, "key": r["key"], "dir": me_dir,
                    "target": other_key, "action": "add-common", "reason": r["reason"],
                    "hash_before": h_before, "hash_after": h_after, "written_at": now,
                }, ensure_ascii=False) + "\n")
                n_applied += 1
    print(f"{'[dry-run] ' if args.dry_run else ''}写入完成：{n_applied} 处 frontmatter 变更 → {writes_path}")


# --------------------------------------------------------------------- report

def cmd_report(args: argparse.Namespace) -> None:
    batch_dir = BATCHES_ROOT / args.batch
    manifest = json.loads((batch_dir / "manifest.json").read_text(encoding="utf-8"))
    n_all = len(manifest["problems"])
    n_in = sum(1 for e in manifest["problems"] if e["screening"]["status"] == "included")
    excludes = load_excludes(batch_dir)
    n_ex = sum(1 for e in manifest["problems"] if e["dir"] in excludes)
    print(f"批次 {manifest['batch_id']}（{manifest['topic']}）")
    print(f"  git: {manifest['git']['branch']} @ {manifest['git']['head'][:10]}")
    print(f"  候选 {n_all} 题 / 自动入选 {n_in} 题 / 人工否决 {n_ex} 题 / 实际参与 {n_in - n_ex} 题 / 待复核 {n_all - n_in} 题")
    for name in ("pairs.jsonl", "pairs-excluded.jsonl", "calibration.json", "calibration-results.jsonl"):
        p = batch_dir / name
        print(f"  {name}: {'存在' if p.exists() else '缺失'}", end="")
        if p.exists() and name.endswith(".jsonl"):
            print(f"（{len(p.read_text(encoding='utf-8').splitlines())} 行）")
        else:
            print()
    mats = list((batch_dir / "materials").glob("*.md")) if (batch_dir / "materials").exists() else []
    print(f"  materials: {len(mats)} 份")


def main() -> None:
    parser = argparse.ArgumentParser(description="题目关系批量补充（common）批处理工具")
    sub = parser.add_subparsers(dest="cmd", required=True)

    p = sub.add_parser("init", help="建立专题候选清单与基线")
    p.add_argument("--batch", required=True, help="批次 ID，例如 b001-erfen-2026-10-02")
    p.add_argument("--topic", required=True, help="专题名，例如 二分答案")
    p.add_argument("--keyword", default=None, help="正文关键词（默认同专题名）")
    p.add_argument("--force", action="store_true")
    p.set_defaults(func=cmd_init)

    p = sub.add_parser("pairs", help="生成并去重候选题对")
    p.add_argument("--batch", required=True)
    p.set_defaults(func=cmd_pairs)

    p = sub.add_parser("materials", help="生成判断材料摘录")
    p.add_argument("--batch", required=True)
    p.add_argument("--only", nargs="*", help="只生成指定题目，如 luogu/P1163")
    p.set_defaults(func=cmd_materials)

    p = sub.add_parser("calibrate", help="运行 Jev 校准并输出阈值建议")
    p.add_argument("--batch", required=True)
    p.set_defaults(func=cmd_calibrate)

    p = sub.add_parser("judge", help="对全部候选题对跑 Jev 判断")
    p.add_argument("--batch", required=True)
    p.add_argument("--workers", type=int, default=6)
    p.set_defaults(func=cmd_judge)

    p = sub.add_parser("decide", help="按合并规则分类判断结果")
    p.add_argument("--batch", required=True)
    p.add_argument("--t1", type=float, default=0.8, help="shared_core 下限")
    p.add_argument("--t2", type=float, default=0.5, help="check_similar 下限")
    p.add_argument("--t3", type=float, default=0.3, help="only_label 上限")
    p.add_argument("--margin", type=float, default=0.05, help="边界带宽：距阈值过近降级为 hold")
    p.set_defaults(func=cmd_decide)

    p = sub.add_parser("write", help="把 reasons.jsonl 的关系写入 frontmatter（双侧）")
    p.add_argument("--batch", required=True)
    p.add_argument("--now", required=True, help="updated 时间，如 '2026-10-02 18:30'")
    p.add_argument("--dry-run", action="store_true")
    p.set_defaults(func=cmd_write)

    p = sub.add_parser("report", help="批次状态汇总")
    p.add_argument("--batch", required=True)
    p.set_defaults(func=cmd_report)

    args = parser.parse_args()
    if getattr(args, "keyword", None) is None and getattr(args, "topic", None) is not None:
        args.keyword = args.topic
    args.func(args)


if __name__ == "__main__":
    main()
