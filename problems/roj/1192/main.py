#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-05 22:10
# update_at: 2026-07-05 22:10

import sys
from functools import cache


@cache
def count(m: int, n: int) -> int:
    """m 个同样的苹果放进 n 个同样的盘子（允许空盘）的方案数。

    边界：没有苹果、或只剩一个盘子，都只有一种放法。
    """
    if m == 0 or n == 1:
        return 1
    if m < n:
        return count(m, m)  # 盘子比苹果多，多出的盘子必然空着，与 m 个盘子等价
    # 按第 n 个盘子是否为空分类：空 → 少一个盘子；不空 → 每盘先垫 1 个
    return count(m, n - 1) + count(m - n, n)


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    T = next(data)

    out: list[str] = []
    for _ in range(T):
        m, n = next(data), next(data)  # 苹果数 m，盘子数 n
        out.append(str(count(m, n)))

    print('\n'.join(out))


if __name__ == "__main__":
    solve()
