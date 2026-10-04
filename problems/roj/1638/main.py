#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 23:32
# update_at: 2026-09-30 23:32

import sys
from math import gcd

IMPOSSIBLE = "Impossible"  # 无解时的输出，单独命名避免散落在分支里


def min_jumps(n: int, d: int, x: int, y: int) -> int | None:
    """连跳 d 步首次落到 y 的最少次数；永远到不了则返回 None。

    跳 k 次后的位置是 (x + k*d) mod n，所以要求 k*d ≡ y-x (mod n)。
    设 g = gcd(d, n)：同余方程有解的充要条件是 g | (y-x)；
    否则两边同除以 g，得模 m = n/g 下唯一的同余类，
    乘上 d/g 的模逆元再对 m 取模，就是最小的非负跳跃次数。
    """
    g = gcd(d, n)
    if (y - x) % g:
        return None                                   # 差值不是 g 的倍数，无整数解
    m = n // g                                        # 约简后的模数，也是解的周期
    return (y - x) // g % m * pow(d // g, -1, m) % m   # pow(a, -1, m) 即 a 的模逆元


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    out: list[str] = []
    T = next(data)                                    # 测试数据组数

    for _ in range(T):
        n, d, x, y = next(data), next(data), next(data), next(data)
        jumps = min_jumps(n, d, x, y)
        out.append(IMPOSSIBLE if jumps is None else str(jumps))

    print('\n'.join(out))


if __name__ == "__main__":
    solve()
