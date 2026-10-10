#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 15:09
# update_at: 2026-10-08 15:09

import sys
from math import isqrt


def used_fireballs(hp: list[int], p: int, k: int) -> int:
    """伤害为 p 时清场所需的最少火球数，超过 k 立即返回 k+1（只关心是否可行）。

    火球只伤及自身与左侧，故从右往左贪心：位置 i 只受距离 j-i <= R 的右侧火球
    溅射，窗口 [i+1, i+R] 的三项和即可 O(1) 求出已受溅射
    (p - i*i)*sum_cnt + 2*i*sum_j - sum_j2；不足 m_i+1 就在 i 上补 ceil(缺/p) 个。
    """
    n = len(hp)
    r = isqrt(p - 1)  # 溅射伤害严格大于 0 的最远距离，p = 1 时为 0
    cnt = [0] * n
    sum_cnt = sum_j = sum_j2 = total = 0

    for i in range(n - 1, -1, -1):
        splash = (p - i * i) * sum_cnt + 2 * i * sum_j - sum_j2
        need = hp[i] + 1 - splash  # 血量变负才算死，累计伤害要到 hp[i] + 1
        c = (need + p - 1) // p if need > 0 else 0
        total += c
        if total > k:
            return k + 1
        cnt[i] = c

        # r == 0（即 p == 1）时溅射半径为 0，左侧怪物吃不到任何伤害，窗口恒为空：
        # 既不弹出也不加入，否则 p = 1 会被误判成不可行。
        if r:
            # 窗口由 [i+1, i+r] 移到下一位置的 [i, i-1+r]：先弹掉距离恰为 r+1 的 i+r
            creep = i + r
            if creep < n:
                cr = cnt[creep]
                sum_cnt -= cr
                sum_j -= cr * creep
                sum_j2 -= cr * creep * creep
            sum_cnt += c  # 再加入位置 i 的火球来源
            sum_j += c * i
            sum_j2 += c * i * i

    return total


def min_damage(hp: list[int], k: int) -> int:
    """二分最小的火球伤害 p，使清场所需火球数不超过 k。"""
    # 上界：只往最右怪物砸 1 个火球，p = max(hp)+1+(n-1)^2 时最左怪物的溅射
    # 也达到 p-(n-1)^2 = max(hp)+1，足以击杀它，故该上界必然可行。
    lo, hi = 1, max(hp) + 1 + (len(hp) - 1) ** 2
    while lo < hi:
        mid = (lo + hi) // 2
        if used_fireballs(hp, mid, k) <= k:
            hi = mid
        else:
            lo = mid + 1
    return lo


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, k = next(data), next(data)
    hp = [next(data) for _ in range(n)]
    print(min_damage(hp, k))


if __name__ == "__main__":
    solve()
