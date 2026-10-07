#!/usr/bin/env python3
"""验收：验证通过才落账，拒绝中间状态。

## 为什么需要它（2026-10-07 事故）

原来父会话的验收是一条 `&&` 链：

    check_new_analysis.py --realdata 1704 | tail -4 && pcs2_queue.py done 1704 ...

这里 `&&` 取的是 **`tail` 的退出码**（恒为 0），不是检查脚本的。结果 1704 的
`index.md` 有真实错误（`difficulty: "省选-"` 非法、缺 `favorite` / `favorite_reason`），
却被静默标成了 `done`，差点混进仓库。

管道吞退出码是这类事故的常见成因，所以这里把它包成一个原子操作：
**检查脚本只要报错，就绝不落账**，并且把完整错误原样打出来。

## 用法

    python3 scripts/problem-analysis-tools/accept.py 1704
    python3 scripts/problem-analysis-tools/accept.py 1684 1686 1690
    python3 scripts/problem-analysis-tools/accept.py --no-realdata 1704   # 只查契约，不跑数据
    python3 scripts/problem-analysis-tools/accept.py --dry-run 1704       # 只验证不落账

退出码：全部通过且已落账为 0；有任何一道不通过为 1。
"""

from __future__ import annotations

import argparse
import json
import pathlib
import subprocess
import sys

REPO_ROOT = pathlib.Path(__file__).resolve().parents[2]
TOOLS = REPO_ROOT / "scripts" / "problem-analysis-tools"
DEFAULT_QUEUE = REPO_ROOT / ".tmp" / "roj283-queue.jsonl"


def run(cmd: list[str]) -> tuple[int, str]:
    proc = subprocess.run(cmd, capture_output=True, text=True, cwd=str(REPO_ROOT))
    return proc.returncode, (proc.stdout or "") + (proc.stderr or "")


def main() -> int:
    parser = argparse.ArgumentParser(description="验证通过才落账的原子验收")
    parser.add_argument("pids", nargs="+")
    parser.add_argument("--queue", default=str(DEFAULT_QUEUE))
    parser.add_argument("--no-realdata", action="store_true",
                        help="只查四文件与 frontmatter 契约，不跑真实数据（快）")
    parser.add_argument("--dry-run", action="store_true", help="只验证，不写入队列")
    args = parser.parse_args()

    check_cmd = [sys.executable, str(TOOLS / "check_new_analysis.py")]
    if not args.no_realdata:
        check_cmd.append("--realdata")
    check_cmd += args.pids

    code, output = run(check_cmd)
    print(output.rstrip())

    passed = code == 0
    # 再确认一遍：即便退出码是 0，输出里也不该出现失败计数
    if "失败 0" not in output and "合计" in output:
        print("\n⚠️  输出里没有「失败 0」字样，出于保守不落账。")
        passed = False

    if not passed:
        print(f"\n⛔ 验收未通过（check_new_analysis 退出码 {code}），**不落账**。")
        print("   修好后再跑本脚本；不要手动 pcs2_queue.py done。")
        return 1

    if args.dry_run:
        print("\n✅ 验证通过（--dry-run，未落账）")
        return 0

    for pid in args.pids:
        done_code, done_out = run([
            sys.executable, str(TOOLS / "pcs2_queue.py"), "done", pid,
            "--evidence", "accept.py 验收通过（契约 + 真实数据）",
            "--queue", args.queue,
        ])
        print(done_out.rstrip())
        if done_code != 0:
            print(f"⛔ {pid} 落账失败（退出码 {done_code}）")
            return 1

    print(f"\n✅ {len(args.pids)} 道验收通过并已落账：{' '.join(args.pids)}")
    print("   下一步：git add 这些题目目录并提交。")
    return 0


if __name__ == "__main__":
    sys.exit(main())
