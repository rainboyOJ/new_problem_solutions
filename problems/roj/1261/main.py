#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 02:17
# update_at: 2026-09-30 02:17

import sys

INF = 10000005  # 不可达哨兵：费用非负、规模极小，真实答案到不了这个量级


def shortest(cost: list[list[int]]) -> tuple[int, list[int]]:
    """逆序 DAG 最短路 DP，返回 (从 1 到 n 的最短费用, 最短路径上的城市序列)。

    边只从编号小的城市指向编号大的城市（与配图中 A→E 的方向一致），
    所以从 n-1 倒着推到 0 时，所有后继的最优值都已算好——这正是逆拓扑序。
    f[i] 记「从 i 到终点 n 的最短费用」，go[i] 记最短路上 i 的下一站。
    """
    n = len(cost)
    f: list[int] = [INF] * n
    go: list[int] = [0] * n  # 下一站的城市编号（1 起），0 表示不可达或已是终点
    f[n - 1] = 0  # 终点到自身的费用为 0

    for i in range(n - 2, -1, -1):
        best, nxt = f[i], 0  # 保留 "没有更优后继" 的初值，回溯时靠 go=0 停止
        for j in range(i + 1, n):
            w = cost[i][j]
            if w and w + f[j] < best:  # 费用为 0 表示没有直通边；严格小于让平手时保序
                best, nxt = w + f[j], j + 1
        f[i], go[i] = best, nxt

    # 从 1 号城市沿 go 逐跳回溯，到终点（go 为 0）自然停下
    path: list[int] = [1]
    k = go[0]
    while k:
        path.append(k)
        k = go[k - 1]
    return f[0], path


def solve() -> None:
    nums = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(nums)  # 城市数量
    # N×N 费用矩阵：cost[i][j] 是 i→j 的直通费用，0 表示两点间没有直通边
    cost = [[next(nums) for _ in range(n)] for _ in range(n)]

    total, path = shortest(cost)
    print(f"minlong={total}")
    print(*path)


if __name__ == "__main__":
    solve()
