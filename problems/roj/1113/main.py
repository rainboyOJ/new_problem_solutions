#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 19:26
# update_at: 2026-09-29 19:26

import sys


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    a = [next(data) for _ in range(n)]

    biggest = max(a)  # 数列最大值；与它相同的数全部不参与求和
    print(sum(x for x in a if x != biggest))


if __name__ == "__main__":
    solve()
