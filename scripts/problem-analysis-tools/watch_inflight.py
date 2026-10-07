#!/usr/bin/env python3
"""在飞看门狗：找出「台账说在跑、其实已经死了」的子代理。

## 为什么需要它（2026-10-07 事故）

本批次的推进完全依赖 subagent 插件的完成通知：子代理结束 → 回投通知 → 父会话验收。
但通知只在子代理**正常结束**时发出。如果子代理中途撞上网络故障：

  - 一部分会落到 `stopReason: "error"`（如 `Connection error.`）后停住，不回投通知；
  - 另一部分停在 `stopReason: "toolUse"` 上等一个永远不返回的响应，会话文件就此不再增长。

两种情况台账里都还是 `state=working / execution=running`，看起来完全正常。
结果是：**10 路在飞子代理在 16:10–16:14 集体死掉，父会话空等了一个小时**才因为
用户追问「继续」而发现。

对账脚本 `reconcile_queue.py` 也查不出来 —— 它只比较「claimed 集合」与
「台账终态集合」，而死掉的子代理台账状态恰好就是在跑。

所以需要按**会话文件的最后写入时间**判断活性：会话文件长时间不增长 = 该子代理
不在推进。这是唯一可靠的活性信号。

## 判定

  - `idle > --stale-min`（默认 15 分钟）且未结束 ⇒ 判为停滞，退出码非 0
  - 台账是终态（success/failed/truncated/aborted/retired）⇒ 不算在飞，跳过

## 用法

    python3 scripts/problem-analysis-tools/watch_inflight.py
    python3 scripts/problem-analysis-tools/watch_inflight.py --stale-min 20
    python3 scripts/problem-analysis-tools/watch_inflight.py --json
    python3 scripts/problem-analysis-tools/watch_inflight.py --pid-filter 1684,1706
"""

from __future__ import annotations

import argparse
import json
import pathlib
import re
import sys
import time

REPO_ROOT = pathlib.Path(__file__).resolve().parents[2]

# 插件把 run 台账放在**会话 cwd** 下。父会话 cwd 是素材源仓库 new_ROJ，
# 但历史批次也可能落在本仓库，所以两处都扫；sessionFile 字段是绝对路径，
# 直接用它可以避免猜错目录。
RUN_ROOTS = (
    REPO_ROOT.parent / "new_ROJ" / ".pi-subagents" / "runs",
    REPO_ROOT / ".pi-subagents" / "runs",
)

# 提示词有两种形态：老式直接写「题号 N」，新式让子代理读任务卡
# /tmp/roj283-cards/<pid>.md。两种都要能抽到题号。
PID_RE = re.compile(r"题号\s*(\d+)|roj283-cards/(\d+)\.md")
IN_FLIGHT_EXECUTION = (None, "running")


def pid_from_match(match: re.Match | None) -> str:
    """两种提示词形态各有一个捕获组，返回非空的那个。"""
    if not match:
        return "?"
    return next((g for g in match.groups() if g), "?")


def collect_inflight() -> list[dict]:
    """扫台账，返回所有「未结束」的子代理记录。"""
    out: list[dict] = []
    seen: set[str] = set()
    for root in RUN_ROOTS:
        if not root.is_dir():
            continue
        for run_dir in sorted(root.iterdir()):
            run_json = run_dir / "run.json"
            if not run_json.is_file():
                continue
            try:
                payload = json.loads(run_json.read_text(encoding="utf-8"))
            except (json.JSONDecodeError, OSError):
                continue
            for child in payload.get("children", []):
                if child.get("state") != "working":
                    continue
                execution = child.get("execution") or {}
                if execution.get("status") not in IN_FLIGHT_EXECUTION:
                    continue
                session_file = child.get("sessionFile") or ""
                # 同一份台账可能被两个 root 扫到，按 sessionFile 去重
                key = session_file or f"{run_dir.name}/{child.get('name')}"
                if key in seen:
                    continue
                seen.add(key)

                text = child.get("promptText") or payload.get("task") or ""
                match = PID_RE.search(text)
                session_path = pathlib.Path(session_file) if session_file else None
                last_write = session_path.stat().st_mtime if (session_path and session_path.exists()) else None
                last_activity, stop_reason, errors, thinking_chars = probe_session(session_path)

                out.append({
                    "pid": pid_from_match(match),
                    "name": child.get("name"),
                    "runId": run_dir.name,
                    "model": child.get("model"),
                    "sessionFile": session_file,
                    "mtime": last_write or 0.0,
                    "idle_min": (time.time() - last_write) / 60 if last_write else None,
                    "lastActivity": last_activity,
                    "stopReason": stop_reason,
                    "errors": errors,
                    "thinkingChars": thinking_chars,
                })
    return out


def probe_session(session_path: pathlib.Path | None) -> tuple[str, str, int, int]:
    """读会话文件尾部，返回 (最后活动 ISO 时间, 最后一个 stopReason, 错误条数, 最大 thinking 字符数)。

    错误条数与 thinking 字符数是两个互补的报警信号：
      - 错误条数 > 0 且末尾 stopReason == "error" ⇒ 撞网络故障死了
      - thinking 字符数接近 10 万 ⇒ 正在撞输出上限，随时会被截断
    """
    if not session_path or not session_path.exists():
        return "", "", 0, 0
    try:
        lines = session_path.read_text(encoding="utf-8", errors="replace").splitlines()
    except OSError:
        return "", "", 0, 0

    last_ts = ""
    last_stop = ""
    errors = 0
    max_thinking = 0
    for line in lines:
        try:
            rec = json.loads(line)
        except json.JSONDecodeError:
            continue
        ts = rec.get("timestamp")
        if ts:
            last_ts = ts
        message = rec.get("message") or {}
        if message.get("role") != "assistant":
            continue
        last_stop = message.get("stopReason") or last_stop
        if message.get("errorMessage"):
            errors += 1
        content = message.get("content")
        if isinstance(content, list):
            for block in content:
                if isinstance(block, dict) and block.get("type") == "thinking":
                    max_thinking = max(max_thinking, len(str(block.get("thinking", ""))))
    return last_ts, last_stop, errors, max_thinking


def main() -> int:
    parser = argparse.ArgumentParser(description="在飞子代理活性看门狗")
    parser.add_argument("--stale-min", type=float, default=15.0,
                        help="会话文件超过这么多分钟没增长即判为停滞（默认 15）")
    parser.add_argument("--thinking-warn", type=int, default=60000,
                        help="单轮推理字符数超过此值即预警（默认 60000）")
    parser.add_argument("--pid-filter", default="",
                        help="只检查这些题号（逗号分隔）")
    parser.add_argument("--json", action="store_true")
    args = parser.parse_args()

    only = {p.strip() for p in args.pid_filter.split(",") if p.strip()}
    records = collect_inflight()
    if only:
        records = [r for r in records if r["pid"] in only]
    records.sort(key=lambda r: (r["idle_min"] is None, -(r["idle_min"] or 0)))

    stale = [r for r in records if r["idle_min"] is None or r["idle_min"] > args.stale_min]
    near_limit = [r for r in records if r["thinkingChars"] >= args.thinking_warn]

    if args.json:
        print(json.dumps({"inflight": len(records), "stale": stale, "near_limit": near_limit},
                         ensure_ascii=False, indent=1))
        return 1 if stale else 0

    print(f"在飞子代理 {len(records)} 路（停滞阈值 {args.stale_min:.0f} 分钟）：")
    if not records:
        print("  （没有在飞子代理）")
    for r in records:
        idle = "无会话文件" if r["idle_min"] is None else f"{r['idle_min']:6.1f} 分"
        flag = "⛔" if (r["idle_min"] is None or r["idle_min"] > args.stale_min) else "✅"
        extra = []
        if r["errors"]:
            extra.append(f"错误{r['errors']}条")
        if r["stopReason"]:
            extra.append(f"stop={r['stopReason']}")
        if r["thinkingChars"] >= args.thinking_warn:
            extra.append(f"推理{r['thinkingChars']}字符⚠")
        print(f"  {flag} {r['pid']:>6} {str(r['name']):<24} 空闲 {idle}  "
              f"{str(r['model']).split('/')[0]:<12} {' '.join(extra)}")

    if stale:
        print(f"\n⚠️  {len(stale)} 路停滞（会话文件 {args.stale_min:.0f} 分钟没增长）——"
              f"大概率已死，建议 retire 后重派：")
        for r in stale:
            print(f"     {r['pid']}  {r['name']}  runId={r['runId']}")
    if near_limit:
        print(f"\n⚠️  {len(near_limit)} 路推理接近输出上限（随时可能被截断）：")
        for r in near_limit:
            print(f"     {r['pid']}  {r['name']}  单轮推理 {r['thinkingChars']} 字符")
    if not stale and not near_limit:
        print("\n✅ 全部在正常推进")

    return 1 if stale else 0


if __name__ == "__main__":
    sys.exit(main())
