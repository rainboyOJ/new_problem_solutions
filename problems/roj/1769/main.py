#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 01:09
# update_at: 2026-10-08 01:09

import sys

INF = 10 ** 9  # 转移里"不可能"的代价，最大答案不超过列数 100

# 类型别名（Python 3.12+ 的 type 语句）：dp 表按 [行][列] 索引
type Grid = list[list[int]]


def compress(points: list[tuple[int, int]]) -> tuple[list[int], list[int], list[int]]:
    """列压缩：同一横坐标只留最高点，返回 (各列横坐标, 各列最高点的高度排名, 排名->高度)。

    矩形 [a,b] x [0,h] 覆盖点 (x,y) 当且仅当 a <= x <= b 且 y <= h，
    所以同一列里只有最高的点有用，矮点被它代表。
    """
    top: dict[int, int] = {}
    for x, y in points:
        if y > top.get(x, 0):  # 题面保证 y >= 1，所以 0 可以当"还没有点"的哨兵
            top[x] = y
    xs = sorted(top)
    hval = sorted(set(top.values()))
    rank_of = {h: r for r, h in enumerate(hval, 1)}  # 高度 -> 排名，1 最矮
    return xs, [rank_of[top[x]] for x in xs], hval


def min_rects(xs: list[int], rank: list[int], hval: list[int], S: int) -> int:
    """最少矩形数。状态 dp[k][i][j]：覆盖列 i..j 中高度排名 >= k 的点所需的最少矩形数。

    取最左的待覆盖列 i，覆盖它的最外层矩形底边是 [xs[i], xs[q]]，高度取宽度允许的最大值；
    该矩形把列 i..q 中高度不超过它的点全部吃掉，剩余点只可能是
      · 列 i..q 中更高的点 —— 由嵌在它内部的矩形处理，即 dp[ymx+1][i][q]；
      · 列 q+1..j 的点 —— 与它相离，即 dp[k][q+1][j]。
    于是 dp[k][i][j] = min_q ( g[i][q] + dp[k][q+1][j] )，g[i][q] = 1 + dp[ymx+1][i][q]。
    """
    n = len(xs)
    m = len(hval)
    ymx: Grid = [[m] * n for _ in range(n)]  # ymx[i][q]：底边 i..q 时允许的最大高度排名
    lim = [0] * n                            # lim[i]：仍盖得住第 i 列最高点的最大 q
    for i in range(n):
        h = m
        lim[i] = i
        for q in range(i + 1, n):
            while h and hval[h - 1] * (xs[q] - xs[i]) > S:
                h -= 1                       # 底边变宽，允许的高度只会更矮
            ymx[i][q] = h
            if h >= rank[i]:                 # 盖得住第 i 列最高点，它才配当最外层矩形
                lim[i] = q

    prev: Grid = [[0] * (n + 1) for _ in range(n + 1)]  # 第 k+1 层，初值即 dp[m+1] 全 0
    g: Grid = [[0] * n for _ in range(n)]               # g[i][q] = 1 + dp[ymx[i][q]+1][i][q]
    for k in range(m, 0, -1):
        for i in range(n):
            gi, yi = g[i], ymx[i]
            for q in range(i, lim[i] + 1):
                need_g = yi[q] == k          # 这一对的 ymx 正好是 k，用第 k+1 层补齐 g
                if need_g:
                    gi[q] = prev[i][q] + 1
        cur: Grid = [[0] * (n + 1) for _ in range(n + 1)]
        for i in range(n - 1, -1, -1):
            row, gi = cur[i], g[i]
            if rank[i] < k:                  # 第 i 列没有待覆盖的点：整列跳过
                nxt = cur[i + 1]
                for j in range(i, n):
                    row[j] = nxt[j]
                continue
            for j in range(i, n):
                best = INF
                for q in range(i, min(lim[i], j) + 1):
                    v = gi[q] + cur[q + 1][j]  # q+1 > j 时后一项是 0（空区间）
                    if v < best:
                        best = v
                row[j] = best
        prev = cur
    return prev[0][n - 1]                    # 第 1 层覆盖全部列


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    T = next(data)
    out: list[int] = []
    for _ in range(T):
        n, S = next(data), next(data)
        points = [(next(data), next(data)) for _ in range(n)]
        xs, rank, hval = compress(points)
        out.append(min_rects(xs, rank, hval, S))
    print('\n'.join(map(str, out)))


if __name__ == "__main__":
    solve()
