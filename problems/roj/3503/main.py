#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 04:16
# update_at: 2026-10-04 13:17

import sys

NEG = -10**9  # 不可达状态哨兵（权值全为正，真实答案恒 >= 0）


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)

    # 1-indexed 方格，四周留 0 边界，未填数的格子自然为 0
    grid = [[0] * (n + 2) for _ in range(n + 2)]
    for r, c, v in zip(data, data, data):
        if r == 0:  # "0 0 0" 是输入结束标记
            break
        grid[r][c] = v

    # cur[(r1, r2)]：两人同在斜线 k = 行+列 上、分别位于 (r1, k-r1)、(r2, k-r2) 时
    # 已取得的最大和；同格被两人同时踩到时只计一次（取过的格子变 0）
    cur = {(1, 1): grid[1][1]}  # 两条路径都从 A 出发
    for k in range(3, 2 * n + 1):  # 下一条斜线（A 点所在斜线 k=2 已定）
        nxt = {}
        lo, hi = max(1, k - n), min(n, k - 1)  # 行号合法区间：列 = k-行 也在 1..n
        for r1 in range(lo, hi + 1):
            g1 = grid[r1][k - r1]
            for r2 in range(lo, hi + 1):
                # 两人不同格各取一份，同格只取一份
                gain = g1 if r1 == r2 else g1 + grid[r2][k - r2]
                # 上一步两人各自只能从"正上方(行-1)"或"正左方(行不变)"走来
                best = max(cur.get((p1, p2), NEG) for p1 in (r1 - 1, r1) for p2 in (r2 - 1, r2))
                if best > NEG:  # 至少有一个前驱可达
                    nxt[r1, r2] = best + gain
        cur = nxt

    print(cur[n, n])  # 终点 B 所在斜线上只剩 (n, n) 一个状态


if __name__ == "__main__":
    solve()
