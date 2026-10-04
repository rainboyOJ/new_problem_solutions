#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 02:10
# update_at: 2026-10-01 02:10

import sys
from functools import cache


@cache
def ways(rest: int, parts: int, low: int) -> int:
    """把 rest 拆成 parts 个非降正整数、且每段都不小于 low 的方案数。

    非降约定让同一个多重集合只有一种写法，于是"数拆分方案"等同于"数非降序列"。
    """
    if parts == 0:
        return 1 if rest == 0 else 0          # 恰好填满才算一个方案
    if parts == 1:
        return 1 if rest >= low else 0        # 只剩一段时，长度一旦合法就唯一
    # 首段 head 的下界是非降约束 low；上界来自「余下 parts-1 段每段至少 head」
    # 即 head + (parts-1)*head <= rest，等价于 head <= rest // parts。
    heads = range(low, rest // parts + 1)
    return sum(ways(rest - head, parts - 1, head) for head in heads)


def solve() -> None:
    n, k = map(int, sys.stdin.buffer.read().split())
    print(ways(n, k, 1))


if __name__ == "__main__":
    solve()
