#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-07 15:11
# update_at: 2026-10-07 15:11

import sys
from array import array
from collections.abc import Iterator
from heapq import heappop, heappush

INF = 1 << 60        # 距离哨兵：本题最长的最短路也不超过 2e5 * 1e9 = 2e14
SHIFT = 20           # 打包用：低 20 位专放点号（N ≤ 2e5 < 2^20），高位放距离
ID_MASK = (1 << SHIFT) - 1

# 类型别名（Python 3.12+ 的 type 语句），相当于 C++ 的 using / typedef
type Adj = list[array]   # 邻接表：adj[u] 是点 u 的「打包边」数组，一条边一个 8 字节整数


def read_graph(tokens: Iterator[int], n: int, m: int) -> Adj:
    """按题面格式读入 m 条无向边，建成邻接表 adj[1..n]。"""
    adj: Adj = [array('q') for _ in range(n + 1)]
    for _ in range(m):
        s, t, d = next(tokens), next(tokens), next(tokens)
        if s == t:
            continue                                     # 自环对最短路没有贡献（样例里就有 2 2 0）
        adj[s].append((d << SHIFT) | t)                  # 无向边：正反各挂一次
        adj[t].append((d << SHIFT) | s)
    return adj


def shortest_path(adj: Adj, n: int) -> int:
    """堆优化 Dijkstra：回答「点 1 到点 n 的最短距离是多少」。

    堆里把 (距离, 点号) 打包成一个整数，低位留给点号，于是整数序就是距离序，
    省掉元组比较，也省掉元组的额外内存。每个点只在第一次出堆时定稿，
    同一个点的过期堆项直接跳过，因此不需要 decrease-key；点 n 定稿即可返回。
    """
    dis = [INF] * (n + 1)       # dis[u] 是当前已知的 1 到 u 的最短距离
    dis[1] = 0
    settled = bytearray(n + 1)  # settled[u] = 1 表示 u 的距离已经定稿
    heap = [1]                  # 源点：距离 0、点号 1

    while heap:
        item = heappop(heap)
        u = item & ID_MASK
        if settled[u]:
            continue            # 过期堆项：u 已经用更短的距离定稿过
        settled[u] = 1
        d = item >> SHIFT
        if u == n:
            return d            # 点 n 定稿，堆里剩下的距离都不可能更小
        for edge in adj[u]:
            v = edge & ID_MASK
            nd = d + (edge >> SHIFT)                     # 先经 u、再走这条边到 v 的距离
            if nd < dis[v]:
                dis[v] = nd
                candidate = (nd << SHIFT) | v            # 把新的 (距离, 点号) 压回堆
                heappush(heap, candidate)

    return dis[n]               # 图保证连通，这里只是兜底


def solve() -> None:
    """读入图、调用 Dijkstra、输出 1 到 n 的最短距离。"""
    # 分词这一层逐行 readline 惰性产出，取值仍然一律走 next() 顺序消费（见 read_graph）。
    # 不用 read().split()：本题输入最大 9MB，一次性读会把上百万个 bytes 对象同时留在
    # 内存里（实测峰值 129MB，已超 128MB 限制），逐行读取只要 55MB。
    tokens = (int(t) for line in iter(sys.stdin.buffer.readline, b"") for t in line.split())
    n, m = next(tokens), next(tokens)
    print(shortest_path(read_graph(tokens, n, m), n))


if __name__ == "__main__":
    solve()
