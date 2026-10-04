#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 07:05
# update_at: 2026-09-30 07:05

import sys
from math import prod


def closure(rules: list[tuple[int, int]]) -> list[set[int]]:
    """每个数字经任意次变换能变成的数字集合（含自身，即传递闭包）。"""
    reach = [{d} | {y for x, y in rules if x == d} for d in range(10)]
    for mid in range(10):                  # Floyd 思想：枚举中转数字 mid
        for d in range(10):
            if mid in reach[d]:            # d → mid 成立，则 mid 能到的 d 也能到
                reach[d] |= reach[mid]
    return reach


def solve() -> None:
    tokens = sys.stdin.buffer.read().split()
    n = tokens[0].decode()                 # n 当字符串读，逐位独立统计
    k = int(tokens[1])
    rules = [(int(tokens[2 + 2 * i]), int(tokens[3 + 2 * i])) for i in range(k)]

    reach = closure(rules)
    print(prod(len(reach[int(c)]) for c in n))  # 各位互不干扰，方案数相乘


if __name__ == "__main__":
    solve()
