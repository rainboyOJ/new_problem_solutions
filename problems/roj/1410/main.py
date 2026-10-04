#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-05 22:10
# update_at: 2026-07-05 22:10

import sys


def largest_prime_factor(n: int) -> int:
    """返回 n 的最大质因子：从小到大除尽因子，剩下的商就是答案。"""
    factor = 2
    while factor * factor <= n:
        if n % factor == 0:
            n //= factor                    # 除尽这个因子，保证剩下的商不含更小因子
        else:
            factor += 1 if factor == 2 else 2   # 2 之后只试奇数
    return n                                # 循环结束时商本身就是最大质因子


def solve() -> None:
    m, n = map(int, sys.stdin.buffer.read().split())

    print(','.join(str(largest_prime_factor(i)) for i in range(m, n + 1)))


if __name__ == "__main__":
    solve()
