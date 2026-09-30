#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 02:00
# update_at: 2026-10-01 02:00

import sys

MOD = 10**8  # 题面要求的取模


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    m, n = next(data), next(data)

    # 每行的肥沃格位掩码：第 c 列肥沃则该位为 1
    fert = [sum(next(data) << c for c in range(n)) for _ in range(m)]

    # 无相邻 1 的掩码是行内种植的基础候选（s << 1 与 s 相交说明有水平相邻）
    no_adj = [s for s in range(1 << n) if s & (s << 1) == 0]

    # 每行真正可用的种植掩码：还必须是肥沃格的子集
    row_masks = [[s for s in no_adj if s & f == s] for f in fert]

    # dp：上一行种植掩码 -> 到上一行为止的方案数；第 0 行之前只有"全不种"
    dp = {0: 1}
    for masks in row_masks:
        # 上下两行不能同列种植：本行掩码 s 只能接在与其无公共位的 prev 之后
        dp = {s: sum(dp[t] for t in dp if t & s == 0) % MOD for s in masks}

    print(sum(dp.values()) % MOD)


if __name__ == "__main__":
    solve()
