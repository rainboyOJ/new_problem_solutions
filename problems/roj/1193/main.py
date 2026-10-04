#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 22:52
# update_at: 2026-09-29 22:52

import sys


def solve() -> None:
    n: int = int(sys.stdin.buffer.read())
    a = b = 1  # f[0] = f[1] = 1
    for _ in range(2, n + 1):
        a, b = b, a + b  # 滚动到 f[i]
    print(b)


if __name__ == "__main__":
    solve()
