#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-07 15:12
# update_at: 2026-10-07 15:12

import sys

INF = 10**16  # 不可达标记，与题面程序里的 f 同值；真实最短路的量级远小于它
MASK = (1 << 64) - 1  # C++ long long 的位宽，用来模拟它的溢出回绕
SIGN = 1 << 63        # 64 位整数的符号位

# 类型别名：邻接矩阵，Dist[i][j] 是 i 到 j 的当前最短距离（0 起下标）
type Dist = list[list[int]]


def wrap(x: int) -> int:
    """把结果折回 C++ long long 的 64 位有符号范围：题面程序用 ll 运算，Python 整数不溢出。"""
    x &= MASK
    return x - (1 << 64) if x >= SIGN else x


def relax_via(dis: Dist, k: int) -> None:
    """把中转点 k 放进允许集合：dis[i][j] 松弛到 min(dis[i][j], dis[i][k] + dis[k][j])。"""
    dk = dis[k]  # 第 k 行，本轮所有松弛都要用它
    # 只枚举 k 真正能到达的 j：边权可以为负，拿 dk[j] = INF 去加会得到
    # INF + 负数 < INF，等于把"不可达"当成一条超长的路写进 dis[i][j]
    reachable = [j for j, w in enumerate(dk) if w != INF]
    for row in dis:
        if row[k] == INF:
            continue  # 到不了中转点 k，这一轮 row 松弛不了任何点
        for j in reachable:
            nd = wrap(row[k] + dk[j])  # row[k] 不提前取：j == k 时这一格会被本循环改写
            if nd < row[j]:
                row[j] = nd


def floyd(dis: Dist) -> None:
    """就地求全源最短路：依次放开每个中转点，跑完 dis[i][j] 就是最短距离。"""
    for k in range(len(dis)):
        relax_via(dis, k)


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)

    dis: Dist = [[0 if i == j else INF for j in range(n)] for i in range(n)]  # Dis(i,i) = 0
    for _ in range(m):
        s, t, d = next(data) - 1, next(data) - 1, next(data)
        if d < dis[s][t]:
            dis[s][t] = d  # 有重边，只留最短的一条

    floyd(dis)

    # 照抄题面程序：逐对把 Dis(i,j) + f 异或进 S（不可达点对贡献 2f）
    S = 0
    for row in dis:
        for value in row:
            S ^= wrap(value + INF)
    print(S)


if __name__ == "__main__":
    solve()
