#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 04:54
# update_at: 2026-09-30 04:54

import sys
from functools import cache


@cache
def ways(m: int, n: int) -> int:
    """把 m 点查克拉分配给 n 个有序影分身（允许为 0）的方案数。

    只看每个分身的点数构成的非递增序列：序列最大值为 0 时全 0 只有一种；
    只用 1 个分身时方案唯一。第一个分身取 0 点 → ways(m, n-1)；
    每个分身都至少 1 点 → 全体减 1，对应 ways(m-n, n)。
    """
    if m == 0 or n == 1:
        return 1
    if m < n:
        return ways(m, m)  # 多出的分身只能拿 0 点，等价于没有它们
    return ways(m, n - 1) + ways(m - n, n)


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    out: list[str] = []
    T = next(data)

    for _ in range(T):
        m, n = next(data), next(data)
        out.append(str(ways(m, n)))

    print('\n'.join(out))


if __name__ == "__main__":
    solve()
