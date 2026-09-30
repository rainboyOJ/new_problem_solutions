#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-04-19 10:00
# update_at: 2026-04-19 10:00

import sys

NEG_INF = -10**18  # 强制不选或非法状态的惩罚权值


def trim_trees(n: int, val: list[int], to: list[int], deg: list[int]) -> tuple[list[int], list[int]]:
    """用拓扑排序把基环树外向树枝收缩到环上节点，返回每个节点的 (f0, f1) 权值。"""
    f0 = [0] * (n + 1)
    f1 = val[:]
    queue = [u for u in range(1, n + 1) if deg[u] == 0]
    head = 0

    while head < len(queue):
        u = queue[head]
        head += 1
        p = to[u]
        f0[p] += max(f0[u], f1[u])
        f1[p] += f0[u]
        deg[p] -= 1
        if deg[p] == 0:
            queue.append(p)

    return f0, f1


def solve_cycle(cycle: list[int], f0: list[int], f1: list[int]) -> int:
    """在单个环上做破环 DP，返回该基环树连通块的最大权独立集。"""
    # 方案 1: cycle[0] 强制不选
    dp0, dp1 = f0[cycle[0]], NEG_INF
    for u in cycle[1:]:
        dp0, dp1 = max(dp0, dp1) + f0[u], dp0 + f1[u]
    best_without_root = max(dp0, dp1)

    # 方案 2: cycle[0] 强制选，则 cycle[-1] 强制不选
    dp0, dp1 = NEG_INF, f1[cycle[0]]
    for u in cycle[1:]:
        dp0, dp1 = max(dp0, dp1) + f0[u], dp0 + f1[u]
    best_with_root = dp0

    return max(best_without_root, best_with_root)


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    try:
        n = next(data)
    except StopIteration:
        return

    val = [0] * (n + 1)
    to = [0] * (n + 1)
    deg = [0] * (n + 1)

    for i in range(1, n + 1):
        val[i] = next(data)
        h = next(data)
        to[i] = h
        deg[h] += 1

    f0, f1 = trim_trees(n, val, to, deg)

    ans = 0
    vis = [False] * (n + 1)
    for i in range(1, n + 1):
        if deg[i] > 0 and not vis[i]:
            cycle: list[int] = []
            curr = i
            while not vis[curr]:
                vis[curr] = True
                cycle.append(curr)
                curr = to[curr]
            ans += solve_cycle(cycle, f0, f1)

    print(ans)


if __name__ == "__main__":
    solve()
