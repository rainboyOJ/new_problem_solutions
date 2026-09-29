#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 21:38
# update_at: 2026-09-29 21:38

import sys
from functools import cache


@cache
def hermite(n: int, x: int) -> int:
    """返回 Hermite 多项式的值 h_n(x)，由 h_0=1、h_1=2x 两条边界递推。"""
    if n < 2:
        return 1 if n == 0 else 2 * x
    return 2 * x * hermite(n - 1, x) - 2 * (n - 1) * hermite(n - 2, x)


def solve() -> None:
    n, x = map(int, sys.stdin.buffer.read().split())
    value = hermite(n, x)
    # 输出恰好两位小数：x 是整数，h_n(x) 必为整数，拼接 ".00" 即可。
    # 不用 f"{value:.2f}"，那会先转成 float，大整数时会丢掉低位数字。
    print(f"{value}.00")


if __name__ == "__main__":
    solve()
