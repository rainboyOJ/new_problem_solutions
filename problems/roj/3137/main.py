#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 19:44
# update_at: 2026-10-01 19:49

import sys
from itertools import accumulate
from operator import add


def level_cost(seq: list[int], values: list[int]) -> int:
    """把 seq 改成非降序列的最小代价，values 是允许使用的台阶高度（升序、已去重）。

    dp[j] = 处理完已扫过的前缀、且最后一个数恰好落在 values[j] 时的最小代价。
    扫描值域做前缀最小即可得到"结尾不超过 values[j] 的最优前缀"，无需 O(m) 内层循环。
    """
    dp = [0] * len(values)  # 未处理任何元素时取任何结尾都不花钱
    for a in seq:
        # accumulate(dp, min) 给出"结尾不超过 values[j]"的最优前缀；它和 |a - values[j]|
        # 逐列相加得到新一行。两个序列在 list(...) 里同时求值，读到的都是本行开始时的旧 dp。
        dp = list(map(add, (abs(a - v) for v in values), accumulate(dp, min)))
    return min(dp)  # 最后一个数允许落在任意台阶上


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    seq = [next(data) for _ in range(n)]
    values = sorted(set(seq))  # 关键性质：最优 B 的取值只需来自 A 中出现过的数

    best_nondecreasing = level_cost(seq, values)
    best_nonincreasing = level_cost(seq[::-1], values)  # 倒过来做非降 = 原序列非升
    print(min(best_nondecreasing, best_nonincreasing))


if __name__ == "__main__":
    solve()
