#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 20:39
# update_at: 2026-09-30 20:39

import sys

MOD = 10**8  # 题面要求输出方案数除以 10^8 的余数


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    m, n = next(data), next(data)  # m 行 n 列
    cells = [next(data) for _ in range(m * n)]  # 行优先铺开的全部格子

    # 每行压成 n 位掩码：第 c 位为 1 表示该格肥沃可种草
    fertile = [
        sum(1 << c for c in range(n) if cells[r * n + c])  # 行内逐格置位
        for r in range(m)
    ]

    # 与肥沃度无关的公共候选：n 位内没有横向相邻 1 的掩码（含空掩码 0）
    valid = [s for s in range(1 << n) if not s & (s << 1)]

    dp = {0: 1}  # 逐行推进：上一行的种植掩码 -> 方案数；第 0 行上方视为空行
    for r in range(m):
        row_ok = [s for s in valid if not s & ~fertile[r]]  # 剔除落在贫瘠格上的掩码
        nxt: dict[int, int] = {}
        for prev, cnt in dp.items():
            for s in row_ok:
                if not s & prev:  # 与上一行同列不同时种草，杜绝纵向相邻
                    nxt[s] = (nxt.get(s, 0) + cnt) % MOD
        dp = nxt

    print(sum(dp.values()) % MOD)  # 末行任意掩码都合法，求和即总方案数


if __name__ == "__main__":
    solve()
