#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-17 01:40
# update_at: 2026-10-20 16:20
#
# main.py：灾后重建。村庄按时间修复，询问某天只经过已修复村庄的最短路。
# 朴素做法是对每个询问重建图再跑一次 Floyd，代价 Q*N^3 必超时。
# 关键：Floyd 的中间点 middle 不是在“迭代次数”，而是在控制“允许使用的中转点集合”，
# 已经跑完 k 轮就代表允许经过前 k 批点中转。而村庄只会修复不会摧毁，
# 所以已开放集合只增不减 —— 这两件事结构相同，就把 middle 交给时间轴：
#   村庄按修复时间排好、询问按时间排好，用指针 activated 记录开放到哪，
#   每开放一个新村庄就让它当一次 middle，做一轮加点转移。
# N 个点全程各只当一次中间点，总代价 O(N^3 + Q)，而不是 O(Q*N^3)。
# 复用旧矩阵的前提是单调收紧：新增中转点只会让最短路变短或不变，
# 所以旧值恒为新值的上界，不会成为错误答案。

import sys

INF = 10**18  # 整数哨兵，比任何合法路径都大，无浮点比较问题


def solve() -> None:
    # 一次性读入全部整数再顺序消费：比逐行 input() 少大量 IO 与解析开销
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)

    ready = [next(data) for _ in range(n)]  # 题面保证 ready 非降序

    dist = [[INF] * n for _ in range(n)]
    for i in range(n):
        dist[i][i] = 0

    for _ in range(m):
        u, v, w = next(data), next(data), next(data)
        # 公路是双向的；题面保证任意两点之间只有一条路，不必取 min
        dist[u][v] = dist[v][u] = w

    activated = 0  # 已经放开到哪个村庄，值就是“下一次要用的 middle”
    answers: list[str] = []

    Q = next(data)
    for _ in range(Q):
        start, end, day = next(data), next(data), next(data)

        # 把重建时间不晚于今天、但还没当中间点用过的村庄依次放开。
        # 每放开一个就做一轮 Floyd 加点转移：允许经过它的路径可能更短。
        while activated < n and ready[activated] <= day:
            middle = activated
            through = dist[middle]  # dist[middle][*]，缓存行引用
            for x in range(n):
                row = dist[x]
                base = row[middle]  # dist[x][middle]
                if base == INF:
                    continue  # x 到 middle 不可达，这一轮对 x 没有改善
                for y in range(n):
                    candidate = base + through[y]
                    if candidate < row[y]:
                        row[y] = candidate
            activated += 1

        # 三种输出 -1 的情形合成一个判断：端点未修复 / 距离仍无穷
        value = dist[start][end]
        reachable = ready[start] <= day and ready[end] <= day and value < INF
        answers.append(str(value if reachable else -1))

    print("\n".join(answers))


if __name__ == "__main__":
    solve()
