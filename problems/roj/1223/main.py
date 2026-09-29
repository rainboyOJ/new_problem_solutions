#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 00:29
# update_at: 2026-09-30 00:29

import sys
from itertools import takewhile


def next_same_ones(n: int) -> int:
    """返回大于 n 的最小整数，其二进制表示中 1 的个数与 n 相同（Gosper 进位法）。"""
    low = n & -n                                  # n 最低位置 1 的值 2^l，即进位的入口
    carried = n + low                             # 从第 l 位起的连续 1 全部进位清空，其上方第一个 0 变 1
    return carried | ((n ^ carried) >> 2) // low   # 把被清空的 k 个 1 中的 k-1 个铺回最低位


def solve() -> None:
    data = map(int, sys.stdin.buffer.read().split())
    out = [str(next_same_ones(n)) for n in takewhile(bool, data)]  # 读到 0（假值）即结束
    sys.stdout.write('\n'.join(out))


if __name__ == "__main__":
    solve()
