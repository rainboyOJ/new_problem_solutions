#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 22:48
# update_at: 2026-10-08 22:48

import sys
from itertools import accumulate, islice, takewhile

MOD = 10**6  # 末 6 位 = 对 10^6 取模


def solve() -> None:
    """读入 n，输出 1! + 2! + ... + n! 的末 6 位（不含前导 0）。"""
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data, None)
    if n is None:  # 空输入：不输出，与 C++ 侧 `if (cin >> n)` 失败时一致
        return

    # accumulate 的 initial=1 是 0!，islice 丢掉它，剩下的依次是 1!, 2!, ..., n! 的末 6 位
    facs = islice(accumulate(range(1, n + 1), lambda f, i: f * i % MOD, initial=1), 1, None)
    # 25! 起必含因子 10^6，其后每一项都是 0，故在第一个 0 处就截断
    terms = takewhile(bool, facs)
    print(sum(terms) % MOD)


if __name__ == "__main__":
    solve()
