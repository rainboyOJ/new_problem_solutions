#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 14:52
# update_at: 2026-09-30 14:52

import sys
from collections import deque

MOD = 100003  # 题面要求的取模值


def bfs_count(adj: list[list[int]], n: int) -> list[int]:
    """从顶点 1 出发 BFS，返回每个顶点被多少条最短路走到（对 MOD 取模）。"""
    dist = [-1] * (n + 1)  # -1 表示尚未访问，同时充当"层号"
    cnt = [0] * (n + 1)
    dist[1], cnt[1] = 0, 1

    queue = deque([1])
    while queue:
        u = queue.popleft()
        du, cu = dist[u], cnt[u]  # 出队时 cnt[u] 已收齐同一层全部前驱的贡献
        for v in adj[u]:
            if dist[v] < 0:  # 第一次到达 v：这正是最短路，层号由 u 决定
                dist[v] = du + 1
                cnt[v] = cu
                queue.append(v)
            elif dist[v] == du + 1:  # v 与 u 同属"u 的下一层"，再多一条最短路
                cnt[v] = (cnt[v] + cu) % MOD

    return cnt[1:]


def solve() -> None:
    data = sys.stdin.buffer.read().split()
    it = iter(data)
    n, m = int(next(it)), int(next(it))

    adj: list[list[int]] = [[] for _ in range(n + 1)]
    for _ in range(m):
        u, v = int(next(it)), int(next(it))
        adj[u].append(v)
        adj[v].append(u)  # 无向图，两个方向都要存

    sys.stdout.write('\n'.join(map(str, bfs_count(adj, n))) + '\n')


if __name__ == "__main__":
    solve()
