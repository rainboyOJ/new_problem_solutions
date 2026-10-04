#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 13:42
# update_at: 2026-09-29 13:42

import sys


def solve() -> None:
    """整型 → 布尔型 → 整型：bool(n) 只保留"是否非零"，回 int 即 1/0。"""
    n = int(sys.stdin.buffer.read())
    print(int(bool(n)))


if __name__ == "__main__":
    solve()
