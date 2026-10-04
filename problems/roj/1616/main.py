#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 22:18
# update_at: 2026-09-30 22:18

import sys


def solve() -> None:
    a, b, m = map(int, sys.stdin.buffer.read().split())

    # a^b 完整展开有 b*log10(a) 位（b 可达 1e9），先算幂再取模会撑爆内存，
    # 必须边平方边取模；三参数 pow 底层正是二进制快速幂，指数每折半一次。
    print(pow(a, b, m))


if __name__ == "__main__":
    solve()
