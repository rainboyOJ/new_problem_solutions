#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 07:43
# update_at: 2026-09-30 07:43

import sys


def hierholzer(adj: dict[int, list[int]]) -> list[int]:
    """非递归 Hierholzer：求字典序最小的欧拉路径顶点序列。"""
    odd = [v for v in adj if len(adj[v]) % 2]        # 度为奇数的顶点
    # 有奇点时从最小的奇点出发（保证存在欧拉路径），否则全为偶点任取最小点
    start = min(odd) if odd else min(adj)
    for nbrs in adj.values():
        nbrs.sort()                                  # 每次贪心走最小的邻点 → 字典序最小
    stack, path = [start], []
    while stack:
        v = stack[-1]
        if adj[v]:                                   # 还有未走的边，继续往深处走
            u = adj[v].pop(0)                      # 取最小邻点；无向边两个方向同时删掉
            adj[u].remove(v)
            stack.append(u)
        else:
            u = stack.pop()
            path.append(u)
    return path[::-1]                                # 逆序弹出，反转得到路径


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    fences = next(data)                              # 栅栏数 F，即边数
    adj: dict[int, list[int]] = {}
    for _ in range(fences):
        u, v = next(data), next(data)
        adj.setdefault(u, []).append(v)
        adj.setdefault(v, []).append(u)

    print('\n'.join(map(str, hierholzer(adj))))


if __name__ == "__main__":
    solve()
