#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 13:02
# update_at: 2026-10-01 13:02

import heapq
import sys
from itertools import groupby

INF = 1 << 60  # 链表两端哨兵的权值：大到永远不会被选中，从而禁止“反悔到边界外”


def same_sign_runs(a: list[int]) -> list[tuple[bool, int]]:
    """把序列压成 (是否为正段, 该段数值和) 的交替列表，0 直接丢弃。"""
    return [(sign, sum(run)) for sign, run in groupby((x for x in a if x), key=lambda x: x > 0)]


def min_merge_cost(path: list[int], t: int) -> int:
    """在路径上选 t 个两两不相邻的点，最小化权值和（堆 + 双向链表反悔）。

    path 交替排列“删掉一个正段”的代价与“并掉一个负段”的代价：一次操作占用一个点，
    相邻点互斥；取完 i 后把左右邻接进 i 并把权值改成 w[l]+w[r]-w[i]，
    再选它一次就等于反悔、改选两侧。
    """
    s = len(path)
    w = [INF, *path, INF]             # 下标 0 与 s+1 为哨兵
    prv = [0, *range(s), s]           # prv[0] 指回自己，反悔到左端时不会越界
    nxt = [*range(1, s + 2), s + 1]   # nxt[s+1] 同理指向自己
    dead = bytearray(s + 2)
    cost = 0
    heap = [(w[i], i) for i in range(1, s + 1)]
    heapq.heapify(heap)

    for _ in range(t):
        value, i = heapq.heappop(heap)
        while dead[i]:                # 已被左右邻居吞并的历史记录
            value, i = heapq.heappop(heap)
        cost += value
        left, right = prv[i], nxt[i]  # 相邻点与 i 互斥，只能合到一起再反悔
        dead[left] = dead[right] = 1
        w[i] = w[left] + w[right] - value
        prv[i], nxt[i] = prv[left], nxt[right]
        nxt[prv[left]] = prv[nxt[right]] = i
        heapq.heappush(heap, (w[i], i))

    return cost


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)
    a = [next(data) for _ in range(n)]

    runs = same_sign_runs(a)
    positive = [i for i, (sign, _) in enumerate(runs) if sign]
    if m == 0 or not positive:        # 一段都取不了，或根本没有正段
        print(0)
        return

    total = sum(value for sign, value in runs if sign)  # 取走所有正段
    if len(positive) <= m:
        print(total)
        return

    lo, hi = positive[0], positive[-1]  # 首尾的负段并进来只会白亏，先剪掉
    # 正段记"删掉它的代价"，负段记"并过它的代价"，于是问题变成路径上取 T 个互不相邻的点
    path = [value if sign else -value for sign, value in runs[lo:hi + 1]]
    print(total - min_merge_cost(path, len(positive) - m))


if __name__ == "__main__":
    solve()
