#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 07:19
# update_at: 2026-10-02 07:19

import sys


def solve() -> None:
    n = int(sys.stdin.readline())
    # 递推 A_k = 2*A_{k-1} + 2，通项 A_n = 2^(n+1) - 2
    print((2 << n) - 2)


if __name__ == "__main__":
    solve()
