#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 04:20
# update_at: 2026-10-08 04:20

import sys

# 值域上界：数列最大项 <= 1e16 + 1e12 * 1e4 = 2e16 < 2^55，所以只需枚举 55 个二进制位


def floor_sum(a: int, b: int, c: int, n: int) -> int:
    """Σ_{i=0}^{n} floor((a*i + b) / c)，类欧几里得递归，规模对数级衰减。"""
    if a == 0:
        return b // c * (n + 1)                      # 水平线，直接算
    if a >= c or b >= c:                             # 拆出斜率/截距的整数部分
        return (floor_sum(a % c, b % c, c, n)
                + n * (n + 1) // 2 * (a // c)
                + (n + 1) * (b // c))
    max_y = (a * n + b) // c                         # 斜率 < 1，转置坐标轴
    if max_y == 0:
        return 0
    return n * max_y - floor_sum(c, c - b - 1, a, max_y - 1)


def count_ones(a: int, b: int, n: int) -> int:
    """一组询问的答案：逐位累加等差数列各项二进制中该位为 1 的个数。"""
    limit = b + a * n                                # 数列最大项，决定枚举到哪一位
    ans = 0
    power = 1                                        # power = 2^k，即当前位的位权
    while power <= limit:
        # 第 k 位上 1 的个数 = Σ floor(x / 2^k) - 2 * Σ floor(x / 2^{k+1})
        ones_here = (floor_sum(a, a + b, power, n - 1)
                     - 2 * floor_sum(a, a + b, power * 2, n - 1))
        ans += ones_here
        power *= 2
    return ans


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    T = next(data)
    out: list[str] = []

    for _ in range(T):
        a, b, n = next(data), next(data), next(data)
        out.append(str(count_ones(a, b, n)))

    print('\n'.join(out))


if __name__ == "__main__":
    solve()
