#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-07 22:29
# update_at: 2026-10-07 22:29

import sys
from bisect import bisect_right

type SegMap = dict[int, tuple[int, int]]  # 线段表：左端点 -> (右端点, 所在连通块的并查集代表元)

# 每个连通块内所有区间的并集是一段连续线段，线段表就是这些线段本身：
#   LEFTS 是存活线段的左端点升序表（唯一需要查找的结构）
#   SEG 是同一批线段的详情表，两张表用左端点对齐
#   PARENT / SIZE 是并查集，下标是区间编号
LEFTS: list[int] = []
SEG: SegMap = {}
PARENT: list[int] = []
SIZE: list[int] = []


def find(x: int) -> int:
    """区间编号 x 所在连通块的代表元（路径减半）。"""
    while PARENT[x] != x:
        PARENT[x] = PARENT[PARENT[x]]
        x = PARENT[x]
    return x


def union(a: int, b: int) -> None:
    """把两个区间所在的连通块合并成一个（按大小合并）。"""
    a, b = find(a), find(b)
    if a == b:
        return
    if SIZE[a] < SIZE[b]:
        a, b = b, a
    PARENT[b] = a
    SIZE[a] += SIZE[b]


def absorb(x: int, y: int, cnt: int) -> None:
    """把区间 (x,y)（编号 cnt）并进线段表：吸收所有与它正长度相交的线段。"""
    # 起点：跨过 x 的那条线段（左端点 <= x 且右端点 > x），否则第一条左端点 > x 的线段
    i = bisect_right(LEFTS, x)
    start = i - 1 if i > 0 and SEG[LEFTS[i - 1]][0] > x else i

    # 线段两两不相交，所以从起点起凡左端点 < y 的线段都跨过 x，逐条吸收
    nl, nr = x, y
    j = start
    while j < len(LEFTS) and LEFTS[j] < y:
        l = LEFTS[j]
        nl = min(nl, l)
        nr = max(nr, SEG[l][0])
        union(cnt, SEG[l][1])
        j += 1

    for l in LEFTS[start:j]:
        del SEG[l]
    LEFTS[start:j] = [nl]  # 被吸收的线段整段换成本次并出来的线段
    SEG[nl] = (nr, find(cnt))


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    PARENT.extend(range(n + 1))
    SIZE.extend([1] * (n + 1))

    cnt = 0                # 已加入的区间个数，也就是区间编号
    out: list[str] = []
    for _ in range(n):
        op, x, y = next(data), next(data), next(data)
        if op == 2:
            same_block = find(x) == find(y)  # 两个区间是否落在同一个连通块
            out.append("YES" if same_block else "NO")
            continue
        cnt += 1
        absorb(x, y, cnt)

    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    solve()
