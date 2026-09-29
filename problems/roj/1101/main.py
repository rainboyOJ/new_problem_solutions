#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 10:30
# update_at: 2026-10-02 10:30

import sys


def solve() -> None:
    a, b, c = map(int, sys.stdin.buffer.read().split())

    # x 上界是 c//a：再大则 a*x > c，y 无非负解；枚举每个 x，余数 (c-a*x) 整除 b 即有一解
    print(sum((c - a * x) % b == 0 for x in range(c // a + 1)))


if __name__ == "__main__":
    solve()
