#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 09:32
# update_at: 2026-10-02 09:32

import sys
from collections.abc import Iterator
from itertools import accumulate


def read_ints() -> Iterator[int]:
    """逐行产出输入里的全部整数，避免一次性物化整份输入。"""
    for line in sys.stdin.buffer:
        yield from map(int, line.split())


def evaluate(limit: int, ores: list[tuple[int, int]], queries: list[tuple[int, int]]) -> int:
    """给定阈值 W = limit，用两组前缀和 O(n+m) 算出总检验值 y(W)。

    区间检验值 = 区间内 w >= W 的矿石块数 × 这些矿石的价值和，
    两组前缀和相减即得区间内的块数与价值和。
    """
    cnt = [0] + list(accumulate(w >= limit for w, _ in ores))                # 入选块数前缀和
    sv = [0] + list(accumulate(v if w >= limit else 0 for w, v in ores))     # 入选价值和前缀和
    return sum((cnt[r] - cnt[l - 1]) * (sv[r] - sv[l - 1]) for l, r in queries)


def min_gap(ores: list[tuple[int, int]], queries: list[tuple[int, int]], target: int) -> int:
    """二分第一个 y(W) <= target 的 W（分界点），答案只可能在它与前一个 W 取到。

    W 变大时入选矿石只减不增，y(W) 单调不增；越过 target 之后差值只会更大。
    """
    max_w = max(w for w, _ in ores)
    lo, hi = 1, max_w + 2   # hi 处已无矿石入选，y = 0 <= target，保证二分有分界点
    while lo < hi:
        mid = (lo + hi) // 2
        if evaluate(mid, ores, queries) > target:
            lo = mid + 1    # y 还太高，往右找
        else:
            hi = mid
    return min(abs(evaluate(w, ores, queries) - target) for w in (lo, lo - 1))


def solve() -> None:
    data = iter(read_ints())
    n, m, target = next(data), next(data), next(data)

    ores = [(next(data), next(data)) for _ in range(n)]      # (w_i, v_i)
    queries = [(next(data), next(data)) for _ in range(m)]   # [L_i, R_i]

    print(min_gap(ores, queries, target))


if __name__ == "__main__":
    solve()
