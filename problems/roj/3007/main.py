#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 09:33
# update_at: 2026-10-01 09:33

import sys
from collections.abc import Iterator


def combine(n: int, m: int, start: int = 1) -> Iterator[tuple[int, ...]]:
    """产出从 start..n 中再选 m 个数的全部组合，按字典序依次给出。"""
    if m == 0:
        yield ()  # 一个数都不用再选，空组合本身就是一种方案
    else:
        # first 最大只能取 n-m+1，否则后面凑不够 m-1 个数
        for first in range(start, n - m + 2):
            for rest in combine(n, m - 1, first + 1):
                yield (first, *rest)


def solve() -> None:
    n, m = map(int, sys.stdin.buffer.read().split())
    print('\n'.join(' '.join(map(str, combo)) for combo in combine(n, m)))


if __name__ == "__main__":
    solve()
