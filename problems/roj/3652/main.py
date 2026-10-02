#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-05 21:47
# update_at: 2026-07-05 21:47

import sys

INF = 10 ** 18


def solve() -> None:
    it = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(it), next(it)
    size = 1 << n

    g = [[INF] * n for _ in range(n)]  # g[u][v]：u,v 之间最短边长（重边取 min）
    for _ in range(m):
        u, v, w = next(it) - 1, next(it) - 1, next(it)
        if w < g[u][v]:
            g[u][v] = g[v][u] = w

    # mnd[S][v]：v 与已挖集合 S 之间最短一条边的长度（去掉 S 最低位后增量合并）
    mnd = [[INF] * n for _ in range(size)]
    for S in range(1, size):
        low = S & -S
        row_g, prev, row = g[low.bit_length() - 1], mnd[S ^ low], mnd[S]
        for v in range(n):
            wv, pv = row_g[v], prev[v]
            row[v] = wv if wv < pv else pv

    # 扩展表 extend[S] = [(T, wsum)]：T 是 S 的非空子集，且 T 中每个点都与
    # S\T 之间有边；wsum = 这些最短连接边的长度和（与挂在第几层无关）。
    # 直接按定义计算：内层枚举 T 的每一位累加 mnd，总工作量约 n·3^n。
    extend: list[list[tuple[int, int]]] = [[] for _ in range(size)]
    for S in range(1, size):
        wd: dict[int, int] = {}
        T = (S - 1) & S  # 从 S 的最大真子集开始降序枚举全部非空子集
        while T:
            total, ok, tt = 0, True, T
            row = mnd[S ^ T]  # T 中每个点都要接回 S\T
            while tt:
                v = (tt & -tt).bit_length() - 1
                wv = row[v]
                if wv == INF:  # 这个点接不回去，整个 T 非法
                    ok = False
                    break
                total += wv
                tt &= tt - 1
            if ok:
                wd[T] = total
            T = (T - 1) & S
        extend[S] = list(wd.items())

    full = size - 1
    masks_with = [[S for S in range(1, size) if S >> r & 1] for r in range(n)]

    ans = INF
    for r in range(n):  # 枚举赞助商免费打通、作为挖掘树根的宝藏屋
        dp_prev = [INF] * size  # dp[S]：挖开集合 S 的最小总代价（层数 ≤ 当前层）
        dp_prev[1 << r] = 0
        for k in range(2, n + 1):  # 第 k 层的新点都挂在第 k-1 层的点下
            dp_cur = dp_prev[:]  # 「最多 k 层」包含「更少层」的方案
            for S in masks_with[r]:
                new = dp_cur[S]
                for T, wsum in extend[S]:
                    if T >> r & 1:  # 新挖的点集不能包含早已免费打通的根
                        continue
                    base = dp_prev[S ^ T]
                    if base == INF:
                        continue
                    cost = base + wsum * (k - 1)  # 每条边的代价 = 边长 × 父结点深度
                    if cost < new:
                        new = cost
                dp_cur[S] = new
            if dp_cur == dp_prev:  # 这一层没有任何改进，更深的层也不会再有
                break
            dp_prev = dp_cur
        if dp_prev[full] < ans:
            ans = dp_prev[full]

    print(ans)


if __name__ == "__main__":
    solve()
