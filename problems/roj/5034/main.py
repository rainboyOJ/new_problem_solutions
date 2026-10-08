#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 22:40
# update_at: 2026-10-08 22:40

import sys
from collections.abc import Iterator


def prime_factors(n: int) -> Iterator[int]:
    """按从小到大产出 n 的全部质因子（含重复）。

    循环退出条件 d*d > n 说明 d 已试到 sqrt(n)：此时若剩余商 > 1 而是合数，
    它的质因子 q <= sqrt(n) 早该被除尽，矛盾，故剩余商必为素数，补产出一次。
    """
    d = 2
    while d * d <= n:
        while n % d == 0:  # 除尽因子 d，重复因子逐个产出
            yield d
            n //= d
        d += 1
    if n > 1:              # 剩余商必为素数，补打最后一个质因子
        yield n


def solve() -> None:
    """读入 n，输出 "n=p1*p2*...*pk"。"""
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data, None)
    if n is None:          # 空输入：不输出
        return
    print(f"{n}=" + "*".join(map(str, prime_factors(n))))


if __name__ == "__main__":
    solve()
