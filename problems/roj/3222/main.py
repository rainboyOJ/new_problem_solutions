#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 03:02
# update_at: 2026-10-02 03:02

import sys
from collections import deque

Rect = tuple[int, int, int, int]  # 一张幻灯片的边界 (x_min, x_max, y_min, y_max)


def slides_covering(rects: list[Rect], point: tuple[int, int]) -> list[int]:
    """返回包含该点的幻灯片下标：编号可能落在哪些幻灯片上（二分图中该编号的邻接表）。"""
    x, y = point
    return [i for i, (x1, x2, y1, y2) in enumerate(rects) if x1 <= x <= x2 and y1 <= y <= y2]


def augment(match: list[int], i: int, adj: list[list[int]], seen: list[bool]) -> bool:
    """匈牙利增广：编号 i 能否沿交错路找到一个空幻灯片，找到则更新 match。"""
    for t in adj[i]:
        if seen[t]:
            continue
        seen[t] = True
        if match[t] == -1 or augment(match, match[t], adj, seen):
            match[t] = i
            return True
    return False


def can_swap(i: int, s: int, adj: list[list[int]], match: list[int]) -> bool:
    """删掉匹配边 (i, s) 后，编号 i 能否沿交错路绕回 s 重新落位：能则 (i, s) 不是必须边。"""
    seen = [False] * len(adj)
    queue = deque(t for t in adj[i] if t != s)  # 第一步不许再走被删的边
    for t in queue:
        seen[t] = True
    while queue:
        t = queue.popleft()
        j = match[t]                # 占用 t 的编号，沿匹配边走到它
        if s in adj[j]:
            return True             # j 腾退到 s、i 顶替 t：交错环成立
        for u in adj[j]:
            if not seen[u]:
                seen[u] = True
                queue.append(u)
    return False


def must_owner(adj: list[list[int]]) -> list[int | None]:
    """返回 owner[s] = 幻灯片 s 被唯一确定的编号，无法确定记为 None。

    必须边 (i, s) 含义：删掉它后不存在完美匹配，于是它出现在每个完美匹配中，
    各编号的必须边天然互不冲突，可以逐个登记后按幻灯片输出。
    """
    n = len(adj)
    match = [-1] * n                   # 幻灯片 -> 当前占用它的编号
    for i in range(n):
        augment(match, i, adj, [False] * n)
    if -1 in match:                    # 完美匹配不存在，任何幻灯片都无法确定
        return [None] * n

    # 编号 i 只有当前匹配边可能成为必须边：其余边都被这份匹配本身避开
    must: list[int | None] = [None] * n
    for i in range(n):
        s = match.index(i)             # 编号 i 当前占用的幻灯片
        if not can_swap(i, s, adj, match):
            must[i] = s                # 删掉后无法重排：每个完美匹配都含这条边

    owner: list[int | None] = [None] * n
    for i, s in enumerate(must):
        if s is not None:
            owner[s] = i
    return owner


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    out: list[str] = []
    heap_no = 0

    while (n := next(data)) != 0:
        heap_no += 1
        rects: list[Rect] = []
        for _ in range(n):
            rects.append((next(data), next(data), next(data), next(data)))
        points = [(next(data), next(data)) for _ in range(n)]  # 编号 1..n 的坐标

        adj = [slides_covering(rects, p) for p in points]
        owner = must_owner(adj)
        # 只输出能唯一确定的幻灯片；一个都确定不了才输出 none
        parts = [f"({chr(65 + s)},{owner[s] + 1})" for s in range(n) if owner[s] is not None]
        out += [f"Heap {heap_no}", " ".join(parts) if parts else "none", ""]

    print("\n".join(out))


if __name__ == "__main__":
    solve()
