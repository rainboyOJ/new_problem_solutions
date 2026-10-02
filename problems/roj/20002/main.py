#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 19:16
# update_at: 2026-10-02 19:16

import sys


def count(length: int, stone: int) -> int:
    """铺满长度为 length 的边需要几块边长 stone 的石板：整数上取整 ⌈length/stone⌉。"""
    return (length + stone - 1) // stone


def solve() -> None:
    n, m, a = map(int, sys.stdin.buffer.read().split())
    print(count(n, a) * count(m, a))


if __name__ == "__main__":
    solve()
