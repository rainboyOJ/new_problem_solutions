#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-05 21:47
# update_at: 2026-07-05 21:47

import math


def is_prime(n: int) -> bool:
    """判断 n 是否为素数。"""
    if n < 2:
        return False
    for i in range(2, int(math.isqrt(n)) + 1):
        if n % i == 0:
            return False
    return True


def solve() -> None:
    out: list[str] = []
    for x in range(10, 100):
        rev = x % 10 * 10 + x // 10  # 数字位置对换
        if is_prime(x) and is_prime(rev):
            out.append(str(x))
    print('\n'.join(out))


if __name__ == "__main__":
    solve()
