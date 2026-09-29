#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-05 21:47
# update_at: 2026-07-05 21:47

import sys


def solve() -> None:
    data = sys.stdin.buffer.read().split()
    rows: list[list[bytes]] = [data[i:i + 5] for i in range(0, 25, 5)]
    m, n = int(data[25]) - 1, int(data[26]) - 1
    rows[m], rows[n] = rows[n], rows[m]
    print('\n'.join(b' '.join(r).decode() for r in rows))


if __name__ == "__main__":
    solve()
