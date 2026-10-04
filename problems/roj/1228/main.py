#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 00:42
# update_at: 2026-10-04 12:56

import sys
from itertools import accumulate


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, b = next(data), next(data)
    heights = sorted((next(data) for _ in range(n)), reverse=True)  # 从高到低叠放
    ans = next(
        (i + 1 for i, s in enumerate(accumulate(heights)) if s >= b),
        n,  # 一定能达到书架高度
    )
    print(ans)


if __name__ == "__main__":
    solve()
