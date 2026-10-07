#!/usr/bin/env python3
"""对账：把子代理的实际结束状态与批次队列的 claimed 集合对上。

背景：本批次的派发靠 subagent 插件在子代理结束时回投通知，但通知可能漏投
（2026-10-07 roj/1353 的 worker 已 `execution: success` / `acceptance: accepted`，
父会话没收到通知，导致该题一直挂在 claimed 上、还差点被当成「文件已齐但未报告」）。

本脚本直接读插件的 run 台账（`.pi-subagents/runs/*/run.json`），从每个子代理的
任务文本里抽出题号，给出：

  - 每个已结束子代理的 execution / acceptance 状态
  - 队列里 claimed 但对应子代理**已结束**的题（= 漏投通知，需要父会话立刻验收）
  - 队列里 claimed 且对应子代理**仍在跑**的题（正常在飞）

用法：
    python3 scripts/problem-analysis-tools/reconcile_queue.py
    python3 scripts/problem-analysis-tools/reconcile_queue.py --queue .tmp/roj283-queue.jsonl
    python3 scripts/problem-analysis-tools/reconcile_queue.py --json
"""

from __future__ import annotations

import argparse
import json
import os
import pathlib
import re
import sys

REPO_ROOT = pathlib.Path(__file__).resolve().parents[2]
DEFAULT_QUEUE = REPO_ROOT / ".tmp" / "roj283-queue.jsonl"

# 插件把 run 台账放在会话 cwd 下。父会话的 cwd 是 new_ROJ（素材源仓库），
# 不是本仓库，所以这里同时试两个位置。
RUN_ROOTS = (
    REPO_ROOT.parent / "new_ROJ" / ".pi-subagents" / "runs",
    REPO_ROOT / ".pi-subagents" / "runs",
)

# 提示词有两种形态：老式直接写「题号 N」，新式让子代理读任务卡
# /tmp/roj283-cards/<pid>.md。两种都要能抽到题号。
PID_RE = re.compile(r"题号\s*(\d+)|roj283-cards/(\d+)\.md")


def collect_children() -> dict[str, list[dict]]:
    """返回 {pid: [该题的所有派发记录]}。

    同一题可能被重派多次（qiluyun 限速/超长推理导致的失败都会重派），所以必须
    保留全部记录：只看「最后一条」会把「已重派且新派发正在跑」的题误报成漏通知。
    """
    found: dict[str, list[dict]] = {}
    for root in RUN_ROOTS:
        if not root.is_dir():
            continue
        for run_dir in root.iterdir():
            run_json = run_dir / "run.json"
            if not run_json.is_file():
                continue
            try:
                payload = json.loads(run_json.read_text(encoding="utf-8"))
            except (json.JSONDecodeError, OSError):
                continue
            for child in payload.get("children", []):
                text = child.get("promptText") or payload.get("task") or ""
                match = PID_RE.search(text)
                if not match:
                    continue
                pid = next((g for g in match.groups() if g), None)
                if not pid:
                    continue
                execution = child.get("execution") or {}
                acceptance = child.get("acceptance") or {}
                found.setdefault(pid, []).append({
                    "pid": pid,
                    "name": child.get("name"),
                    "state": child.get("state"),
                    "execution": execution.get("status"),
                    "stopReason": execution.get("stopReason"),
                    "acceptance": acceptance.get("status"),
                    "runId": run_dir.name,
                    "model": child.get("model"),
                    "spawnedAt": child.get("spawnedAt"),
                })
    for records in found.values():
        records.sort(key=lambda r: r.get("spawnedAt") or "")
    return found


def main() -> int:
    parser = argparse.ArgumentParser(description="子代理结束状态 vs 队列 claimed 对账")
    parser.add_argument("--queue", default=str(DEFAULT_QUEUE))
    parser.add_argument("--json", action="store_true")
    args = parser.parse_args()

    queue_path = pathlib.Path(args.queue)
    if not queue_path.is_absolute():
        queue_path = REPO_ROOT / queue_path
    rows = [json.loads(line) for line in queue_path.read_text(encoding="utf-8").splitlines() if line.strip()]
    by_pid = {str(r["pid"]): r for r in rows}

    children = collect_children()

    silently_done: list[dict] = []   # claimed 但子代理已结束 → 漏通知，要立刻验收
    inflight: list[dict] = []        # claimed 且子代理还在跑
    unknown: list[dict] = []         # claimed 但找不到子代理记录

    for pid, row in by_pid.items():
        if row["status"] != "claimed":
            continue
        records = children.get(pid)
        if not records:
            unknown.append({"pid": pid, "title": row.get("title", "")})
            continue
        # 任一派发仍在跑 ⇒ 这道题在飞；否则取最后一次派发作为本轮结果
        # execution 可能是 None（还没落状态）或 "running"（进行中），两者都算在飞；
        # 只有 success/failed/truncated/aborted 这类终态才算已结束。
        in_flight_states = (None, "running")
        running = [r for r in records
                   if r.get("state") == "working" and r.get("execution") in in_flight_states]
        last = records[-1]
        entry = {"pid": pid, "title": row.get("title", ""), "attempts": len(records), **last}
        if running:
            entry["name"] = running[-1]["name"]
            entry["model"] = running[-1]["model"]
            inflight.append(entry)
        else:
            silently_done.append(entry)

    done_count = sum(1 for r in rows if r["status"] == "done")
    pending = sum(1 for r in rows if r["status"] == "pending")

    if args.json:
        print(json.dumps({
            "total": len(rows), "done": done_count, "pending": pending,
            "inflight": inflight, "silently_done": silently_done, "unknown": unknown,
        }, ensure_ascii=False, indent=1))
        return 1 if silently_done else 0

    print(f"队列 {len(rows)} 道：done {done_count} / pending {pending} / "
          f"claimed {len(inflight) + len(silently_done) + len(unknown)}")
    print(f"\n在飞 {len(inflight)} 路：")
    for e in sorted(inflight, key=lambda x: x["pid"]):
        print(f"  {e['pid']:>6}  {e['title'][:28]:<30} {e['name']:<24} {str(e.get('model')).split('/')[0]}")

    if silently_done:
        print(f"\n⚠️  子代理已结束但队列仍 claimed（{len(silently_done)} 道）——通知漏投，需要立刻验收：")
        for e in sorted(silently_done, key=lambda x: x["pid"]):
            print(f"  {e['pid']:>6}  {e['title'][:28]:<30} {e['name']:<24} "
                  f"state={e.get('state')} execution={e.get('execution')} "
                  f"stop={e.get('stopReason')} acceptance={e.get('acceptance')} "
                  f"(共派 {e.get('attempts')} 次)")
    else:
        print("\n✅ 没有漏投通知：所有 claimed 的题都还有子代理在跑")

    if unknown:
        print(f"\n❓ claimed 但找不到子代理记录（{len(unknown)} 道）：")
        for e in unknown:
            print(f"  {e['pid']:>6}  {e['title'][:28]}")

    return 1 if silently_done else 0


if __name__ == "__main__":
    sys.exit(main())
