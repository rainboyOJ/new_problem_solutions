#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-05 21:47
# update_at: 2026-07-05 21:47

import sys
import heapq


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)

    # 每个函数读成，每个函数当前只推进一个"指针"x
    fs = [(a, b, c) for a, b, c in zip(data, data, data)]  # n 个二次函数

    # 堆里放（函数值, 所属函数编号，当前自变量 x）：f 在 x≥1 上严格单调递增，
    # 所以每个函数只需保留最小的一个候选值 F_i(1)，弹出后再压入 F_i(x+1)。
    heap = [(a + b + c, i, 1) for i, (a, b, c) in enumerate(fs)]  # 初始 x = 1
    heapq.heapify(heap)

    out: list[int] = []
    for _ in range(m):
        v, i, x = heapq.heappop(heap)
        out.append(v)
        a, b, c = fs[i]
        x += 1  # 该函数下一个自变量
        heapq.heappush(heap, (a * x * x + b * x + c, i, x))

    print(*out)


if __name__ == "__main__":
    solve()
