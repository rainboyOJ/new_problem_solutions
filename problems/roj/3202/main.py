#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 01:38
# update_at: 2026-10-02 01:38

import sys
from bisect import bisect_right
from math import dist

SECOND = 60  # 题面 T1 用秒、T2 用分钟、飞行时间也用分钟，这里统一折算成秒再比较


def slot_times(
    towers: list[tuple[int, int]],
    intruders: list[tuple[int, int]],
    t1: int,
    t2: int,
    v: int,
) -> list[list[float]]:
    """slot[j][i*m+k]：第 i 座塔第 k 次发射命中第 j 个入侵者的时刻（秒）。

    一次发射就是一个「发射位」，编码 i*m+k 表示「第 i 座塔的第 k 次发射」（k 从 0 起）。
    塔 i 第 k 次发射在第 (k+1)*T1 秒射出，此前每轮还要冷却 60*T2 秒；
    飞行时间为水平距离/V 分钟，即 60*距离/V 秒。
    """
    n, m = len(towers), len(intruders)
    ready = [[SECOND * dist(w, q) / v for q in intruders] for w in towers]  # 塔 i → 目标 j 的纯飞行时间
    shoot = [(k + 1) * t1 + k * SECOND * t2 for k in range(m)]             # 第 k 次发射的射出时刻
    return [[ready[i][j] + s for i in range(n) for s in shoot] for j in range(m)]


def max_matching(adj: list[list[int]], size: int) -> int:
    """匈牙利算法：左部是 m 个入侵者，右部是 size 个发射位，返回最大匹配数。

    每个入侵者只需被命中一次，所以左部每个点只要抢到一个发射位就算匹配成功。
    """
    match = [-1] * size

    def augment(u: int, seen: list[bool]) -> bool:
        for x in adj[u]:
            if not seen[x]:
                seen[x] = True
                if match[x] < 0 or augment(match[x], seen):
                    match[x] = u
                    return True
        return False

    matched = 0
    for u in range(len(adj)):
        if augment(u, [False] * size):
            matched += 1
        else:
            break  # 这个入侵者抢不到位，后面也补不上，直接判定不可行
    return matched


def minimum_time(slot_time: list[list[float]], m: int) -> float:
    """二分最小的可行截止时刻（秒）：答案一定是某个发射位的命中时刻。"""
    size = len(slot_time[0])
    order = [sorted(range(size), key=lambda s, j=j: slot_time[j][s]) for j in range(m)]
    by_time = [[slot_time[j][s] for s in order[j]] for j in range(m)]  # 与 order 同步的升序时刻表

    def feasible(deadline: float) -> bool:
        """在 deadline 之前（含）每个入侵者都能占到一个互不冲突的发射位。"""
        adj = [order[j][: bisect_right(by_time[j], deadline)] for j in range(m)]
        return max_matching(adj, size) == m

    timeline = sorted({t for row in slot_time for t in row})
    lo, hi = 0, len(timeline) - 1
    while lo < hi:
        mid = (lo + hi) // 2
        if feasible(timeline[mid]):
            hi = mid
        else:
            lo = mid + 1
    return timeline[lo]


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m, t1, t2, v = next(data), next(data), next(data), next(data), next(data)

    intruders = [(next(data), next(data)) for _ in range(m)]
    towers = [(next(data), next(data)) for _ in range(n)]

    answer = minimum_time(slot_times(towers, intruders, t1, t2, v), m)
    print(f"{answer / SECOND:.6f}")


if __name__ == "__main__":
    solve()
