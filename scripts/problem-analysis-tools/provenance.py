"""产物溯源：某个暂存文件到底是**哪个子 agent**写的。

⚠ 为什么需要它
------------
专家与 worker 共享工作区（`worktree: false`），且都可能在
`/tmp/roj-think/<pid>/` 下写文件。正常分工是：

    R1 专家写 index.md / main.cpp / main.py   （初稿）
    R2 worker 改 main.cpp / main.py           （**明令禁止碰 index.md**）
    R3 专家重写 index.md                      （以最终代码为准）

但**没有机制阻止两个角色写同一个路径** —— 谁后写谁赢。

2026-10-08 实际发生过一次：父会话误把 R3 指令发给了 worker（角色混淆），
于是 worker 写了 175 行的 `index.md`，专家随后写了 93 行的正确版本。
**运气好是专家后写。** 若顺序反过来，落盘的就会是 worker 版。

本工具从各子 agent 的会话文件里 grep「Successfully wrote to <path>」记录，
按时间列出**每个文件的完整写入历史**，从而回答「这份文件是谁写的、什么时候」。

用法
----
    python3 provenance.py 5017                    # 查某题暂存目录
    python3 provenance.py 5017 --file index.md    # 只查某文件
    python3 provenance.py --stage /tmp/roj-think/5017

退出码：0 = 正常；1 = 发现**非预期角色**的写入（例如 worker 写了 index.md）
"""

from __future__ import annotations

import argparse
import datetime as dt
import json
import pathlib
import re
import sys

REPO_ROOT = pathlib.Path(__file__).resolve().parents[2]
RUNS_ROOT = REPO_ROOT.parent / "new_ROJ" / ".pi-subagents" / "runs"
STAGE_ROOT = pathlib.Path("/tmp/roj-think")

WRITE_RE = re.compile(r"Successfully wrote to (\S+?)(?:[\"\s]|$)")
# worker 角色**不允许**写的文件
WORKER_FORBIDDEN = {"index.md"}


def _ts(rec: dict) -> float | None:
    """从 jsonl 记录里取精确时间戳（毫秒）。取不到返回 None。"""
    for k in ("timestamp", "ts", "time"):
        v = rec.get(k)
        if isinstance(v, (int, float)) and v > 1e11:   # 毫秒
            return v / 1000.0
    return None


def _text_of(rec: dict) -> str:
    """把一条记录里的文本部分拼出来（tool result / text 都要）。"""
    m = rec.get("message") or rec
    c = m.get("content")
    parts: list[str] = []
    if isinstance(c, str):
        parts.append(c)
    elif isinstance(c, list):
        for b in c:
            if not isinstance(b, dict):
                continue
            t = b.get("type")
            if t == "text":
                parts.append(b.get("text", ""))
            elif t == "tool_result":
                parts.append(json.dumps(b.get("content"), ensure_ascii=False))
    return "\n".join(parts)


def role_of(agent: str) -> str:
    if "verify-worker" in agent or agent.endswith("worker"):
        return "worker"
    if "expert" in agent:
        return "expert"
    return "other"


def collect_writes(target: pathlib.Path) -> list[dict]:
    """扫所有子 agent 会话，收集对 target 目录下文件的写入。

    时间取 jsonl 记录里自带的 `timestamp`（毫秒），比会话文件 mtime 准确得多。
    """
    out: list[dict] = []
    if not RUNS_ROOT.is_dir():
        return out
    for sess in RUNS_ROOT.glob("*/*.jsonl"):
        agent = sess.stem
        try:
            text = sess.read_text(errors="replace")
        except OSError:
            continue
        for lineno, line in enumerate(text.splitlines(), 1):
            if "/tmp/roj-think/" not in line:
                continue
            try:
                rec = json.loads(line)
            except json.JSONDecodeError:
                continue
            body = _text_of(rec)
            if "/tmp/roj-think/" not in body:
                continue
            stamp = _ts(rec)
            approx = stamp is None
            if stamp is None:
                # 部分记录（尤其老格式）没有 timestamp —— 用会话文件 mtime 兜底，
                # 这个值**对同一会话里的多条记录全都一样**，只能用于排序，不能当精确时刻。
                stamp = sess.stat().st_mtime
            for m in WRITE_RE.finditer(body):
                raw = m.group(1).rstrip('"\\,')
                p = pathlib.Path(raw)
                if p.parent != target:
                    continue
                out.append({
                    "agent": agent,
                    "role": role_of(agent),
                    "file": p.name,
                    "ts": stamp,
                    "approx": approx,
                    "session": str(sess.relative_to(RUNS_ROOT)),
                    "line": lineno,
                })
    out.sort(key=lambda r: (r["file"], r["ts"]))
    return out


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("pid", nargs="?")
    ap.add_argument("--stage")
    ap.add_argument("--file")
    args = ap.parse_args()

    if args.stage:
        target = pathlib.Path(args.stage)
    elif args.pid:
        target = STAGE_ROOT / args.pid
    else:
        raise SystemExit("用法：provenance.py <pid> [--file index.md] [--stage DIR]")

    print(f"暂存目录：{target}")
    if not target.is_dir():
        print("  ⛔ 目录不存在")
        return 1

    # 现存文件的实况
    print("\n现存文件：")
    for f in sorted(target.iterdir()):
        if f.is_file():
            ts = dt.datetime.fromtimestamp(f.stat().st_mtime).strftime("%H:%M:%S")
            print(f"  {f.name:<14} {f.stat().st_size:>7}B  行数 {sum(1 for _ in f.open(errors='replace')):>4}  mtime {ts}")

    writes = collect_writes(target)
    if args.file:
        writes = [w for w in writes if w["file"] == args.file]

    if not writes:
        print("\n⚠ 未在子 agent 会话里找到写入记录")
        print("  （可能：文件是父会话直接写的，或会话文件已被清理）")
        return 0

    print("\n写入历史（按文件 + 时间）：")
    bad = []
    cur = None
    for w in writes:
        if w["file"] != cur:
            cur = w["file"]
            print(f"  ── {cur} ──")
        ts = dt.datetime.fromtimestamp(w["ts"]).strftime("%H:%M:%S") + ("≈" if w["approx"] else " ")
        flag = ""
        if w["role"] == "worker" and w["file"] in WORKER_FORBIDDEN:
            flag = "  ⛔⛔ worker 不该写这个文件！"
            bad.append(w)
        print(f"     {ts} {w['role']:<7} {w['agent']}{flag}")

    # 每个文件的**最后一次**写入者（决定落盘内容）
    print("\n最终生效（每个文件取最后一次写入）：")
    last: dict[str, dict] = {}
    for w in writes:
        last[w["file"]] = w
    for fname, w in sorted(last.items()):
        ts = dt.datetime.fromtimestamp(w["ts"]).strftime("%H:%M:%S") + ("≈" if w["approx"] else " ")
        print(f"  {fname:<14} ← {w['role']:<7} {w['agent']}  ({ts})")
        if w["role"] == "worker" and fname in WORKER_FORBIDDEN:
            print(f"     ⛔ 该文件最终由 worker 写入 —— 与定义不符！")

    if bad:
        print(f"\n⛔ 发现 {len(bad)} 次**非预期角色**的写入：")
        for w in bad:
            print(f"   {w['agent']} 写了 {w['file']}（worker 定义明令禁止）")
        print("\n  注：标 ≈ 的时间是从会话文件 mtime 兜底的近似值（该记录无 timestamp），"
              "\n      只可用于排序，不能当精确时刻。")
        final = last.get("index.md")
        if final and final["role"] == "expert":
            print("\n  ✅ 但最后一次写 index.md 的是**专家** ⇒ 落盘内容正确")
            return 0
        print("\n  ⛔ 且最后一次写 index.md 的不是专家 ⇒ 落盘内容可能错误，请重做 R3")
        return 1

    print("\n✅ 写入者与角色分工一致")
    return 0


if __name__ == "__main__":
    sys.exit(main())
