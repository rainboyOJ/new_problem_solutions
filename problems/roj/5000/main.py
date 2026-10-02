#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 15:22
# update_at: 2026-10-02 15:22

import sys
from functools import cache


@cache
def parts(rest: int, cap: int) -> int:
    """把 rest 拆成若干不超过 cap 的正整数之和（顺序无关）的方案数。

    枚举首段 x，再把 rest-x 交给同一个问题、上限收紧为 x：
    下一段永远不超过上一段，5+1 与 1+5 落进同一条分支，天然不重不漏。
    """
    if rest == 0:
        return 1  # 空拆分：各段恰好拼完，算一种方案
    return sum(parts(rest - x, x) for x in range(min(rest, cap), 0, -1))


def solve() -> None:
    n = int(sys.stdin.buffer.read())
    print(parts(n, n))


if __name__ == "__main__":
    solve()
