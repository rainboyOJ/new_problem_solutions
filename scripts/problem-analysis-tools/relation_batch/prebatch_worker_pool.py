#!/usr/bin/env python3
"""pre 批次 worker 池驱动器：回收 → 补位 → 启动 → 派题，一个「轮次」一次完成。

为什么需要它：本批的派发单元是「一个候选对一个全新 pi」，全量需要上千次启停。
手写 shell 循环容易出错（M1 试点期间曾因槽位状态被覆盖而重复派发），
因此把机械步骤集中到一个可复核的脚本里，并让状态更新只走 pre_batch.py 的
dispatch/collect/grounding 三个子命令。

用法：
    prebatch_worker_pool.py round --batch <batch> --workspace wN          # 一轮（8 槽）
    prebatch_worker_pool.py round --batch <batch> --workspace wN --n 4    # 只补 4 个槽
    prebatch_worker_pool.py status --batch <batch>                        # 只看状态
    prebatch_worker_pool.py finish --batch <batch>                        # 收工：退出全部 pi，槽位置空闲

每一轮的动作：
    1. collect + grounding（把已返回的结果并入台账与机检结论）
    2. 对每个槽位：若 pi 仍在运行 → ctrl+d 退出 → 确认 pane 回到 shell
    3. dispatch 取下一批待派任务（以 dispatch.jsonl 的 slot→task 映射为准）
    4. tab 改名 → 启动全新 pi（pre-<slot>-g<gen>）→ 发送任务书指针
    5. 保存状态

约束（与任务书一致）：worker 一律 pi --no-session；不创建下级 agent；
不使用长 --wait 派题；不关 tab（只 rename + 复用 pane）。
"""

from __future__ import annotations

import argparse
import json
import subprocess
import sys
import time
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))
import prebatch_lib as L  # noqa: E402

REPO = L.REPO_ROOT_DEFAULT
PRE = HERE / "pre_batch.py"
MISSING = "unknown option"


def herdr(*args: str, check: bool = False) -> tuple[bool, str]:
    r = subprocess.run(["herdr", *args], cwd=REPO, capture_output=True, text=True)
    out = (r.stdout or "") + (r.stderr or "")
    ok = r.returncode == 0 and MISSING not in out
    if check and not ok:
        raise SystemExit(f"herdr {' '.join(args)} 失败：{out.strip()[:300]}")
    return ok, out


def herdr_json(*args: str) -> dict | None:
    ok, out = herdr(*args)
    if not ok:
        return None
    try:
        return json.loads(out)
    except json.JSONDecodeError:
        return None


def state_path(batch: str) -> Path:
    return L.resolve_state_dir(REPO, batch) / "state.json"


def load_state(batch: str) -> dict:
    p = state_path(batch)
    return json.loads(p.read_text(encoding="utf-8")) if p.exists() else {}


def save_state(batch: str, st: dict) -> None:
    L.atomic_write_text(state_path(batch), json.dumps(st, ensure_ascii=False, indent=2))


def run_pre(*args: str) -> str:
    r = subprocess.run(["python3", "-B", str(PRE), *args], cwd=REPO, capture_output=True, text=True)
    return (r.stdout or "") + (r.stderr or "")


def panes_status() -> dict[str, tuple[str, str]]:
    """权威的 pane → (agent 名, 状态) 映射。

    state.json 里记的 agent 名可能滞后（回收/重启后未及时更新），
    因此判断「还有没有 worker 在跑」必须看 herdr 的实时视图，而不是 state.json。
    """
    d = herdr_json("agent", "list")
    out: dict[str, tuple[str, str]] = {}
    if not d:
        return out
    for a in ((d.get("result") or {}).get("agents") or []):
        pane, name, status = a.get("pane_id"), a.get("name"), a.get("agent_status")
        if pane and name:
            out[pane] = (name, status)
    return out


def pane_has_pi(pane: str) -> bool:
    d = herdr_json("pane", "process-info", "--pane", pane)
    if not d:
        return False
    procs = (d.get("result") or {}).get("process_info", {}).get("foreground_processes") or []
    return any(p.get("argv0") == "pi" for p in procs)


def agent_status(name: str) -> str | None:
    d = herdr_json("agent", "get", name)
    if not d:
        return None
    return ((d.get("result") or {}).get("agent") or {}).get("agent_status")


def stop_agent(name: str, pane: str, wait_s: float = 6.0) -> bool:
    """退出该槽位的 pi，确认 pane 回到 shell。返回 True 表示已干净。"""
    if agent_status(name) is not None:
        herdr("agent", "send-keys", name, "ctrl+d")
    else:
        # agent 名可能已失效（重启代次错位）→ 退化为直接对 pane 发送退出键
        herdr("pane", "send-keys", pane, "ctrl+d")
    deadline = time.time() + wait_s
    while time.time() < deadline:
        if not pane_has_pi(pane):
            return True
        time.sleep(0.7)
    # 一次 ctrl+d 可能只清了输入框（pi 的 app.exit 需要编辑器为空）
    if agent_status(name) is not None:
        herdr("agent", "send-keys", name, "ctrl+d")
    else:
        herdr("pane", "send-keys", pane, "ctrl+d")
    time.sleep(2.0)
    return not pane_has_pi(pane)


def start_agent(name: str, pane: str, model: str) -> bool:
    # `-ne` = --no-extensions：worker 不加载任何扩展，避免它们被 skill/扩展带偏。
    d = herdr_json("agent", "start", name, "--kind", "pi", "--pane", pane,
                   "--", "-ne", "--no-session", "--provider", model.split("/")[0],
                   "--model", model.split("/", 1)[1])
    if not d:
        return False
    a = (d.get("result") or {}).get("agent") or {}
    return bool(a.get("name") == name and a.get("interactive_ready"))


def remaining_pending(batch: str) -> int:
    st = load_state(batch)
    return sum(1 for v in (st.get("tasks") or {}).values() if v["status"] == "待派发")


def do_status(batch: str) -> None:
    st = load_state(batch)
    from collections import Counter
    print(f"gate: {json.dumps(st.get('gate', {}), ensure_ascii=False)}")
    print(f"pilot: {st.get('pilot', {}).get('status')}")
    print(f"tasks: {dict(Counter(v['status'] for v in (st.get('tasks') or {}).values()))}")
    print(f"usage: jev {st.get('usage', {}).get('jev', {}).get('cost_usd')} USD / "
          f"{st.get('usage', {}).get('jev', {}).get('requests')} requests")
    judged = len(L.read_jsonl(REPO / "relation-batches" / batch / "worker-results.jsonl"))
    pres = L.read_jsonl(REPO / "relation-batches" / batch / "prescreen-results.jsonl")
    print(f"prescreen: {sum(1 for r in pres if r.get('prescreen_pass'))} pass / {len(pres)} total")
    print(f"worker results: {judged}")
    print(f"待派发: {remaining_pending(batch)}")
    for slot, s in sorted((st.get("slots") or {}).items()):
        live = agent_status(s.get("agent", "")) if s.get("agent") else None
        print(f"  {slot}: {s.get('status')} gen={s.get('gen')} cand={s.get('candidate') or '—'} "
              f"agent={s.get('agent')} live={live}")


def do_round(batch: str, workspace: str, n: int, now: str,
             model: str = "small-sheep/deepseek-v4.1-flash", skip_collect: bool = False,
             parents: list[str] | None = None) -> None:
    st = load_state(batch)
    slots_cfg = st.get("slots") or {}
    if not slots_cfg:
        raise SystemExit("state.json 里没有 slots：先运行 gate slots 建立槽位")

    # 1) 收结果：collect + grounding（把已返回的并入台账）
    # 注意：collect/grounding 是子进程，它们会改写磁盘上的 state（任务状态、usage）。
    # 必须在它们之后重新加载 st，否则下面的 save_state 会把陈旧副本写回去，
    # 把 collect 的状态推进和预算计数覆盖掉（M2 实测 48 个任务被回退成“运行中”）。
    if not skip_collect:
        print("== collect / grounding ==")
        print(run_pre("collect", "--batch", batch, "--now", now).strip()[-300:])
        print(run_pre("grounding", "--batch", batch, "--now", now).strip()[-400:])
        st = load_state(batch)
        slots_cfg = st.get("slots") or {}

    # 2) 选空闲槽：pane 里没有 pi 才算空闲（不信任 state.json 的乐观状态）
    live = panes_status()
    free: list[str] = []
    for slot, s in sorted(slots_cfg.items()):
        pane = s.get("pane")
        if not pane:
            continue
        if pane in live:
            name, status = live[pane]
            s["agent"] = name  # 与实时视图对齐，避免 state.json 滞后
            # 流水线化后下一轮会在还有 worker 在跑时就开始：
            # 只能回收已经停下来的 agent，绝不能打断还在 working 的。
            # （否则每轮都把在跑的 worker 杀掉，任务反复派发——M2 实测 80 次误杀。）
            if status == "working":
                s["status"] = "占用"
                continue
            if stop_agent(name, pane):
                print(f"  {slot}: 旧 pi 已退出，pane 回到 shell")
            else:
                print(f"  {slot}: 旧 pi 未能干净退出 → 隔离，跳过本轮")
                s["status"] = "隔离"
                continue
        free.append(slot)
    free = free[:n]
    save_state(batch, st)
    if not free:
        print("没有可用槽位")
        return

    # 3) 生成任务（dispatch 是 slot→task 的唯一权威来源）
    print(f"== dispatch {len(free)} ==")
    disp = ["dispatch", "--batch", batch, "--now", now, "--n", str(len(free)),
            "--slots", ",".join(free)]
    if parents:
        disp += ["--parents", ",".join(parents)]
    out = run_pre(*disp)
    print(out.strip()[-800:])
    pairs = []
    for line in out.splitlines():
        if line.startswith("DISPATCH "):
            _, task_id, key, slot_field = line.split()[:4]
            pairs.append((slot_field.split("=", 1)[1], task_id, key))
    if not pairs:
        print("dispatch 没有产出新任务（待派发已空？）")
        return

    # 4) 启动并派题
    st = load_state(batch)
    for slot, task_id, key in pairs:
        s = st["slots"][slot]
        gen = int(s.get("gen") or 1) + 1
        name = f"{slot}-g{gen}"
        pane = s["pane"]
        if pane_has_pi(pane):
            print(f"  {slot}: pane 仍被占用，跳过 {task_id}")
            continue
        herdr("tab", "rename", s["tab"], f"{key.replace('/', '-').replace('->', '__')}"[:48])
        if not start_agent(name, pane, model):
            print(f"  {slot}: 启动 {name} 失败 → 标记隔离")
            s["status"] = "隔离"
            continue
        brief = f"relation-batches/{batch}/results/{task_id}/brief.md"
        prompt_text = (
            f"请完整阅读并严格按任务书执行：{brief} 。"
            f"你只写任务书指定的那一个结果文件（results/{task_id}/<attempt>.json），"
            "不要修改题目文件、不要运行 git、不要创建下级 agent。"
            "完成时输出一行 DONE <题对 key> <verdict>。"
        )
        herdr("agent", "prompt", name, prompt_text)
        s.update({"status": "占用", "gen": gen, "agent": name,
                  "candidate": key, "task_id": task_id})
        st["tasks"][task_id]["status"] = "运行中"
        print(f"  {slot}: {name} -> {key}")
    save_state(batch, st)


def do_finish(batch: str) -> None:
    st = load_state(batch)
    for slot, s in sorted((st.get("slots") or {}).items()):
        name, pane = s.get("agent"), s.get("pane")
        if name and pane and pane_has_pi(pane):
            ok = stop_agent(name, pane)
            print(f"  {slot}: {'已退出' if ok else '未能退出（隔离）'}")
            s["status"] = "空闲" if ok else "隔离"
        else:
            s["status"] = "空闲"
        s.update({"candidate": "", "task_id": ""})
    save_state(batch, st)
    print("worker 池已收工（tab 保留，供用户查看）")


def do_run(batch: str, workspace: str, n: int, rounds: int, cadence: float, now0: str,
           model: str, parents: list[str] | None, max_minutes: float) -> None:
    """连续跑若干轮：每轮收结果 → 补位派题 → 等 cadence 秒（≥180s 即 3 分钟巡检节奏）。"""
    from datetime import datetime, timedelta
    t0 = datetime.strptime(now0, "%Y-%m-%d %H:%M")
    deadline = time.time() + max_minutes * 60
    for r in range(1, rounds + 1):
        now = (t0 + timedelta(minutes=max(0, r - 1) * 4)).strftime("%Y-%m-%d %H:%M")
        print(f"\n########## round {r}/{rounds} @ {now} ##########", flush=True)
        do_round(batch, workspace, n, now, model, skip_collect=False, parents=parents)
        st = load_state(batch)
        pend = sum(1 for v in (st.get("tasks") or {}).values() if v["status"] == "待派发")
        busy = sum(1 for s in (st.get("slots") or {}).values() if s.get("status") == "占用")
        print(f"-- 待派发 {pend}，占用 {busy}", flush=True)
        if pend == 0 and busy == 0:
            print("队列已空，所有槽位空闲 → 停止", flush=True)
            break
        if time.time() > deadline:
            print("达到本次时间上限，停止（下轮可续）", flush=True)
            break
        # 等待本轮 worker 完成：轮询而不是固定 sleep。
        # 固定 cadence 会在 worker 还没写出结果时就把它们杀掉
        # （M2 早期误设 15s，导致 124 个任务被派发却无结果），因此这里按「是否仍在 working」等待。
        # 但只等「全部完成」会让先完成的槽位空等整轮（M2 实测约 43% 空闲）：
        # 一有 2 个以上空位就尽早开下一轮，把空等时间换成实际派发。
        wait_until = time.time() + max(cadence, 600)
        min_wait = time.time() + 90.0
        st_slots = load_state(batch).get("slots") or {}
        panes = [s["pane"] for s in st_slots.values() if s.get("pane")]
        while time.time() < wait_until:
            live = {pane: v for pane, v in panes_status().items()
                    if pane in panes and v[1] == "working"}
            if not live:
                break
            if time.time() >= min_wait and len(panes) - len(live) >= 2:
                print(f"  有 {len(panes) - len(live)} 个空位，提前开下一轮", flush=True)
                break
            time.sleep(15)
        else:
            print("  等待超时：仍有 worker 在跑，进入下一轮（会先收结果）", flush=True)


def main() -> None:
    ap = argparse.ArgumentParser(description="pre 批次 worker 池驱动器")
    sub = ap.add_subparsers(dest="cmd", required=True)
    p = sub.add_parser("round"); p.add_argument("--batch", required=True)
    p.add_argument("--workspace", default="wN"); p.add_argument("--n", type=int, default=8)
    p.add_argument("--now", required=True); p.add_argument("--model", default="small-sheep/deepseek-v4.1-flash")
    p.add_argument("--skip-collect", action="store_true")
    p.add_argument("--parents", default=None, help="逗号分隔的主标签，只派这些标签的分片")
    p.set_defaults(func=lambda a: do_round(a.batch, a.workspace, a.n, a.now, a.model, a.skip_collect,
                                          [x for x in (a.parents or "").split(",") if x] or None))
    p = sub.add_parser("run"); p.add_argument("--batch", required=True)
    p.add_argument("--workspace", default="wN"); p.add_argument("--n", type=int, default=8)
    p.add_argument("--rounds", type=int, default=5)
    p.add_argument("--cadence", type=float, default=600.0, help="等待本轮完成的最长秒数（默认 10 分钟，轮询检测）")
    p.add_argument("--now", required=True); p.add_argument("--model", default="small-sheep/deepseek-v4.1-flash")
    p.add_argument("--parents", default=None)
    p.add_argument("--max-minutes", type=float, default=25.0)
    p.set_defaults(func=lambda a: do_run(a.batch, a.workspace, a.n, a.rounds, a.cadence, a.now, a.model,
                                         [x for x in (a.parents or "").split(",") if x] or None,
                                         a.max_minutes))
    p = sub.add_parser("status"); p.add_argument("--batch", required=True)
    p.set_defaults(func=lambda a: do_status(a.batch))
    p = sub.add_parser("finish"); p.add_argument("--batch", required=True)
    p.set_defaults(func=lambda a: do_finish(a.batch))
    args = ap.parse_args()
    args.func(args)


if __name__ == "__main__":
    main()
