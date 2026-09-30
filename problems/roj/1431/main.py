#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 09:58
# update_at: 2026-09-30 09:58

import sys
from heapq import heapify, heappop, heappush
from itertools import accumulate

SLOTS_PER_HOUR = 12  # 1 小时 = 60 分钟 = 12 个 5 分钟钓鱼段


def best_catch(first: list[int], dec: list[int], slots: int) -> int:
    """在 1..len(first) 号湖里钓满 slots 个 5 分钟段，最多能钓到多少条鱼。

    每湖"下一段的产量"以 (负产量, 衰减量) 入小根堆，弹堆顶即全局产量最高的湖：
    收下这一段后，该湖产量减自己的衰减量（下限 0）再回堆。各湖的产量序列都递减，
    依次取当前最大恰好取走合并后最大的 slots 项，就是最优的时间分配。
    """
    pool = [(-fish, drop) for fish, drop in zip(first, dec)]  # (负产量, 衰减量)
    heapify(pool)
    total = 0
    for _ in range(slots):
        neg, drop = heappop(pool)
        fish = -neg                       # 该湖这一段的产量
        total += fish
        heappush(pool, (-max(fish - drop, 0), drop))  # 同一湖下一段的产量
    return total


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    hours = next(data)
    first = [next(data) for _ in range(n)]     # 各湖第 1 个 5 分钟能钓到的鱼数
    dec = [next(data) for _ in range(n)]       # 每多钓一段比上一段减少的鱼数
    walk = [next(data) for _ in range(n - 1)]  # 湖 i→i+1 要花 5*T_i 分钟

    best = 0
    # 枚举最远走到哪个湖：一旦终点定了，路程时间就固定，剩下全部时间都能用来钓鱼
    for last, spent in enumerate(accumulate(walk, initial=0)):
        slots = SLOTS_PER_HOUR * hours - spent  # 剩余的 5 分钟钓鱼段数
        if slots <= 0:                          # 路程耗光了时间，更远的湖只会更亏
            break
        best = max(best, best_catch(first[:last + 1], dec, slots))
    print(best)


if __name__ == "__main__":
    solve()
