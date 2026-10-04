#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 17:43
# update_at: 2026-09-29 17:48

import sys
from math import gcd


def solve() -> None:
    a, b, c = map(int, sys.stdin.buffer.read().split())

    # 同余条件 a%x == b%x == c%x ⇔ x 同时整除两个差 a-b 与 b-c
    diff_ab = a - b  # 题面的 a-b，等于 0 时对约束无贡献
    diff_bc = b - c  # 题面的 b-c，同理
    g = gcd(diff_ab, diff_bc) or 2  # 所有可行 x 的公约束；a=b=c 时为 0，任何 x>1 都可行，答案 2

    x = next(i for i in range(2, g + 1) if g % i == 0)  # g 的最小大于 1 的因子

    print(x)


if __name__ == "__main__":
    solve()
