#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-21 20:00
# update_at: 2026-10-21 20:00

import sys

INF = float("inf")  # 已加入城市的 dist 哨兵，让 min 扫描自动跳过它们


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    pairs = [(next(data), next(data)) for _ in range(n)]  # (x_i, y_i) 成对读入
    X = [px for px, _ in pairs]  # 题面的 x_i，下标 0..n-1 对应城市 1..n
    Y = [py for _, py in pairs]
    C = [next(data) for _ in range(n)]  # 建电站代价
    K = [next(data) for _ in range(n)]  # 拉线系数

    def wire_cost(i: int, j: int) -> int:
        """城市 i 与 j 之间拉线的代价：(k_i + k_j) * 曼哈顿距离。"""
        return (K[i] + K[j]) * (abs(X[i] - X[j]) + abs(Y[i] - Y[j]))

    # Prim：dist[i] 是城市 i 到已并入集合的最近边权，初始为“建电站”虚拟边 c_i。
    dist = C[:]
    source = [None] * n  # source[i]：dist[i] 这条边的另一端城市，None 表示建电站
    joined = [False] * n
    stations: list[int] = []
    connections: list[tuple[int, int]] = []
    for _ in range(n):  # 每轮并入一个城市，共 n 轮
        best = min(range(n), key=lambda i: INF if joined[i] else dist[i])
        joined[best] = True
        if source[best] is None:
            stations.append(best + 1)  # 树里挂在虚拟源点下：这个城市建电站
        else:
            connections.append((source[best] + 1, best + 1))
        for i in range(n):
            cost = wire_cost(best, i)  # 新点并入后用它刷新其余城市的最近距离
            if not joined[i] and cost < dist[i]:
                dist[i] = cost
                source[i] = best

    total = sum(C[s - 1] for s in stations) + sum(wire_cost(a - 1, b - 1) for a, b in connections)
    out = [str(total), str(len(stations)), " ".join(map(str, stations)), str(len(connections))]
    out += [f"{a} {b}" for a, b in connections]
    print("\n".join(out))


if __name__ == "__main__":
    solve()
