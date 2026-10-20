#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-17 01:40
# update_at: 2026-10-20 15:32
#
# main.py：传送门。只能装一对、把两栋楼之间距离变成 0，求安装后所有无序点对最短路之和的最小值。
# 全源最短路部分沿用 rbook 代码模板 floyed-py（《Floyd-Warshall 全源最短路》）：
#   点编号 1..n，floyd(n, edges) 返回 (n+1) 阶矩阵，INF 表示不可达，平行边只保留最小权值。
#
# 传送门等价于在 a、b 之间加一条权为 0 的双向边。不必为每个候选重跑 Floyd：
#   不用这条新边：原图边全在，距离仍是原矩阵的 d[x][y]（最优子结构，d 表直接复用）；
#   用这条新边：权为 0，所以多次经过可化简成一次，且传送门双向，只有两个方向。
# 于是新距离就是三个候选取最小：
#   d'[x][y] = min(d[x][y], d[x][a] + d[b][y], d[x][b] + d[a][y])
# 每对 (x,y) 只花 O(1)，整体 O(n^3) 一次 Floyd + O(n^4) 枚举。
# 注意：(a,b) 这一对本身也要计入总和，装传送门后它是 0。

import sys

INF = 1 << 60  # 哨兵，约 1.15e18，比任何合法路径都大

type Grid = list[list[int]]


def floyd(n: int, edges: list[tuple[int, int, int]]) -> Grid:
    """返回 n+1 阶距离矩阵；dist[0][*] 与 dist[*][0] 恒为 INF，不使用。"""
    dist: Grid = [[INF] * (n + 1) for _ in range(n + 1)]
    for i in range(1, n + 1):
        dist[i][i] = 0  # 自己到自己距离 0

    for u, v, w in edges:
        if w < dist[u][v]:  # 平行边保留最小权值
            dist[u][v] = w

    for k in range(1, n + 1):
        for i in range(1, n + 1):
            if dist[i][k] == INF:
                continue  # i 到中转点 k 不可达，松弛无意义
            for j in range(1, n + 1):
                if dist[k][j] == INF:
                    continue
                nd = dist[i][k] + dist[k][j]
                if nd < dist[i][j]:
                    dist[i][j] = nd
    return dist


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)

    edges: list[tuple[int, int, int]] = []
    for _ in range(m):
        u, v, w = next(data), next(data), next(data)
        # 无向边两个方向都要建；模板里按有向边处理，所以这里各加一次
        edges.append((u, v, w))
        edges.append((v, u, w))

    dist = floyd(n, edges)  # dist[i][j]：原图中 i 到 j 的最短路

    answer = INF
    for first in range(1, n + 1):
        for second in range(first + 1, n + 1):
            from_second = dist[second]
            from_first = dist[first]
            total = 0
            for x in range(1, n + 1):
                row = dist[x]  # 缓存行引用，内层只做一次二维访问
                left = row[first]  # d[x][a]，内层循环里不变
                right = row[second]  # d[x][b]，同理
                for y in range(x + 1, n + 1):
                    # 不用传送门 / 经 a->b / 经 b->a，三者取最小
                    total += min(row[y], left + from_second[y], right + from_first[y])
            if total < answer:
                answer = total

    print(answer)


if __name__ == "__main__":
    solve()
