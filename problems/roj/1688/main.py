#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-07 15:30
# update_at: 2026-10-07 15:30

import sys
from collections import deque

UNREACHABLE = -1  # dist 里的哨兵：该点走不到 n（最短路长度必 >= 0，不会撞车）

# 类型别名（Python 3.12+ 的 type 语句），相当于 C++ 的 using / typedef
type Adj = list[list[tuple[int, int]]]  # 邻接表：adj[u] = [(邻居, 边颜色), ...]


def rev_bfs(adj: Adj, n: int) -> list[int]:
    """从 n 反向 BFS，返回每个点到 n 的最短边数（不可达为 UNREACHABLE）。"""
    dist = [UNREACHABLE] * (n + 1)
    dist[n] = 0
    q = deque([n])
    while q:
        u = q.popleft()
        for v, _color in adj[u]:
            if dist[v] == UNREACHABLE:  # 反向 BFS 首次到达即最短
                dist[v] = dist[u] + 1
                q.append(v)
    return dist


def ideal_path(adj: Adj, dist: list[int]) -> list[int] | None:
    """长度已被最短路钉死，逐层在“能走完剩余最短路”的出边里取最小颜色。

    返回 None 表示 1 走不到 n（dist[1] 是 UNREACHABLE），此时没有颜色序列。
    """
    total = dist[1]
    if total == UNREACHABLE:
        return None
    seq: list[int] = []
    seen = [False] * len(dist)  # 每个点至多入层一次，保证总扫描量 O(n + m)
    cur = [1]
    seen[1] = True
    while len(seq) < total:
        target = total - len(seq) - 1  # 下一层节点必须满足 dist == target
        # 本层所有可行出边的颜色里取最小，就是这一位能取到的最小值
        cmin = min(c for u in cur for v, c in adj[u] if dist[v] == target)
        seq.append(cmin)
        nxt: list[int] = []
        for u in cur:
            for v, c in adj[u]:
                on_best_edge = dist[v] == target and c == cmin  # 走它能续完剩余最短路
                if on_best_edge and not seen[v]:
                    seen[v] = True
                    nxt.append(v)
        cur = nxt
    return seq


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    out: list[str] = []
    T = next(data)

    for _ in range(T):
        n, m = next(data), next(data)
        adj: Adj = [[] for _ in range(n + 1)]
        for _ in range(m):
            a, b, c = next(data), next(data), next(data)
            if a == b:
                continue  # 自环不可能落在最短路上
            adj[a].append((b, c))
            adj[b].append((a, c))

        dist = rev_bfs(adj, n)
        seq = ideal_path(adj, dist)
        # 题面未定义不连通，约定输出 0 与空行；可达时输出长度与颜色序列
        out += ["0", ""] if seq is None else [str(len(seq)), ' '.join(map(str, seq))]

    print('\n'.join(out))


if __name__ == "__main__":
    solve()
