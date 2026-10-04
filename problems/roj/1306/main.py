#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 04:12
# update_at: 2026-09-30 04:12

import sys


def solve() -> None:
    data = list(map(int, sys.stdin.buffer.read().split()))
    it = iter(data)

    n = next(it)
    a = [next(it) for _ in range(n)]
    m = next(it)
    b = [next(it) for _ in range(m)]

    # order[j] 记录以 a[j] 结尾的 LCIS：长度 + 序列本身。
    lens = [0] * n
    seqs: list[list[int]] = [[] for _ in range(n)]

    for target in b:
        cur_len = 0
        cur_seq: list[int] = []
        for j, x in enumerate(a):
            if x < target and lens[j] > cur_len:
                cur_len = lens[j]
                cur_seq = seqs[j]
            elif x == target:
                lens[j] = cur_len + 1
                seqs[j] = cur_seq + [x]

    best = max(range(n), key=lambda j: lens[j], default=-1)
    length = lens[best] if best != -1 else 0

    print(length)
    print(' '.join(map(str, seqs[best])) if best != -1 else '')


if __name__ == "__main__":
    solve()
