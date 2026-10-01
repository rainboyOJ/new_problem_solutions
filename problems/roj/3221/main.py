#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 02:46
# update_at: 2026-10-02 02:46

import sys

FREE = 0  # 右副本未匹配的哨兵；顶点编号从 1 开始，0 永远不会和真实顶点撞上


def find_augment(u: int, adj: list[list[int]], match_r: list[int], seen: list[bool]) -> bool:
    """从右副本一侧给左副本 u 找增广路：能腾出一个位置就返回 True。"""
    for v in adj[u]:
        if seen[v]:
            continue
        seen[v] = True                                        # 本轮已试过 v，不再重复访问
        if match_r[v] == FREE or find_augment(match_r[v], adj, match_r, seen):
            match_r[v] = u                                    # v 改配 u；原来占 v 的点已另找出路
            return True
    return False


def max_matching(n: int, adj: list[list[int]]) -> int:
    """匈牙利算法：依次为每个左副本找增广路，返回二分图最大匹配数。"""
    match_r = [FREE] * (n + 1)
    matched = 0
    for u in range(1, n + 1):
        if find_augment(u, adj, match_r, [False] * (n + 1)):
            matched += 1
    return matched


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    out: list[str] = []
    T = next(data)

    for _ in range(T):
        n, m = next(data), next(data)
        # 拆点建图：每条有向边 u → v 对应一条二分边 u_L — v_R（左管出边，右管入边）
        adj: list[list[int]] = [[] for _ in range(n + 1)]
        for _ in range(m):
            adj[next(data)].append(next(data))

        # 最小路径点覆盖 = 顶点数 - 最大匹配数
        out.append(str(n - max_matching(n, adj)))

    print('\n'.join(out))


if __name__ == "__main__":
    solve()
