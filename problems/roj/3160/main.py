#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 21:46
# update_at: 2026-10-01 21:50

import sys
from functools import cache
from math import comb

TERMINATOR = 0  # 输入以单独一行的 0 结束，它不是一次询问


def graph_count(n: int) -> int:
    """n 个标号点的任意无向图个数：每条可能边独立取舍，共 2^(n(n-1)/2) 个。"""
    return 1 << (n * (n - 1) // 2)


@cache
def connected_count(n: int) -> int:  # n 最大 50，缓存让多组询问与递归都不重复计算
    """n 个标号点的连通无向图个数：全集减去 1 号点所在块大小 k<n 的全部分类情形。"""
    return graph_count(n) - sum(
        comb(n - 1, k - 1) * connected_count(k) * graph_count(n - k)  # 选 k-1 个同伴，块内连通，块外任意
        for k in range(1, n)
    )


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    asked = [n for n in data if n != TERMINATOR]  # 丢弃终止用的 0

    lines = '\n'.join(map(str, map(connected_count, asked)))
    if lines:  # 只有终止标记 0 时一行都不输出，而不是打印一个空行
        print(lines)


if __name__ == "__main__":
    solve()
