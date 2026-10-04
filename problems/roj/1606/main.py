#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 21:29
# update_at: 2026-09-30 21:29

import sys
from itertools import accumulate


def min_cost(startup: int, prefix_t: list[int], prefix_c: list[int]) -> int:
    """前 n 个任务分批的最小总费用 f[n]（f[0] = 0，O(n^2)）。

    同一批任务同时完成，所以批 (j, i] 的启动费 startup 会推迟它自己以及后面
    所有批次里任务的完成时刻；把总费用按批次交换求和次序，批 (j, i] 的贡献就是
    (startup + 该批时间和) × (j 之后所有任务的费用系数和)，前缀和让两项都是 O(1)。
    """
    total_c = prefix_c[-1]
    n = len(prefix_t) - 1
    f = [0] * (n + 1)  # f[i]：前 i 个任务分批的最小总费用
    for i in range(1, n + 1):
        time_i = prefix_t[i]
        f[i] = min(
            f[j] + (startup + time_i - prefix_t[j]) * (total_c - prefix_c[j])
            for j in range(i)
        )
    return f[n]


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, startup = next(data), next(data)  # 任务数 n、每批启动时间 S
    tasks = [(next(data), next(data)) for _ in range(n)]  # 按题面结构成对消费：每个任务一行 (T_i, C_i)
    times = [t for t, _ in tasks]   # 各任务耗时 T_i，n 个
    fees = [c for _, c in tasks]    # 各任务费用系数 C_i，n 个
    prefix_t = list(accumulate(times, initial=0))   # n+1 个前缀和，下标 0 处为 0
    prefix_c = list(accumulate(fees, initial=0))
    print(min_cost(startup, prefix_t, prefix_c))


if __name__ == "__main__":
    solve()
