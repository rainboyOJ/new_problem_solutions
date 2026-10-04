#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 16:10
# update_at: 2026-10-04 12:47

import sys

BOTH = 15  # 3 与 5 的最小公倍数：被 3 整除且被 5 整除 ⇔ 被 15 整除


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)  # 待判定的整数，可能为负数或 0
    # n 是 15 的倍数 ⇔ n % 3 == 0 且 n % 5 == 0；Python 负数取余结果仍非负，判定不受符号影响
    divisible = n % BOTH == 0
    print("YES" if divisible else "NO")


if __name__ == "__main__":
    solve()
