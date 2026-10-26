#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-26 13:30
# update_at: 2026-10-26 13:30

import sys

BITS = 30  # a_i <= 1e9 < 2^30，只需要看低 30 位


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    seq = [next(data) for _ in range(n)]

    best = [0] * BITS  # best[b]：以某个含第 b 位的数结尾的最长合法子序列长度
    ans = 0
    for x in seq:
        # 所有与 x 有公共位的末项都能接上 x，取其中最长的那个
        length = 1 + max((best[b] for b in range(BITS) if x >> b & 1), default=0)
        for b in range(BITS):
            if x >> b & 1:
                best[b] = max(best[b], length)
        ans = max(ans, length)

    print(ans)


if __name__ == "__main__":
    solve()
