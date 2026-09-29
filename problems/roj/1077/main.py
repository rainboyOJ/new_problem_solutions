#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 17:42
# update_at: 2026-09-29 17:42

import sys


def digit_sum(value: int) -> int:
    """求一个正整数的十进制各位数字之和。"""
    return sum(map(int, str(value)))


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)  # 四位数的个数

    # divmod(x, 10) 依次给出 (x // 10, x % 10)：去掉个位的前缀，以及个位本身
    readings = (divmod(next(data), 10) for _ in range(n))

    # 个位 - 千位 - 百位 - 十位 > 0 ⟺ 个位 > 其余三位数字之和
    print(sum(digit_sum(rest) < units for rest, units in readings))


if __name__ == "__main__":
    solve()
