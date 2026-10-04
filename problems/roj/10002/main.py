#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 17:23
# update_at: 2026-10-02 17:23

import sys
from collections import Counter
from math import isqrt

# a_i ≤ 2×10⁹，而 p³ ≤ 2×10⁹ ⟺ p ≤ 1259：立方因子只可能来自这些素数
CUBE_PRIMES = [p for p in range(2, 1260) if all(p % d for d in range(2, isqrt(p) + 1))]  # 205 个


def kernel_pair(x: int) -> tuple[int, int]:
    """把性格值 x 拆成 (核, 补)：核是剥掉全部立方因子的 x，补使 核×补 恰为完全立方数。"""
    f = g = 1
    for p in CUBE_PRIMES:
        if x % p:
            if p * p > x:  # 更小的素数都除尽了，剩下的 x 只能是 1 或素数
                break
            continue
        e = 0
        while x % p == 0:  # 数清指数，顺便把 x 里的 p 除干净
            x //= p
            e += 1
        e %= 3  # 立方部分剥掉，核里只留对 3 取余的指数
        f *= p ** e
        if e:
            g *= p ** (3 - e)  # 补的指数补到 3，乘积里每个素因子的指数都是 3 的倍数
    # 收尾：剩余因子都 > 1259，x 只可能是 1、p、p²、p·q（p²q 已超过 2×10⁹）
    if x > 1:
        f *= x
        root = isqrt(x)
        g *= root if root * root == x else x * x  # p² 的补是 p；p 与 p·q 的补是各自的平方
    return f, g


def count_group(cnt: Counter[int], comp: dict[int, int]) -> int:
    """按互补核配对求和：每对取人数多的一侧，核为 1 的人两两冲突只能留 1 人。"""
    taken: set[int] = set()
    ans = 0
    for f, c in cnt.items():
        if f in taken:
            continue
        g = comp[f]  # comp 是对合：补的补还是 f，每对只在第一次遇到时结算
        taken.update((f, g))
        ans += 1 if f == 1 else max(c, cnt.get(g, 0))
    return ans


def solve() -> None:
    data = list(map(int, sys.stdin.buffer.read().split()))
    n = data[0]
    cnt: Counter[int] = Counter()
    comp: dict[int, int] = {}
    for a in data[1:n + 1]:
        f, g = kernel_pair(a)
        cnt[f] += 1
        comp[f] = g  # 同一个核的补唯一，重复赋值无害

    print(count_group(cnt, comp))


if __name__ == "__main__":
    solve()
