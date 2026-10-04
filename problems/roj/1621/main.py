#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 22:32
# update_at: 2026-09-30 22:35

import sys


def divisor_sums(cards: list[int]) -> list[int]:
    """div_sums[v] = 有多少头牛的数字整除 v（含「自己整除自己」这一份）。"""
    max_a = max(cards)
    cnt = [0] * (max_a + 1)
    for a in cards:
        cnt[a] += 1

    div_sums = [0] * (max_a + 1)
    for d in range(1, max_a + 1):
        c = cnt[d]
        if c:  # 只让出现过的数字向自己的所有倍数广播，总步数是调和级数 O(M log M)
            for multiple in range(d, max_a + 1, d):
                div_sums[multiple] += c
    return div_sums


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    cards = [next(data) for _ in range(n)]

    div_sums = divisor_sums(cards)
    # 自己的数字整除自己，每个询问都被多算了 1，扣掉
    print('\n'.join(str(div_sums[a] - 1) for a in cards))


if __name__ == "__main__":
    solve()
