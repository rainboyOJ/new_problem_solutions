#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 08:45
# update_at: 2026-10-02 08:45

import sys

DIGIT = 2  # 要统计的数字


def count_upto(n: int) -> int:
    """[0, n] 中数字 2 出现的总次数：按位分段计数。"""
    total = 0
    w = 1
    while w <= n:
        # 该位把 [0, n] 分成三段：前缀 higher、当前位 cur、后缀 lower
        higher, cur, lower = n // (w * 10), n // w % 10, n % w
        # 前缀每取一个值，该位贡献整段 w 个 2（前缀 < higher）；
        # 前缀 == higher 时：cur>2 补满 w，cur==2 只到 lower+1，cur<2 没有
        add = w if cur > DIGIT else lower + 1 if cur == DIGIT else 0
        total += higher * w + add
        w *= 10
    return total


def solve() -> None:
    L, R = map(int, sys.stdin.buffer.read().split())
    # 区间计数用前缀差： [L, R] = [0, R] - [0, L-1]
    print(count_upto(R) - count_upto(L - 1))


if __name__ == "__main__":
    solve()
