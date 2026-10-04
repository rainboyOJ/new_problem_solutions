#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 08:13
# update_at: 2026-10-02 08:13

import sys
from collections.abc import Iterator


def factorize(m1: int) -> dict[int, int]:
    """把 m1 分解质因数，返回 {质数: 指数}；m1 ≤ 30000，试除到 √m1 即可。"""
    factors: dict[int, int] = {}
    d = 2
    while d * d <= m1:
        while m1 % d == 0:
            factors[d] = factors.get(d, 0) + 1
            m1 //= d
        d += 1
    if m1 > 1:  # 剩下的大于 1 的部分本身就是一个质数
        factors[m1] = factors.get(m1, 0) + 1
    return factors


def seconds_needed(s: int, need: dict[int, int]) -> int:
    """细胞 s 每秒乘以自己，至少多少秒后 s^t 含有 need 里每个质数的全部指数。

    返回 -1 表示 s 缺某个质数，无论分裂多久都凑不齐。
    只需统计 s 中 m1 的那些质数的指数，其余大质因子与整除性无关。
    """
    steps = 0
    for p, e in need.items():
        cnt = 0  # s 中质数 p 的指数
        while s % p == 0:
            s //= p
            cnt += 1
        if cnt == 0:  # s 里没有 p，s^t 永远不含 p
            return -1
        # t 秒后 s^t 有 cnt*t 个 p，要求 cnt*t ≥ e，即 t = ceil(e / cnt)
        steps = max(steps, -(-e // cnt))
    return steps


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    m1, m2 = next(data), next(data)
    # M = m1^m2，每个质数的总需求指数 = m1 中的指数 × m2
    need = {p: e * m2 for p, e in factorize(m1).items()}

    ans = -1
    for _ in range(n):
        s = next(data)
        steps = seconds_needed(s, need)
        if steps >= 0 and (ans < 0 or steps < ans):
            ans = steps  # 所有能凑齐的细胞里取最早开始的时间
    print(ans)


if __name__ == "__main__":
    solve()
