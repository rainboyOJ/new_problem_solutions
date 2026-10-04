#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-04-18 10:00
# update_at: 2026-04-18 10:00

import sys
from collections import deque


def longest_path(n: int, adj: list[list[tuple[int, int]]]) -> int | None:
    """求差分约束系统的最长路总和；若存在正权环则返回 None。"""
    dist = [0] * (n + 1)
    cnt = [0] * (n + 1)
    in_q = [False] * (n + 1)

    # 优先用栈（LIFO）检测正环，对差分约束卡常和判环极快
    stack = list(range(n, -1, -1))
    for u in stack:
        in_q[u] = True

    while stack:
        u = stack.pop()
        in_q[u] = False
        du = dist[u]

        for v, w in adj[u]:
            if dist[v] < du + w:
                dist[v] = du + w
                cnt[v] = cnt[u] + 1
                if cnt[v] > n:
                    return None
                if not in_q[v]:
                    stack.append(v)
                    in_q[v] = True

    return sum(dist[1:])


def solve() -> None:
    input_data = sys.stdin.buffer.read().split()
    if not input_data:
        return
    it = iter(input_data)
    n = int(next(it))
    k = int(next(it))

    adj: list[list[tuple[int, int]]] = [[] for _ in range(n + 1)]

    for _ in range(k):
        x = int(next(it))
        a = int(next(it))
        b = int(next(it))
        if x == 1:
            adj[a].append((b, 0))
            adj[b].append((a, 0))
        elif x == 2:
            if a == b:
                print(-1)
                return
            adj[a].append((b, 1))
        elif x == 3:
            adj[b].append((a, 0))
        elif x == 4:
            if a == b:
                print(-1)
                return
            adj[b].append((a, 1))
        elif x == 5:
            adj[a].append((b, 0))

    # 超级源点 0：每个人至少分 1 个糖果，即 dist[i] >= dist[0] + 1
    # 倒序加边让栈先访问 1..n
    for i in range(n, 0, -1):
        adj[0].append((i, 1))

    total = longest_path(n, adj)
    print(-1 if total is None else total)


if __name__ == "__main__":
    solve()
