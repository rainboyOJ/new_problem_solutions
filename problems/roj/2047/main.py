#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-05 21:47
# update_at: 2026-07-05 21:47

import sys
from functools import cache


@cache
def count_valid(length: int, ones: int) -> int:
    """计算长度为 length 且含 1 个数不超过 ones 的二进制串总数。"""
    if length == 0 or ones == 0:
        return 1
    # 最高位放 0 则剩余有 count_valid(length - 1, ones) 个；放 1 则有 count_valid(length - 1, ones - 1) 个
    return count_valid(length - 1, ones) + count_valid(length - 1, ones - 1)


def solve() -> None:
    data = sys.stdin.read().split()
    if not data:
        return
    n, l, rank = map(int, data[:3])

    bits: list[str] = []
    rem_ones = l
    for i in range(n, 0, -1):
        # 当前最高位填 0 时，后续满足条件的串总数
        zeros_branch = count_valid(i - 1, rem_ones)
        if rank <= zeros_branch:
            bits.append("0")
        else:
            bits.append("1")
            rank -= zeros_branch
            rem_ones -= 1

    print("".join(bits))


if __name__ == "__main__":
    solve()
