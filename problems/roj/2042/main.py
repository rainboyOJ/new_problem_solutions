#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 04:42
# update_at: 2026-10-01 04:47

import sys
from heapq import heapify, heappop, heappush


def nth_humble(primes: list[int], n: int) -> int:
    """返回质因数全部取自 primes 的正整数中第 n 小的那个（1 不算丑数）。"""
    # 每个素数 p_j 只管一条候选队列 a[0]*p_j, a[1]*p_j, ...；idx[j] 是它已用掉的乘数个数。
    idx = [0] * len(primes)
    a = [1]                                              # a[0]=1 只是乘数起点，本身不是丑数
    heap = [(p, j) for j, p in enumerate(primes)]        # 堆元素带 j，弹出后才知道该推进哪个素数
    heapify(heap)

    for _ in range(n):
        cur = heap[0][0]                                 # 堆顶是所有队列的最小候选 = 下一个丑数
        a.append(cur)
        while heap[0][0] == cur:                         # 打平的队列一起推进，否则下一轮会重复产出 cur
            _value, j = heappop(heap)
            idx[j] += 1
            heappush(heap, (a[idx[j]] * primes[j], j))   # 新候选引用刚生成的 cur，因而严格大于 cur

    return a[n]                                          # a[0] 是哨兵，第 n 个丑数正是 a[n]


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    k, n = next(data), next(data)
    primes = [next(data) for _ in range(k)]
    print(nth_humble(primes, n))


if __name__ == "__main__":
    solve()
