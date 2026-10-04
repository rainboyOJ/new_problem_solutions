#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 21:15
# update_at: 2026-09-29 21:21

from functools import cache
from itertools import count
from math import isqrt


@cache
def divisor_sum(n: int) -> int:
    """n 的真因数和（所有小于 n 的因子之和）。

    因子成对出现：若 d 是因子，则 n // d 也是；所以只枚举 d <= sqrt(n)，
    每对 (d, n // d) 各收一次。1 是 n >= 2 时必有的真因子，单独计入；
    n 是完全平方数时 sqrt(n) 是自己的搭档，`d * d != n` 保证它只算一次。
    """
    if n == 1:
        return 0
    low = [d for d in range(2, isqrt(n) + 1) if n % d == 0]
    return 1 + sum(low) + sum(n // d for d in low if d * d != n)


def solve() -> None:
    # 无输入。定义要求 a = sigma(sigma(a)) 且 a != sigma(a)；
    # 从小到大枚举 a，第一次命中的 a 就是较小者（若 b < a 早就以 b 为 a 命中了）。
    for a in count(2):
        b = divisor_sum(a)
        if b != a and divisor_sum(b) == a:
            print(a, b)
            break


if __name__ == "__main__":
    solve()
