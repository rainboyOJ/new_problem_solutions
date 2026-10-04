#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 19:22
# update_at: 2026-10-01 20:05

import sys
from operator import add

INF = 1 << 50  # "该站位不可达"的哨兵，加法不溢出即可


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    l = next(data)  # 位置数量 L
    n = next(data)  # 请求数量 N

    cost = [[next(data) for _ in range(l)] for _ in range(l)]  # c(i,j)
    req = [next(data) for _ in range(n)]                       # 请求序列 p_1..p_N

    # D[b][a]：一名服务员站在当前请求位 p（本轮前是 3），另两名站在 {a, b} 的最小花费。
    # 对称存储（D[b][a] == D[a][b]），且含 p 下标的格子恒为 INF（另两人不可能在 p）。
    p = 3  # 当前请求位（初始视为第 0 个请求发生在 3）
    big = INF * 2
    D = [[big] * l for _ in range(l)]
    D[0][1] = D[1][0] = 0

    for q in req:
        q1 = q - 1
        if q == p:
            continue  # 唯一合法动作是 p 处服务员原地接单，状态不变

        # ca[a] = c(a, q)：任何人被派去 q 的代价
        ca = [row[q1] for row in cost]
        cp = cost[p - 1][q1]
        p1 = p - 1

        # 转移一：p 处服务员去 q，另两人不动 → 新的"另两人"还是 {a, b}
        nD = [[x + cp for x in D[b]] for b in range(l)]
        nD[q1] = [big] * l          # 新请求位上恰有一人，另两人不能在 q
        for row in nD:
            row[q1] = big

        # 转移二：a 去接 q，b 与 p 处服务员留下 → 新的"另两人"是 {b, p}
        # b == q 时该动作非法（撞位），由转移三单独处理
        for b in range(l):
            if b == q1:
                continue
            best = min(map(add, D[b], ca))
            if best < nD[b][p1]:
                nD[b][p1] = best
                nD[p1][b] = best

        # 转移三：q 恰是另两人之一时，只有他原地接单（代价 0）→ 新的"另两人"是 {x, p}
        for x in range(l):
            v = D[x][q1]
            if v < nD[x][p1]:
                nD[x][p1] = v
                nD[p1][x] = v

        D = nD
        p = q

    print(min(min(row) for row in D))


if __name__ == "__main__":
    solve()
