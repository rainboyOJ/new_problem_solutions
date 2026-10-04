#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 22:51
# update_at: 2026-09-29 22:51

import sys
from functools import cache
from itertools import takewhile


@cache
def ways(n: int) -> int:
    """上到第 n 阶的走法数：把 n 拆成 1/2/3 之和的有序方案数。

    最后一步只能跨 1、2 或 3 阶，所以 ways(n) 等于前三项之和；
    n = 0 的空走法记 1 种，正是递推的种子，n = 1 也恰好是 1。
    """
    return ways(n - 1) + ways(n - 2) + ways(n - 3) if n > 2 else max(n, 1)


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    queries = list(takewhile(int, data))  # 逐行读询问，遇到 0 结束

    # @cache 让每个下标只被真正算一次，全部询问共享同一份递推结果
    print('\n'.join(map(str, map(ways, queries))))


if __name__ == "__main__":
    solve()
