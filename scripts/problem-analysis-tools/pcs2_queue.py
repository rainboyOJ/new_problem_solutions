#!/usr/bin/env python3
"""pcs2-roj 长期批次的 JSONL 队列（主 agent 的派发约束）。

与 new_ROJ-tags 批次同款队列，唯一区别：init 按 roj index.md frontmatter 的
difficulty 分 cohort：simple（入门/普及-/普及）= 简化解析+补 main.cpp；
hard（其余）= 只补 main.cpp。roj 题目没有 config.json。

queue.jsonl 每行一道题，是唯一派发来源：
    {"pid": "1142", "path": "problems/roj/1142", "title": "单词的长度",
     "cohort": "simple", "status": "pending", "worker": null, "gen": 0,
     "note": "", "updated": "..."}

状态机：pending --claim--> claimed --done--> done
                     claimed --review--> review   claimed --fail--> failed
        review/failed --reset--> pending

约束语义：只能派发 claim 返回的题；验收后必须 done/fail 落账；崩溃/超时用
reset 回池；全部变更走本工具（flock + 原子写），禁止手改 queue.jsonl。

用法：
    pcs2_queue.py init [--root problems/roj]
    pcs2_queue.py claim --worker <name> --count <n> [--cohort simple|hard]
    pcs2_queue.py done <pid> [--evidence <path>]   # 证据：编译+样例+check 命令
    pcs2_queue.py review <pid> --reason "..."      pcs2_queue.py fail <pid> --reason "..."
    pcs2_queue.py reset <pid> [--all-claimed]      pcs2_queue.py stats   pcs2_queue.py show <pid>
"""

from __future__ import annotations

import argparse
import datetime
import fcntl
import json
import os
import pathlib
import re
import sys
import tempfile

REPO_ROOT = pathlib.Path(__file__).resolve().parents[2]
DEFAULT_QUEUE = REPO_ROOT / ".tmp" / "pcs2-queue.jsonl"
SIMPLE = {"入门", "普及-", "普及"}


def now() -> str:
    return datetime.datetime.now().strftime("%Y-%m-%dT%H:%M:%S")


class Queue:
    def __init__(self, path: pathlib.Path):
        self.path = path
        self.lock_path = path.with_suffix(".lock")

    def __enter__(self):
        self.lock_path.parent.mkdir(parents=True, exist_ok=True)
        self._lock = open(self.lock_path, "w")
        fcntl.flock(self._lock, fcntl.LOCK_EX)
        self.rows = self._read()
        return self

    def __exit__(self, *exc):
        self._lock.close()

    def _read(self) -> list[dict]:
        if not self.path.exists():
            return []
        rows = []
        for number, line in enumerate(self.path.read_text(encoding="utf-8").splitlines(), 1):
            if not line.strip():
                continue
            try:
                rows.append(json.loads(line))
            except json.JSONDecodeError as error:
                raise SystemExit(f"queue.jsonl 第 {number} 行不是合法 JSON：{error}")
        return rows

    def flush(self) -> None:
        self.path.parent.mkdir(parents=True, exist_ok=True)
        fd, tmp = tempfile.mkstemp(dir=str(self.path.parent), prefix=".queue-", suffix=".tmp")
        with os.fdopen(fd, "w", encoding="utf-8") as handle:
            for row in sorted(self.rows, key=lambda r: r["pid"]):
                handle.write(json.dumps(row, ensure_ascii=False) + "\n")
        os.replace(tmp, self.path)

    def get(self, pid: str) -> dict:
        for row in self.rows:
            if row["pid"] == pid:
                return row
        raise SystemExit(f"队列里没有 pid={pid}")

    def init(self, root: pathlib.Path) -> None:
        if self.rows:
            raise SystemExit(f"队列已有 {len(self.rows)} 行，拒绝覆盖；要重建请先删除文件")
        for md in sorted(root.glob("*/index.md")):
            text = md.read_text(encoding="utf-8")
            fm = re.match(r"^---\n(.*?)\n---\n", text, re.S)
            difficulty, title = "未知", ""
            if fm:
                dm = re.search(r"^difficulty:\s*[\"']?([^\"'\n]+)", fm.group(1), re.M)
                tm = re.search(r"^title:\s*[\"']?(.+?)[\"']?\s*$", fm.group(1), re.M)
                difficulty = dm.group(1).strip() if dm else "未知"
                title = tm.group(1).strip() if tm else ""
            has_main = (md.parent / "main.cpp").exists()
            self.rows.append({
                "pid": md.parent.name,
                "path": f"problems/roj/{md.parent.name}",
                "title": title,
                "difficulty": difficulty,
                "cohort": "simple" if difficulty in SIMPLE else "hard",
                "has_main": has_main,
                "status": "pending",
                "worker": None,
                "gen": 0,
                "note": "",
                "updated": now(),
            })
        self.flush()
        counts: dict[str, int] = {}
        for r in self.rows:
            counts[r["cohort"]] = counts.get(r["cohort"], 0) + 1
        print(f"初始化 {len(self.rows)} 题 -> {self.path}  cohort={counts}")


def cmd(args: argparse.Namespace) -> None:
    queue_path = pathlib.Path(args.queue).resolve()
    with Queue(queue_path) as q:
        if args.command == "init":
            root = pathlib.Path(args.root)
            if not root.is_absolute():
                root = REPO_ROOT / root
            q.init(root)
            return

        if args.command == "claim":
            if not args.worker:
                raise SystemExit("claim 需要 --worker")
            pool = [r for r in q.rows if r["status"] == "pending"]
            if args.cohort:
                pool = [r for r in pool if r["cohort"] == args.cohort]
            picked = pool[: args.count]
            for row in picked:
                row["status"] = "claimed"
                row["worker"] = args.worker
                row["gen"] += 1
                row["updated"] = now()
            q.flush()
            print(json.dumps({"claimed": picked}, ensure_ascii=False, indent=2))
            return

        if args.command == "show":
            print(json.dumps(q.get(args.pid), ensure_ascii=False, indent=2))
            return
        if args.command == "stats":
            counts: dict[str, int] = {}
            for r in q.rows:
                key = f"{r['status']}:{r['cohort']}"
                counts[key] = counts.get(key, 0) + 1
            print(json.dumps({"total": len(q.rows), "by_status_cohort": counts}, ensure_ascii=False, indent=2))
            return

        if args.command == "reset" and args.all_claimed:
            for r in q.rows:
                if r["status"] == "claimed":
                    r["status"], r["worker"] = "pending", None
                    r["updated"] = now()
            q.flush()
            print("已把全部 claimed 回池")
            return

        row = q.get(args.pid)
        if args.command == "done":
            if row["status"] not in ("claimed", "review"):
                raise SystemExit(f"只有 claimed/review 能 done，当前 {row['status']}")
            row["status"] = "done"
            row["has_main"] = True
            if args.evidence:
                row["note"] = f"evidence={args.evidence}"
        elif args.command in ("review", "fail"):
            if row["status"] != "claimed":
                raise SystemExit(f"只有 claimed 能 {args.command}，当前 {row['status']}")
            row["status"] = args.command
            row["note"] = args.reason or ""
        elif args.command == "reset":
            if row["status"] not in ("claimed", "review", "failed"):
                raise SystemExit(f"当前状态 {row['status']} 不需要回池")
            row["status"], row["worker"] = "pending", None
        row["updated"] = now()
        q.flush()
        print(f"{args.pid} -> {row['status']}")


def main() -> int:
    parser = argparse.ArgumentParser(description="pcs2-roj 批次 JSONL 队列")
    parser.add_argument("command", choices=["init", "claim", "done", "review", "fail", "reset", "show", "stats"])
    parser.add_argument("pid", nargs="?")
    parser.add_argument("--queue", default=str(DEFAULT_QUEUE))
    parser.add_argument("--root", default="problems/roj")
    parser.add_argument("--worker")
    parser.add_argument("--count", type=int, default=10)
    parser.add_argument("--cohort", choices=["simple", "hard"])
    parser.add_argument("--evidence")
    parser.add_argument("--reason")
    parser.add_argument("--all-claimed", action="store_true")
    args = parser.parse_args()
    if args.command in ("done", "review", "fail", "reset", "show") and not args.pid and not args.all_claimed:
        parser.error(f"{args.command} 需要 pid")
    cmd(args)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
