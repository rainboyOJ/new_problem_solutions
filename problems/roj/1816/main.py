#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 06:24
# update_at: 2026-10-08 06:24
import sys

INSTANT = -1   # 哨兵：这堆可一步取空，先手取完即全局获胜


def pile_grundy(x: int, a: int, b: int) -> int:
    """化简后单堆的 SG 值；返回 INSTANT 表示该堆能一次取空、先手当场获胜。"""
    if a <= x <= b:               # 一步取空，直接赢下整局
        return INSTANT
    if x < a:                     # 取不动，死堆
        return 0
    if x < a + b:                 # 能一步压进 <a 的死区，且自身无法被直接取空
        return 1
    r = x % (a + b)               # 循环节 M = a+b 下的余数
    if a == 1:
        return r                  # a=1 时余数本身就是 SG 值
    if r < a:
        return 0
    if r >= b:                    # 等价于 r >= M-a：可一步压回死区
        return 1
    return 2 + (r - a) // a       # 中段余数需要额外 (r-a)/a 层托举


def alice_wins(xs: list[int], a: int, b: int) -> bool:
    """把所有堆的 SG 值异或起来：出现 INSTANT 堆或异或和非零即先手必胜。"""
    xor = 0
    for x in xs:
        g = pile_grundy(x, a, b)
        if g == INSTANT:
            return True
        xor ^= g
    return xor != 0


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    t = next(data)
    out: list[str] = []
    for _ in range(t):
        n, a, b = next(data), next(data), next(data)
        xs = [next(data) for _ in range(n)]
        out.append('Alice' if alice_wins(xs, a, b) else 'Bob')
    print('\n'.join(out))


if __name__ == "__main__":
    solve()
