#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 21:32
# update_at: 2026-10-01 21:40

import sys
from collections import deque


def add_painter(best: list[int], limit: int, price: int, must_paint: int) -> list[int]:
    """让一个工匠（必刷 must_paint、一次最多刷 limit 块、每块 price）加入后，返回新的报酬表。

    best[j] 是已安排的工匠在「前 j 块木板」上能拿到的最大报酬。新表先继承 best：
    这个工匠不刷，或者刷的那一段不包含第 j 块木板。剩下的一种情况是「他刷的段右端正好是 j」，
    设左端为 k，k 必须满足 k <= must_paint（段要盖住必刷的那块）和 k >= j-limit+1（长度受限），
    收益为 best[k-1] + (j-k+1)*price = price*j + (best[k-1] - price*(k-1))。
    右边只有 price*j 随 j 变化，所以每块木板只需在窗口 m = k-1 ∈ [j-limit, must_paint-1] 里
    取 best[m] - price*m 的最大值；j 增大时窗口左端右移、右端不动，用单调队列维护即可。
    """
    n = len(best) - 1
    cur = best[:]                 # 先承接「不刷」和「刷的段不含第 j 块」两种可能
    window = deque()              # (best[m] - price*m, m)，值从队首到队尾单调递减
    for m in range(must_paint):   # 窗口右端恒为 must_paint-1，候选一次性入队
        value = best[m] - price * m
        while window and window[-1][0] <= value:
            window.pop()
        window.append((value, m))
    for j in range(must_paint, n + 1):
        while window and window[0][1] < j - limit:  # 从这些起点起刷，长度已超过 limit
            window.popleft()
        if window:
            brushed = window[0][0] + price * j
            if brushed > cur[j]:
                cur[j] = brushed
        if cur[j - 1] > cur[j]:                     # 「前 j 块」可退化成「前 j-1 块」
            cur[j] = cur[j - 1]
    return cur


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)

    fences: list[tuple[int, int, int]] = []  # (limit, price, must_paint)，即题面的 (L, P, S)
    for _ in range(m):
        limit, price, must_paint = next(data), next(data), next(data)
        fences.append((limit, price, must_paint))
    # 按 S 排序后，每个工匠刷的段都排在后面工匠要盖住的 S 之前，逐行 DP 才成立
    fences.sort(key=lambda fence: fence[2])

    best = [0] * (n + 1)
    for limit, price, must_paint in fences:
        best = add_painter(best, limit, price, must_paint)
    print(best[n])


if __name__ == "__main__":
    solve()
