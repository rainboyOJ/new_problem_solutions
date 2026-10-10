#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 22:09
# update_at: 2026-10-08 22:09

import sys
from itertools import accumulate, count


def solve() -> None:
    """求最小的 n，使 S_n = 1 + 2 + ... + n 严格「超过」m。"""
    data = iter(map(int, sys.stdin.buffer.read().split()))
    m = next(data)

    sums = accumulate(count(1))  # 依次产出三角数 1, 3, 6, 10, ...（无限，按需取）
    answer = next(i for i, s in enumerate(sums, 1) if s > m)
    print(answer)


if __name__ == "__main__":
    solve()
