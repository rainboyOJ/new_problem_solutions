#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 01:57
# update_at: 2026-10-02 01:57

import heapq
import sys
from collections import defaultdict
from collections.abc import Iterator

INF = float("inf")  # dist 里“还没到过”的哨兵


def neighbors(state: tuple[int, int], slots: list[int], top: int) -> Iterator[tuple[int, tuple[int, int]]]:
    """从状态 (楼层, 槽位) 出发，依次产出 (边权, 新状态)。

    扳槽只改槽位，走电梯只改楼层，所以邻边天然分两类。
    """
    floor, slot = state
    for j in range(len(slots)):  # 扳到槽 j：|槽差| 秒，电梯跟着动 |C_j| 层
        nf = floor + slots[j]
        if 1 <= nf <= top:
            yield abs(slot - j) + 2 * abs(slots[j]), (nf, j)


def shortest_time(slots: list[int], top: int) -> int:
    """从 (1 层, 初始槽) 到 N 层任意槽位的最短时间；到不了返回 -1。"""
    start = (1, slots.index(0))  # 手柄最初停在值为 0 的槽
    dist = defaultdict(lambda: INF)
    dist[start] = 0
    pq = [(0, start)]
    while pq:
        d, state = heapq.heappop(pq)
        if state[0] == top:  # 第一次弹出 N 层即最优
            return d
        if d > dist[state]:
            continue
        for w, nxt in neighbors(state, slots, top):
            if d + w < dist[nxt]:
                dist[nxt] = d + w
                heapq.heappush(pq, (d + w, nxt))
    return -1


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    m = next(data)  # 题面的 M
    slots = [next(data) for _ in range(m)]
    print(shortest_time(slots, n))


if __name__ == "__main__":
    solve()
