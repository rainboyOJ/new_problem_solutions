#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 10:42
# update_at: 2026-10-02 10:42

import sys


def min_operations(heights: list[int]) -> int:
    """最少操作数：从 0 起，逐块累加"比左邻高出的部分"，下降段贡献 0。"""
    prev = 0  # 左边没有积木，虚拟高度 0
    total = 0
    for height in heights:
        if height > prev:           # 这段爬升必须由不覆盖左邻的操作补齐
            total += height - prev
        prev = height
    return total


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    heights = [next(data) for _ in range(n)]  # 第 i 块的目标高度 h_i
    print(min_operations(heights))


if __name__ == "__main__":
    solve()
