#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 12:24
# update_at: 2026-09-30 12:24

import sys

LIMIT = 2 * 10**6  # 题面规定：答案超过 2×10^6 输出 -1，所以最多往后模拟这么多项


def first_repeat(a: int, b: int, c: int) -> int:
    """返回数列第一次出现重复项的下标；若首次重复发生在 LIMIT 之后则返回 -1。"""
    value, seen = 1, {1}  # a_0 = 1；seen 是已经出现过的项的集合
    for i in range(1, LIMIT + 1):
        value = (a * value + value % b) % c
        if value in seen:
            return i  # value 之前出现过，i 就是第一次出现重复的标号
        seen.add(value)
    return -1


def solve() -> None:
    a, b, c = map(int, sys.stdin.buffer.read().split())
    print(first_repeat(a, b, c))


if __name__ == "__main__":
    solve()
