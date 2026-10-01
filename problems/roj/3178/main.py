#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 23:33
# update_at: 2026-10-01 23:33

import sys
from itertools import accumulate

INF = 10 ** 18  # “不可达”哨兵；真实答案不超过 N × 10000 = 3 × 10⁶，远小于它


def segment_cost(xs: list[int], pre: list[int], l: int, r: int) -> int:
    """把村庄 l..r（闭区间，按下标）全交给一个邮局时的最小距离和。

    坐标已升序，建在中位数的那个村庄上最优；左右两侧各自用前缀和一次算完。
    l > r 是空区间，返回 0。
    """
    mid = (l + r) // 2
    c = xs[mid]                                  # 中位数村庄的坐标
    left = c * (mid - l + 1) - (pre[mid + 1] - pre[l])
    right = (pre[r + 1] - pre[mid + 1]) - c * (r - mid)
    return left + right


def layer(dp: list[int], xs: list[int], pre: list[int], k: int) -> list[int]:
    """由“k-1 个邮局”的代价表 dp 推出“k 个邮局”的代价表 ndp[0..n]。

    ndp[i] = min_{j<i} dp[j] + cost(j, i-1)：前 j 个村庄交给 k-1 个邮局，
    第 k 个邮局负责剩下的 j..i-1 这一段。代价函数满足四边形不等式，
    所以最优分割点 j 随 i 单调不减，于是用分治把每层的 O(n²) 降成 O(n log n)。
    """
    n = len(xs)
    ndp = [INF] * (n + 1)

    def fill(lo: int, hi: int, opt_lo: int, opt_hi: int) -> None:
        """算 ndp[lo..hi]，已知这些位置的最优分割点都落在 [opt_lo, opt_hi]。"""
        if lo > hi:
            return
        mid = (lo + hi) // 2
        best, best_j = INF, opt_lo
        for j in range(opt_lo, min(mid - 1, opt_hi) + 1):
            value = dp[j] + segment_cost(xs, pre, j, mid - 1)
            if value < best:
                best, best_j = value, j
        ndp[mid] = best
        fill(lo, mid - 1, opt_lo, best_j)     # 左半边的最优分割点不超过 mid 的
        fill(mid + 1, hi, best_j, opt_hi)     # 右半边的最优分割点不小于 mid 的

    fill(k, n, k - 1, n - 1)
    return ndp


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, p = next(data), next(data)

    xs = sorted(next(data) for _ in range(n))  # 邮局只关心相对顺序，先排序
    pre = [0, *accumulate(xs)]                 # pre[i] = 前 i 个村庄的坐标和

    if p >= n:                                 # 邮局够多，每个村庄都建一个
        print(0)
        return

    dp = [INF] * (n + 1)                       # 0 个邮局：只有“前 0 个村庄”代价为 0
    dp[0] = 0
    for k in range(1, p + 1):
        dp = layer(dp, xs, pre, k)

    print(dp[n])


if __name__ == "__main__":
    solve()
