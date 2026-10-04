#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-05 21:47
# update_at: 2026-07-05 21:47

import sys


def solve() -> None:
    it = iter(sys.stdin.buffer.read().split())
    n = int(next(it))
    a, b = int(next(it)), int(next(it))          # 国王的左右手数字

    # 大臣按 a_i * b_i 从小到大排：交换相邻两人不会让最大奖赏变大
    ministers = sorted(
        ((int(next(it)), int(next(it))) for _ in range(n)),
        key=lambda p: p[0] * p[1],
    )

    best = 0
    for ai, bi in ministers:
        best = max(best, a // bi)  # 队列里排在他前面的人左手的乘积
        a *= ai

    print(best)


if __name__ == "__main__":
    solve()
