#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 19:05
# update_at: 2026-10-02 19:05

import sys

MOD = 10**9 + 7
M = 60  # lcm(4,5,6)：数位和只要模 60，就能判断是否被 4/5/6 中某个数整除


def conv(a: list[int], b: list[int]) -> list[int]:
    """两个「数位和模 60 分布」的循环卷积：先累加、最后一次取模。"""
    acc = [0] * M
    for i, x in enumerate(a):
        if not x:
            continue  # 空档跳过，省掉一半内层循环
        for j, y in enumerate(b):
            if y:
                acc[(i + j) % M] += x * y
    return [v % MOD for v in acc]


def pow_dist(base: list[int], n: int) -> list[int]:
    """初始分布 base 做 n 次循环卷积（快速幂）：恰好 n 位的数位和模 60 分布。"""
    res = [1] + [0] * (M - 1)  # 单位元：0 位、数位和为 0
    while n:
        if n & 1:
            res = conv(res, base)
        base = conv(base, base)
        n >>= 1
    return res


def count_good(step: list[int], n: int) -> int:
    """恰好 n 位（允许前导零）的 k 进制数里，数位和被 4/5/6 整除的个数。"""
    dist = pow_dist(step, n)
    return sum(v for i, v in enumerate(dist) if i % 4 == 0 or i % 5 == 0 or i % 6 == 0) % MOD


def solve() -> None:
    l, r, k = map(int, sys.stdin.buffer.read().split())

    # 一位数字 d（0 <= d < k）贡献的数位和增量 d mod 60：每个余数先摊 k//60 个，
    # 余下 k%60 个（即 0..k%60-1 这些余数）各再多一个。
    quota, extra = divmod(k, M)
    step = [quota + (1 if i < extra else 0) for i in range(M)]  # 60 项

    # l 位数到 r 位数 = 数值落在 [k^(l-1), k^r) 的数；高位补零到 r 位后数位和不变，
    # 于是答案 = 恰好 r 位的合法个数 - 恰好 l-1 位的合法个数（被减掉的是更短前缀）。
    print((count_good(step, r) - count_good(step, l - 1)) % MOD)


if __name__ == "__main__":
    solve()
