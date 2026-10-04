#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 22:30
# update_at: 2026-09-29 22:30

import sys


def parity_ordered(values: list[int]) -> list[int]:
    """重排序列：奇数从大到小在前，偶数从小到大在后。"""
    values.sort()                                 # 一次升序排序同时满足两类数的排序方向
    odds = [x for x in values if x & 1][::-1]     # 奇数取升序后反转，即从大到小
    evens = [x for x in values if not x & 1]      # 偶数保持升序，直接接在奇数后面
    return odds + evens


def solve() -> None:
    values = list(map(int, sys.stdin.buffer.read().split()))  # 一行 10 个数，空白切分即可
    print(*parity_ordered(values))


if __name__ == "__main__":
    solve()
