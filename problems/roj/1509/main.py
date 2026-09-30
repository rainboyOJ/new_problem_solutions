#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 15:40
# update_at: 2026-09-30 15:40

import sys
from collections import deque


def spfa_longest(adj: list[list[tuple[int, int]]]) -> list[int]:
    """差分约束的最长路：dist[v] 是满足 dist[v] >= dist[u] + w 的最小可行解。

    所有 dist 初值 0 且全节点一起入队，等价于超级源点向每个点连 0 权边，
    一轮即可从所有点出发；c_i <= b_i - a_i + 1 保证图中无正环，队列必然收敛。
    """
    dist = [0] * len(adj)
    in_queue = [True] * len(adj)
    queue = deque(range(len(adj)))
    while queue:
        u = queue.popleft()
        in_queue[u] = False
        du = dist[u]  # 弹出时才读，保证用的是 u 的最新距离
        for v, w in adj[u]:
            if du + w > dist[v]:
                dist[v] = du + w
                if not in_queue[v]:
                    in_queue[v] = True
                    queue.append(v)
    return dist


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    intervals = [(next(data), next(data), next(data)) for _ in range(n)]

    hi = max(b for _, b, _ in intervals)  # 只建到最右端点：更右的位置选了也不贡献任何区间
    # 编号 = 坐标 + 1，让坐标 -1 也有节点：S(-1) 是全 0 的前缀基准
    adj: list[list[tuple[int, int]]] = [[] for _ in range(hi + 2)]
    for a, b, c in intervals:
        adj[a].append((b + 1, c))  # 节点 a 即坐标 a-1：S(b) >= S(a-1) + c
    for v in range(1, hi + 2):
        adj[v - 1].append((v, 0))    # S(坐标 v) >= S(坐标 v-1)：前缀不减
        adj[v].append((v - 1, -1))   # S(坐标 v-1) >= S(坐标 v) - 1：每个整数至多选一个

    dist = spfa_longest(adj)
    print(dist[hi + 1] - dist[0])  # S(max_b) - S(-1) = [0, max_b] 里被选中的整数个数


if __name__ == "__main__":
    solve()
