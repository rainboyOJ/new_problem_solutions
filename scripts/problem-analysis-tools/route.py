"""角色路由：给定题号，查出它的「专家」与「worker」子 agent 名字。

⚠ 为什么需要它
------------
2026-10-08，父会话**连续两次**把 R3（写最终 index.md）指令误发给了 worker：

  · `5017` → 发给了 roj-verify-worker-17（正确应为 roj-expert-gemini-29）
  · `5013` → 发给了 roj-verify-worker-21（正确应为 roj-expert-gemini-32）

两次都是「手滑」：上一轮刚跟 worker 交互过，`continue` 时名字还在手边。
worker 的定义里明确写着「❌ 不写 index.md」—— 所以这是**必须防住**的错误。

**结论：「记住要小心」不是有效的修法。** 必须在调用点做机械校验。
本工具就是那个校验点：发 R3 之前先跑一次，拿到确切的专家名字。

## 工作原理

pi 的子 agent 运行记录在 `<new_ROJ>/.pi-subagents/runs/<runId>/`：
  · `run.json`      —— 每个 child 的 name / agent / promptText（含题号）
  · `<name>.jsonl`  —— 会话记录

所以「题号 → 专家名字」是可以从磁盘上查出来的，不需要凭记忆。

用法
----
    python3 route.py 5013              # 查该题的专家与 worker
    python3 route.py 5013 --expert     # 只要专家名（R3 就这么用）
    python3 route.py --all             # 列出全部题号的映射

退出码：0 = 找到；1 = 未找到（说明该题还没派过专家，或记录已清理）
"""

from __future__ import annotations

import argparse
import json
import pathlib
import re
import sys

REPO_ROOT = pathlib.Path(__file__).resolve().parents[2]
RUNS_ROOT = REPO_ROOT.parent / "new_ROJ" / ".pi-subagents" / "runs"

PID_RE = re.compile(r"题号\s*\*\*(\d+)\*\*")


def role_of(agent: str) -> str:
    if "expert" in agent:
        return "expert"
    if "worker" in agent:
        return "worker"
    return "other"


def _text_of(rec: dict) -> str:
    m = rec.get("message") or rec
    c = m.get("content")
    if isinstance(c, str):
        return c
    if isinstance(c, list):
        return "\n".join(b.get("text", "") for b in c
                         if isinstance(b, dict) and b.get("type") == "text")
    return ""


def pid_from_session(sess: pathlib.Path) -> str | None:
    """从会话文件里取**第一条**含题号的用户消息 —— 那才是原始任务。

    ⚠ 不要用 run.json 的 promptText：它会被最近的 continue 消息**覆盖**，
    于是专家跑完 R3 之后，promptText 已变成「请写最终 index.md」（不含题号）。
    """
    try:
        text = sess.read_text(errors="replace")
    except OSError:
        return None
    for line in text.splitlines()[:60]:
        try:
            rec = json.loads(line)
        except json.JSONDecodeError:
            continue
        m = rec.get("message") or rec
        if m.get("role") != "user":
            continue
        mm = PID_RE.search(_text_of(rec))
        if mm:
            return mm.group(1)
    # 兜底：全文搜（子 agent 常在报告里重复题号）
    mm = PID_RE.search(text[:20000])
    return mm.group(1) if mm else None


def build_map() -> dict[str, dict[str, list[dict]]]:
    """扫全部 run.json，构造 {pid: {role: [ {name, run, spawn} ]}}。"""
    out: dict[str, dict[str, list[dict]]] = {}
    if not RUNS_ROOT.is_dir():
        return out
    for run_json in sorted(RUNS_ROOT.glob("*/run.json")):
        try:
            d = json.loads(run_json.read_text(errors="replace"))
        except (OSError, json.JSONDecodeError):
            continue
        for c in (d.get("children") or d.get("agents") or []):
            if not isinstance(c, dict):
                continue
            name = c.get("name")
            if not name:
                continue
            text = str(c.get("promptText") or "")
            m = PID_RE.search(text)
            if not m:
                # run.json 的 promptText 会被 continue 覆盖 —— 改从会话文件首条任务取
                sess = run_json.parent / f"{name}.jsonl"
                pid_guess = pid_from_session(sess) if sess.is_file() else None
                if pid_guess:
                    pid = pid_guess
                    agent = c.get("agent") or name
                    out.setdefault(pid, {}).setdefault(role_of(str(agent)), []).append({
                        "name": name,
                        "agent": agent,
                        "run": run_json.parent.name,
                        "spawn": c.get("spawnedAt") or "",
                        "state": c.get("state") or "",
                        "model": c.get("model") or "",
                    })
                continue
            pid = m.group(1)
            agent = c.get("agent") or name
            out.setdefault(pid, {}).setdefault(role_of(str(agent)), []).append({
                "name": name,
                "agent": agent,
                "run": run_json.parent.name,
                "spawn": c.get("spawnedAt") or "",
                "state": c.get("state") or "",
                "model": c.get("model") or "",
            })
    # 每个角色按时间排序，最新的在后
    for pid, roles in out.items():
        for r in roles.values():
            r.sort(key=lambda x: x["spawn"])
    return out


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("pid", nargs="?")
    ap.add_argument("--expert", action="store_true", help="只输出专家名字（供 R3 使用）")
    ap.add_argument("--all", action="store_true")
    args = ap.parse_args()

    m = build_map()

    if args.all:
        if not m:
            print("（没有任何映射 —— runs 目录为空？）")
            return 1
        print(f"{'pid':>7}  {'expert':<26} {'worker':<26}")
        print("-" * 64)
        for pid in sorted(m):
            ex = m[pid].get("expert") or []
            wo = m[pid].get("worker") or []
            print(f"{pid:>7}  {(ex[-1]['name'] if ex else '-'):<26} {(wo[-1]['name'] if wo else '-'):<26}")
        return 0

    if not args.pid:
        ap.error("需要 pid（或 --all）")

    pid = args.pid
    if pid not in m:
        print(f"⛔ 未找到 {pid} 的任何子 agent 记录", file=sys.stderr)
        print(f"   （runs 目录：{RUNS_ROOT}）", file=sys.stderr)
        return 1

    roles = m[pid]
    ex = roles.get("expert") or []
    wo = roles.get("worker") or []

    if args.expert:
        if not ex:
            print(f"⛔ {pid} 没有专家记录 —— 不能发 R3！", file=sys.stderr)
            return 1
        # 多条记录时取**最新**的那次（续跑会复用同一个 name）
        print(ex[-1]["name"])
        return 0

    print(f"题号 {pid}")
    for label, lst in (("专家（R3 发这里）", ex), ("worker（R2 发这里）", wo)):
        if not lst:
            print(f"  {label}: （无）")
            continue
        print(f"  {label}:")
        for r in lst:
            print(f"     {r['name']:<26} agent={r['agent']:<20} run={r['run']}  state={r['state']}")
            if r["model"]:
                print(f"       model={r['model']}")
    if ex and wo:
        print(f"\n  ⇒ R3 请用 name=\"{ex[-1]['name']}\"（专家）")
        print(f"  ⇒ R2 请用 name=\"{wo[-1]['name']}\"（worker）")
    return 0


if __name__ == "__main__":
    sys.exit(main())
