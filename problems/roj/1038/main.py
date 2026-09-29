#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 15:25
# update_at: 2026-09-29 15:25

import sys


def eaten_apples(x: int, y: int) -> int:
    """x 小时啃完一个时 y 小时啃过的苹果数 ⌈y/x⌉：啃了一半的也不再完整。"""
    return -(-y // x)  # 整数向上取整


def solve() -> None:
    n, x, y = map(int, sys.stdin.buffer.read().split())
    remain = max(n - eaten_apples(x, y), 0)  # 吃到超出总数时按 0 算
    print(remain)


if __name__ == "__main__":
    solve()
