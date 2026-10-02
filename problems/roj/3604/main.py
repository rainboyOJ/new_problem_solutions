#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 10:05
# update_at: 2026-10-02 10:05

import sys


def count_digit(n: int, x: int) -> int:
    """统计 1..n 的十进制表示中数字 x 一共出现了多少次。"""
    total = 0
    p = 1  # 当前考察的数位权重：1 是个位，10 是十位，以此类推
    while p <= n:
        # 把 n 在这一位切成三段：高位 / 当前位 / 低位
        high, cur, low = n // (p * 10), n // p % 10, n % p

        # 当前位取值小于 x：前缀只能取 0..high-1，后缀任取 0..p-1
        total += high * p
        # 当前位取值与 x 的比较决定前缀恰好取 high 时的后缀范围
        if cur > x:
            total += p          # 后缀任取 0..p-1
        elif cur == x:
            total += low + 1    # 后缀只能取 0..low，再加上数 n 自己

        if x == 0:
            total -= p          # 前导零修正：前缀全 0 的“数”并不存在，刚才多算了一整段
        p *= 10
    return total


def solve() -> None:
    """读入 n 和 x，输出 x 在 1..n 中出现的次数。"""
    n, x = map(int, sys.stdin.buffer.read().split())
    print(count_digit(n, x))


if __name__ == "__main__":
    solve()
