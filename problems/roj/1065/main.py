#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 16:58
# update_at: 2026-09-29 16:58

import sys


def solve() -> None:
    m, n = map(int, sys.stdin.buffer.read().split())
    first = m if m & 1 else m + 1   # 区间内第一个奇数：m 为偶数则右移一位
    last = n if n & 1 else n - 1     # 区间内最后一个奇数：n 为偶数则左移一位
    count = (last - first) // 2 + 1  # 奇数个数：等差数列项数，可能算出 0 项
    print((first + last) * count // 2)  # 等差数列求和公式；两因子恒一偶，整除无损


if __name__ == "__main__":
    solve()
