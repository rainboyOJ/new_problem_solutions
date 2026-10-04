#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 06:05
# update_at: 2026-10-02 06:05

import sys


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    length = next(data)  # 马路长 L，0..L 每个整数点一棵树
    m = next(data)       # 区域个数

    removed = bytearray(length + 1)  # 桶：1 = 该整数点的树已被移走
    for _ in range(m):
        start, end = next(data), next(data)
        lo, hi = sorted((start, end))  # 起止点顺序不保证，含两端端点
        removed[lo:hi + 1] = b'\x01' * (hi - lo + 1)  # 区间整体打标记

    print(removed.count(0))  # 仍为 0 的点就是留下来的树


if __name__ == "__main__":
    solve()
