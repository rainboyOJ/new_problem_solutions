#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 21:40
# update_at: 2026-09-29 21:40

import sys


def digit(n: int, k: int) -> int:
    """返回整数 n 从右往左数第 k 个数字（个位是第 1 个）。

    题面的递归 f(n,k) 每层做一次 n//10 并让计数加一，等价于先在末位之前砍掉
    k-1 位、再取新的末位：砍掉 k-1 位是 10^(k-1) 整除，取末位是对 10 取余。
    """
    return n // 10 ** (k - 1) % 10


def solve() -> None:
    n, k = map(int, sys.stdin.buffer.read().split())
    print(digit(n, k))


if __name__ == "__main__":
    solve()
