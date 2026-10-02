#!/usr/bin/env python3
"""pre 全量批次共享库（M0b）。

被 `pre_batch.py` 与 `pre_batch.py selftest` 复用。所有路径基于 `repo_root`
（默认真实仓库根），因此 M0b 的离线自检可以在临时 fixture 仓库上跑完整管线，
不触碰真实题目文件、不发真实付费调用。

职责：
- 统一难度源校验（tag-config.json vs lib/problem.js）
- 全仓题目索引（身份以 frontmatter 为准）
- 候选对生成（全局去重、Δrank 窗口、辅助标签排除、不占写入名额）
- 专题分片与子分片（固定归属 + 并集/互斥校验）
- 材料摘录、引文定位、关键词双向子串匹配
- 全局候选池与四键仲裁
- frontmatter 关系项文本级编辑（追加 / 定点删除）
- 环检测、原子写、批次状态目录解析
"""

from __future__ import annotations

import hashlib
import json
import os
import re
import subprocess
import sys
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))
import batch as B  # noqa: E402

REPO_ROOT_DEFAULT = B.REPO_ROOT
CONFIG_NAME = "tag-config.json"

# 仲裁强度等级：历史未重审关系先占位，其次 strong，最后 template-level
STRENGTH_RANK = {"legacy-placeholder": -1, "strong": 0, "template-level": 1}
CONFIDENCE_RANK = {"high": 2, "medium": 1, "low": 0}

VERDICTS = ("accept", "reject", "doubtful")
REJECT_REASONS = (
    "same-difficulty-twin",
    "b-difficulty-elsewhere",
    "no-reuse",
    "direction-wrong",
    "insufficient-evidence",
    "self-or-duplicate",
)

ANALYSIS_HEADING = B.ANALYSIS_HEADING
STOP_HEADING = B.STOP_HEADING
MATERIAL_CHARS = 4000


# ------------------------------------------------------------------ 基础工具

def norm_ws(s: str) -> str:
    """去除全部空白，用于引文与关键词的跨行定位。"""
    return re.sub(r"\s+", "", s or "")


def sha16(text: str) -> str:
    return hashlib.sha256(text.encode("utf-8")).hexdigest()[:16]


def atomic_write_text(path: Path, text: str) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    tmp = path.with_suffix(path.suffix + ".tmp")
    tmp.write_text(text, encoding="utf-8")
    os.replace(tmp, path)


def append_jsonl(path: Path, rows: list[dict]) -> None:
    if not rows:
        return
    path.parent.mkdir(parents=True, exist_ok=True)
    with path.open("a", encoding="utf-8") as f:
        for row in rows:
            f.write(json.dumps(row, ensure_ascii=False) + "\n")


def read_jsonl(path: Path) -> list[dict]:
    if not path.exists():
        return []
    return [json.loads(l) for l in path.read_text(encoding="utf-8").splitlines() if l.strip()]


def write_jsonl(path: Path, rows: list[dict]) -> None:
    atomic_write_text(path, "\n".join(json.dumps(r, ensure_ascii=False) for r in rows) + ("\n" if rows else ""))


# ------------------------------------------------------- 难度单源与配置加载

def load_config(repo_root: Path) -> dict:
    return json.loads((repo_root / "scripts/problem-analysis-tools/relation_batch" / CONFIG_NAME).read_text(encoding="utf-8"))


def lib_difficulty_order(repo_root: Path) -> list[str]:
    js = (repo_root / "lib" / "problem.js").read_text(encoding="utf-8")
    m = re.search(r"DIFFICULTY_ORDER\s*=\s*\[(.*?)\]", js, re.S)
    if not m:
        raise SystemExit("无法从 lib/problem.js 读取 DIFFICULTY_ORDER，拒绝启动（防两套难度序漂移）")
    return re.findall(r"'([^']+)'", m.group(1))


def assert_difficulty_sync(repo_root: Path, cfg: dict) -> list[str]:
    """难度序必须与 lib/problem.js 一致，漂移即拒绝启动。"""
    lib_order = lib_difficulty_order(repo_root)
    cfg_order = cfg.get("difficulty_order")
    if lib_order != cfg_order:
        raise SystemExit(
            "难度序漂移：lib/problem.js 与 tag-config.json 不一致\n"
            f"  lib : {lib_order}\n  cfg : {cfg_order}\n"
            "请以 lib/problem.js 为准更新 tag-config.json"
        )
    return lib_order


# --------------------------------------------------------------- 题目索引

def load_problems(repo_root: Path, difficulty_order: list[str]) -> list[dict]:
    """全仓题目索引。身份以 frontmatter 为准，目录名只做对照；缺失身份则跳过并记账。

    两个 hash 分工（§7.1-3）：
    - `hash`：整文件 hash，用于写入前的外部编辑检测（人工改过则跳过）。
    - `evidence_hash`：正文 + 非关系 frontmatter（排除 pre/common/recommend/updated）的 hash，
      作为「判断证据」的版本。本批自己写 pre 不会改变它，所以不会把自己的写入误判为证据变化。
    """
    tiers = {name: i for i, name in enumerate(difficulty_order)}
    out: list[dict] = []
    for index_md in sorted((repo_root / "problems").glob("*/*/index.md")):
        text = index_md.read_text(encoding="utf-8")
        scalars, relations, body = B.extract_frontmatter(index_md)
        oj, pid = scalars.get("oj", ""), scalars.get("problem_id", "")
        if not oj or not pid:
            continue
        tags = [t for t in re.findall(r'"([^"]+)"', scalars.get("tags", "")) if t]
        difficulty = scalars.get("difficulty", "")
        evidence = {k: v for k, v in scalars.items()
                    if k not in ("pre", "common", "recommend", "updated")}
        out.append({
            "key": f"{oj}/{pid}",
            "dir": str(index_md.parent.relative_to(repo_root)),
            "oj": oj,
            "problem_id": pid,
            "title": scalars.get("title", ""),
            "difficulty": difficulty,
            "tier": tiers.get(difficulty),
            "tags": tags,
            "existing_pre": sorted(
                f"{r.get('oj')}/{r.get('problem_id')}" for r in relations if r["field"] == "pre"
            ),
            "hash": sha16(text),
            "evidence_hash": sha16(
                json.dumps(evidence, ensure_ascii=False, sort_keys=True) + "\n" + body),
            "body_chars": len(body),
        })
    return out


def tag_doc_order(problems: list[dict]) -> dict[str, int]:
    """标签的全局文档序：按题目目录扫描顺序首次出现的次序（分片主专题的第二排序键）。"""
    order: dict[str, int] = {}
    for p in problems:
        for t in p["tags"]:
            order.setdefault(t, len(order))
    return order


def topic_problem_counts(problems: list[dict], aux_tags: set[str]) -> dict[str, int]:
    counts: dict[str, int] = {}
    for p in problems:
        if p["tier"] is None:
            continue
        for t in set(p["tags"]) - aux_tags:
            counts[t] = counts.get(t, 0) + 1
    return counts


# --------------------------------------------------------------- 材料与引文

def build_material(repo_root: Path, p: dict, with_line_numbers: bool = False) -> str:
    """题目材料：frontmatter 元信息 + 解析原文摘录 + 代码位置（原文摘录，非模型摘要）。"""
    index_md = repo_root / p["dir"] / "index.md"
    text = index_md.read_text(encoding="utf-8")
    _, _, body = B.extract_frontmatter(index_md)
    candidates = [
        r"^##\s*题目解析.*?(?=^##\s|\Z)",
        r"^###?\s*(?:题意|思路).*?(?=^#{2,3}\s*(?:Python 知识|代码|复杂度|总结|一图流)|\Z)",
        ANALYSIS_HEADING + rf".*?(?={STOP_HEADING}|\Z)",
    ]
    analysis = ""
    for pat in candidates:
        m = re.search(pat, body, re.M | re.S)
        if m and len(m.group(0).strip()) >= 300:
            analysis = m.group(0).strip()[:MATERIAL_CHARS]
            break
    if not analysis:
        analysis = body.strip()[:2000]
    code_files = sorted(f.name for f in (repo_root / p["dir"]).iterdir()
                        if f.is_file() and f.suffix in {".cpp", ".py"})
    lines = [
        f"# {p['oj']} {p['problem_id']} {p['title']}",
        "",
        f"> 原文摘录，非模型摘要。来源：`{p['dir']}/index.md`（内容哈希 {p['hash']}）。",
        "> 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。",
        "",
        "## 元信息（frontmatter 摘录）",
        f"- 难度：{p['difficulty'] or '—'}；标签：{p['tags']}",
        "",
        "## 题目解析（原文摘录）",
        "",
        analysis,
        "",
        "## 代码位置",
    ]
    lines += [f"- `{p['dir']}/{c}`" for c in code_files] or ["- （无）"]
    md = "\n".join(lines) + "\n"
    if with_line_numbers:
        md = "\n".join(f"{i:4d}| {l}" for i, l in enumerate(md.splitlines(), 1))
    _ = text
    return md


def quote_line(text: str, quote: str) -> tuple[int, bool]:
    """在原文中定位逐字引文（忽略空白差异），返回（行号, 是否命中）。"""
    target = norm_ws(quote)
    if not target:
        return 0, False
    stripped = re.sub(r"^\s*\d+\|\s?", "", text, flags=re.M)  # 兼容带行号材料
    norm_chars: list[str] = []
    line_of: list[int] = []
    for lineno, line in enumerate(stripped.splitlines(), 1):
        for ch in line:
            if ch.isspace():
                continue
            norm_chars.append(ch)
            line_of.append(lineno)
    hay = "".join(norm_chars)
    pos = hay.find(target)
    if pos < 0:
        return 0, False
    return line_of[pos], True


def tokens(text: str) -> set[str]:
    """结构化落点关键词：ASCII 词 + 中文 2/3-gram（中文无分词，用 n-gram 做子串匹配）。"""
    out: set[str] = set()
    for w in re.findall(r"[A-Za-z_][A-Za-z0-9_]{2,}", text or ""):
        out.add(w.lower())
    for run in re.findall(r"[\u4e00-\u9fff]+", text or ""):
        if len(run) <= 6:
            out.add(run)
        for n in (2, 3):
            for i in range(len(run) - n + 1):
                out.add(run[i:i + n])
    return out


def keyword_hits(step_text: str, material: str) -> tuple[int, list[str]]:
    """双向子串匹配：step 的关键词出现在材料中，或材料中的词出现在 step 中。"""
    hay = norm_ws(material)
    toks = tokens(step_text)
    hits = sorted(t for t in toks if t and norm_ws(t) in hay)
    return len(hits), hits[:8]


# ------------------------------------------------------------------ 候选生成

def pair_key(a: dict, b: dict) -> str:
    return f"{a['key']}->{b['key']}"


def build_candidates(problems: list[dict], cfg: dict) -> tuple[list[dict], list[dict]]:
    """全局候选对（有向：简单→难），去重、不消耗写入名额。

    规则：两侧都有难度分级；1 <= Δrank <= 2；至少一个非辅助共同标签；
    已有 pre 边（任一方向）排除并记录原因。
    """
    aux = set(cfg["aux_tags"])
    min_delta = cfg["candidate"]["min_delta"]
    max_delta = cfg["candidate"]["max_delta"]
    tiered = [p for p in problems if p["tier"] is not None]
    exists: set[tuple[str, str]] = set()
    for p in problems:
        for t in p["existing_pre"]:
            exists.add((t, p["key"]))
            exists.add((p["key"], t))

    cands: list[dict] = []
    excluded: list[dict] = []
    order = sorted(tiered, key=lambda p: (p["tier"], p["oj"], p["problem_id"]))
    for i in range(len(order)):
        for j in range(i + 1, len(order)):
            a, b = order[i], order[j]
            # 方向固定为难度秩小 → 大（Δ>=1 保证不会同秩）
            if a["tier"] > b["tier"]:
                a, b = b, a
            delta = b["tier"] - a["tier"]
            if delta < min_delta or delta > max_delta:
                continue
            shared = sorted(set(a["tags"]) & set(b["tags"]) - aux)
            if not shared:
                continue
            k = pair_key(a, b)
            if (a["key"], b["key"]) in exists or (b["key"], a["key"]) in exists:
                excluded.append({"key": k, "reason": "already-exists-pre",
                                 "existing_on": "recheck-candidate" if (b["key"], a["key"]) in exists else ""})
                continue
            cands.append({
                "key": k,
                "a": {kk: a[kk] for kk in ("key", "oj", "problem_id", "dir", "tier", "difficulty", "title")},
                "b": {kk: b[kk] for kk in ("key", "oj", "problem_id", "dir", "tier", "difficulty", "title")},
                "delta": delta,
                "shared_tags": shared,
                "status": "candidate",
            })
    return cands, excluded


# --------------------------------------------------------------- 专题分片

def _sanitize(tag: str) -> str:
    """分片 ID 片段：保留中文与 ASCII 字母数字（便于读报告与台账），其余转连字符。

    中文可以出现在 task_id / shard_id / 文件路径中；而 agent 名与 tab label 另有约定
    （`pre-<slot>-<gen>` 与 `<oj>-<pid>`），不受本函数影响。
    """
    s = re.sub(r"[^0-9A-Za-z\u4e00-\u9fff]+", "-", tag).strip("-")
    if not s:
        s = "t" + hashlib.sha1(tag.encode("utf-8")).hexdigest()[:6]
    return s[:24]


def _unique(base: str, used: dict[str, int]) -> str:
    """全局唯一分片 ID：同名时分片追加数字后缀。"""
    used[base] = used.get(base, 0) + 1
    return base if used[base] == 1 else f"{base}-{used[base]}"


def assign_shards(cands: list[dict], problems: list[dict], cfg: dict) -> tuple[list[dict], dict[str, str]]:
    """固定归属分片：每个候选恰好一个主专题；大专题按共现标签拆子类并保留剩余分片。"""
    aux = set(cfg["aux_tags"])
    topic_cfg = cfg["topic"]
    counts = topic_problem_counts(problems, aux)
    doc_order = tag_doc_order(problems)
    topics = {t for t, n in counts.items() if n >= topic_cfg["min_problems"]}

    # 主专题：共享非辅助标签中「文档序最靠前」的合格专题；都不合格时退到文档序最前的共同标签
    def primary(c: dict) -> str:
        shared = c["shared_tags"]
        ok = [t for t in shared if t in topics]
        pool = ok or shared
        return min(pool, key=lambda t: (doc_order.get(t, 10 ** 9), t))

    for c in cands:
        c["primary_topic"] = primary(c)
    for c in cands:
        c.setdefault("tag", c["primary_topic"])

    by_topic: dict[str, list[dict]] = {}
    for c in cands:
        by_topic.setdefault(c["primary_topic"], []).append(c)

    shards: list[dict] = []
    shard_of: dict[str, str] = {}
    used: dict[str, int] = {}
    for tag, plist in sorted(by_topic.items(), key=lambda kv: (-len(kv[1]), kv[0])):
        base = _unique(_sanitize(tag), used)
        need_split = (counts.get(tag, 0) > topic_cfg["split_threshold_problems"]
                      or len(plist) > topic_cfg["split_threshold_pairs"])
        if not need_split:
            shards.append({"shard_id": base, "tag": tag, "parent": tag, "kind": "topic",
                           "pair_count": len(plist), "pairs": [c["key"] for c in plist]})
            for c in plist:
                shard_of[c["key"]] = base
            continue
        # 次级拆分：按共现的非辅助标签（排除主标签）的候选数降序，选择能覆盖大部分的分片
        co: dict[str, int] = {}
        for c in plist:
            for t in c["shared_tags"]:
                if t != tag and t in topics:
                    co[t] = co.get(t, 0) + 1
        secondaries = [t for t, n in sorted(co.items(), key=lambda kv: (-kv[1], doc_order.get(kv[0], 0))) if n >= 3]
        buckets: dict[str, list[dict]] = {t: [] for t in secondaries}
        remainder: list[dict] = []
        for c in plist:
            hit = next((t for t in secondaries if t in c["shared_tags"]), None)
            (buckets[hit] if hit else remainder).append(c)
        for t in secondaries:
            if not buckets[t]:
                continue
            sid = _unique(f"{base}-{_sanitize(t)}", used)
            shards.append({"shard_id": sid, "tag": tag, "parent": tag, "kind": "subtopic",
                           "sub_tag": t, "pair_count": len(buckets[t]), "pairs": [c["key"] for c in buckets[t]]})
            for c in buckets[t]:
                shard_of[c["key"]] = sid
        if remainder:
            sid = _unique(f"{base}-rest", used)
            shards.append({"shard_id": sid, "tag": tag, "parent": tag, "kind": "remainder",
                           "pair_count": len(remainder), "pairs": [c["key"] for c in remainder]})
            for c in remainder:
                shard_of[c["key"]] = sid
    for c in cands:
        c["shard_id"] = shard_of[c["key"]]
    return shards, shard_of


def validate_shards(shards: list[dict], cands: list[dict]) -> dict:
    """子分片并集 = 父集合且互不重叠；全部候选恰好分配一次。"""
    problems: list[str] = []
    for s in shards:
        problems.extend(s["pairs"])
    dup = {k for k in problems if problems.count(k) > 1}
    assigned = set(problems)
    all_keys = {c["key"] for c in cands}
    unassigned = sorted(all_keys - assigned)
    unknown = sorted(assigned - all_keys)
    # 父集合校验：同一 parent 的子分片并集必须等于「主专题为该 parent 的全部候选」，且互不重叠
    parents: dict[str, list[dict]] = {}
    for s in shards:
        if s["kind"] != "topic":
            parents.setdefault(s["parent"], []).append(s)
    parent_of = {c["key"]: c.get("primary_topic", c.get("tag", "")) for c in cands}
    parent_check = []
    for parent, subs in parents.items():
        sets = [set(s["pairs"]) for s in subs]
        union = set().union(*sets) if sets else set()
        inter = set()
        for i in range(len(sets)):
            for j in range(i + 1, len(sets)):
                inter |= sets[i] & sets[j]
        expect = {k for k, t in parent_of.items() if t == parent}
        parent_check.append({"parent": parent, "subs": len(subs), "union": len(union),
                             "expected": len(expect), "overlap": len(inter),
                             "ok": not inter and union == expect})
    ok = not dup and not unassigned and not unknown and all(p["ok"] for p in parent_check)
    return {"ok": ok, "assigned": len(assigned), "candidates": len(all_keys),
            "duplicated": sorted(dup)[:10], "unassigned": unassigned[:10], "unknown": unknown[:10],
            "parent_check": parent_check}


# ------------------------------------------------------------------ 仲裁

def select_m1_candidates(repo_root: Path, batch: str, bound: int = 200,
                         parents: list[str] | None = None) -> tuple[list[str], dict]:
    """M1 有界试点候选选择（§5/§15）：默认从最大专题（可指定多个 parent 标签）按比例抽，

    每个分片至少 1 个（含子分片与剩余分片），体现边界案例；总量 <= bound。
    parents 为空时覆盖全部分片。
    """
    bd = repo_root / "relation-batches" / batch
    shards = read_jsonl(bd / "shards.jsonl")
    if parents:
        shards = [s for s in shards if s["tag"] in set(parents)]
    pairs_path = bd / "shard-pairs.json"
    pairs = json.loads(pairs_path.read_text(encoding="utf-8")) if pairs_path.exists() else {}
    total = sum(s["pair_count"] for s in shards) or 1
    ordered = sorted(shards, key=lambda s: (-s["pair_count"], s["shard_id"]))
    picked: list[str] = []
    seen: set[str] = set()
    left = bound
    for s in ordered:
        if left <= 0:
            break
        ps = sorted(pairs.get(s["shard_id"], []))
        k = max(1, round(bound * len(ps) / total))
        k = min(k, len(ps), left)
        for key in ps[:k]:
            if key not in seen:
                picked.append(key)
                seen.add(key)
                left -= 1
    idx = {s["shard_id"]: sorted(pairs.get(s["shard_id"], [])) for s in ordered}
    ptr = {sid: 0 for sid in idx}
    while left > 0:
        progressed = False
        for s in ordered:
            if left <= 0:
                break
            sid = s["shard_id"]
            while ptr[sid] < len(idx[sid]) and idx[sid][ptr[sid]] in seen:
                ptr[sid] += 1
            if ptr[sid] < len(idx[sid]):
                key = idx[sid][ptr[sid]]
                ptr[sid] += 1
                picked.append(key)
                seen.add(key)
                left -= 1
                progressed = True
        if not progressed:
            break
    per_shard = {s["shard_id"]: sum(1 for k in picked if k in set(pairs.get(s["shard_id"], []))) for s in ordered}
    info = {"bound": bound, "selected": len(picked), "candidates": total,
            "shards_covered": sum(1 for v in per_shard.values() if v),
            "topics_covered": len({s["tag"] for s in ordered if per_shard.get(s["shard_id"])}),
            "per_shard": per_shard}
    return picked, info


def arbitration_key(item: dict) -> tuple:
    """四键稳定排序（§6.1）：强度等级 → confidence → step 分数降序 → 题对 key 升序。"""
    return (
        STRENGTH_RANK.get(item.get("strength", "template-level"), 1),
        -CONFIDENCE_RANK.get(item.get("confidence", "low"), 0),
        -float(item.get("step_score") or 0.0),
        item["key"],
    )


def arbitrate(pool: list[dict], max_pre: int) -> tuple[list[dict], list[dict]]:
    """对单个 B 的候选池做前 N 选择；返回 (kept, displaced)。"""
    ordered = sorted(pool, key=arbitration_key)
    return ordered[:max_pre], ordered[max_pre:]


# ------------------------------------------------------- frontmatter 关系编辑

def remove_relation_item(text: str, field: str, target: dict) -> tuple[str, bool]:
    """定点删除某关系项（保留顺序与其余内容），返回 (新文本, 是否删除)。"""
    if not text.startswith("---\n"):
        raise ValueError("缺少 frontmatter")
    end = text.find("\n---", 4)
    if end == -1:
        raise ValueError("frontmatter 未闭合")
    fm_lines = text[4:end].splitlines()
    body = text[end:]
    out: list[str] = []
    i = 0
    removed = False
    while i < len(fm_lines):
        line = fm_lines[i]
        if re.match(rf"^{field}:\s*$", line):
            out.append(line)
            i += 1
            while i < len(fm_lines):
                cur = fm_lines[i]
                if cur.startswith("  - ") or cur.startswith("    "):
                    block = [cur]
                    j = i + 1
                    while j < len(fm_lines) and fm_lines[j].startswith("    "):
                        block.append(fm_lines[j])
                        j += 1
                    blob = "\n".join(block)
                    if (re.search(rf'oj:\s*"?{re.escape(target["oj"])}"?', blob)
                            and re.search(rf'problem_id:\s*"?{re.escape(target["problem_id"])}"?', blob)):
                        removed = True
                    else:
                        out.extend(block)
                    i = j
                else:
                    break
            continue
        out.append(line)
        i += 1
    if not removed:
        return text, False
    return "---\n" + "\n".join(out) + body, True


def add_relation_item(text: str, field: str, target: dict, reason: str, now: str) -> tuple[str, bool]:
    return B.add_relation_item(text, field, target, reason, now)


def frontmatter_of(text: str) -> str:
    if not text.startswith("---\n"):
        return ""
    end = text.find("\n---", 4)
    return text[4:end] if end != -1 else ""


def body_of(text: str) -> str:
    end = text.find("\n---", 4)
    return text[end + 4:] if end != -1 else text


def pre_entries_of(repo_root: Path, oj: str, pid: str) -> list[dict]:
    for index_md in (repo_root / "problems").glob(f"{oj}/{pid}/index.md"):
        _, relations, _ = B.extract_frontmatter(index_md)
        return [{"oj": r.get("oj", ""), "problem_id": r.get("problem_id", ""), "reason": r.get("reason", "")}
                for r in relations if r["field"] == "pre"]
    return []


def all_pre_edges(repo_root: Path, problems: list[dict]) -> set[tuple[str, str]]:
    edges = set()
    for p in problems:
        for t in p["existing_pre"]:
            edges.add((t, p["key"]))
    return edges


def find_cycle(edges: set[tuple[str, str]]) -> list[str] | None:
    """返回一条环（若存在）。"""
    graph: dict[str, list[str]] = {}
    for a, b in edges:
        graph.setdefault(a, []).append(b)
    color: dict[str, int] = {}
    stack: list[str] = []

    def dfs(u: str) -> list[str] | None:
        color[u] = 1
        stack.append(u)
        for v in graph.get(u, []):
            if color.get(v, 0) == 1:
                return stack[stack.index(v):] + [v]
            if color.get(v, 0) == 0:
                r = dfs(v)
                if r:
                    return r
        stack.pop()
        color[u] = 2
        return None

    for node in list(graph):
        if color.get(node, 0) == 0:
            r = dfs(node)
            if r:
                return r
    return None


# ------------------------------------------------------------ 状态与预算

def resolve_state_dir(repo_root: Path, batch: str) -> Path:
    """用 git 状态目录承载任务队列（不提交），失败时退回批次目录。"""
    try:
        out = subprocess.run(["git", "rev-parse", "--git-path", f"rbook-batches/{batch}"],
                             cwd=repo_root, capture_output=True, text=True)
        if out.returncode == 0:
            p = Path(out.stdout.strip())
            if not p.is_absolute():
                p = (repo_root / p).resolve()
            p.mkdir(parents=True, exist_ok=True)
            return p
    except Exception:
        pass
    p = repo_root / "relation-batches" / batch / "state"
    p.mkdir(parents=True, exist_ok=True)
    return p


def git_state(repo_root: Path) -> dict:
    def run(*args: str) -> str:
        r = subprocess.run(["git", *args], cwd=repo_root, capture_output=True, text=True)
        return r.stdout.strip()

    dirty = run("status", "--porcelain")
    return {"head": run("rev-parse", "HEAD"), "branch": run("rev-parse", "--abbrev-ref", "HEAD"),
            "dirty_files": str(len([l for l in dirty.splitlines() if l.strip()]))}


class Budget:
    """逐请求上界估算 + 单一计账器：已结算 + 在途预留 + 本次上界 <= 上限。"""

    def __init__(self, limit_usd: float, usd_per_1k_tokens: float):
        self.limit = limit_usd
        self.price = usd_per_1k_tokens
        self.settled = 0.0
        self.inflight = 0.0
        self.stopped = False
        self.stop_reason = ""

    def upper_bound(self, state_chars: int, question_chars: int) -> float:
        """单请求费用上界（规格 §11：逐请求上界估算，上界不得低于实际）。

        token 估算：按实测吞吐反推，Jev 每对约 2400 token / 约 9500 字符 ≈ 0.25 token/字符。
        这里取 **0.5 token/字符**（约 2 倍于实测），作为保守上界。
        单价默认取规格 §2 反推值：$5.1 / 121M tok ≈ $4.215e-5 每千 token。
        """
        tokens = (state_chars + question_chars) * 0.5
        return tokens / 1000.0 * self.price

    def reserve(self, upper: float) -> bool:
        if self.stopped:
            return False
        if self.settled + self.inflight + upper > self.limit:
            self.stopped = True
            self.stop_reason = f"预算硬顶：已结算 {self.settled:.4f} + 在途 {self.inflight:.4f} + 本次上界 {upper:.4f} > {self.limit}"
            return False
        self.inflight += upper
        return True

    def settle(self, upper: float, actual_cost: float | None) -> None:
        self.inflight = max(0.0, self.inflight - upper)
        self.settled += upper if actual_cost is None else actual_cost
        if self.settled >= self.limit * 0.9:
            self.stopped = True
            self.stop_reason = f"已达 90% 暂停线：{self.settled:.4f} / {self.limit}"

    def snapshot(self) -> dict:
        return {"limit_usd": self.limit, "settled_usd": round(self.settled, 4),
                "inflight_usd": round(self.inflight, 4), "stopped": self.stopped,
                "stop_reason": self.stop_reason, "usd_per_1k_tokens": self.price}
