#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 00:47
# update_at: 2026-10-01 00:48

import sys


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, k = next(data), next(data)

    # 巴什博弈：剩余数不是 (k+1) 的倍数即为必胜态，先手取走 n % (k+1) 颗就把它交给对手
    first_wins = n % (k + 1) != 0
    print(1 if first_wins else 2)


if __name__ == "__main__":
    solve()
