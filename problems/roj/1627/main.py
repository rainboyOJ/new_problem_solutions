#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 22:54
# update_at: 2026-09-30 23:05

import math
import sys


def solve() -> None:
    a, b = map(int, sys.stdin.buffer.read().split())
    print(math.gcd(a, b))


if __name__ == "__main__":
    solve()
