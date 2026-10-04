#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 22:43
# update_at: 2026-09-30 22:43

import sys
from math import isqrt

COLOR_PRIME = 1  # 珠宝价值本身是质数时用的颜色
COLOR_COMPOSITE = 2  # 珠宝价值是合数时用的颜色


def prime_table(limit: int) -> bytearray:
    """table[m] == 1 表示 m 是质数，覆盖 0 到 limit。

    埃氏筛：p 只需扫到 sqrt(limit)，命中质数时把它从 p*p 起的倍数整片涂 0
    （整片切片赋值，不在 Python 层写内层循环）。
    """
    table = bytearray(b"\x01") * (limit + 1)
    table[0:2] = b"\x00\x00"
    for p in range(2, isqrt(limit) + 1):
        if table[p]:
            table[p * p :: p] = bytes(len(range(p * p, limit + 1, p)))
    return table


def solve() -> None:
    n = int(sys.stdin.buffer.read().split()[0])  # 输入只有一行一个整数
    table = prime_table(n + 1)

    # 第 i 件珠宝的价值是 v = i + 1：质数涂 1 号色，合数涂 2 号色。
    colors = [COLOR_PRIME if table[v] else COLOR_COMPOSITE for v in range(2, n + 2)]

    # v = 2 与 v = 4 同色会冲突（2 是 4 的质因子），所以 n >= 3 时两种颜色都在用。
    count = 2 if n >= 3 else 1

    print(count)
    print(*colors)


if __name__ == "__main__":
    solve()
