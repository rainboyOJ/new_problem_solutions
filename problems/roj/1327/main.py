#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 05:27
# update_at: 2026-10-04 13:29

import sys


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    size = 2 * n + 2
    a = [''] * (size + 1)                       # 1-index，a[1..2n+2]
    for i in range(1, n + 1):
        a[i] = 'o'
    for i in range(n + 1, size + 1):
        a[i] = '*'
    a[size - 1] = a[size] = '-'                  # 最后两个空位

    st = 0
    sp = size - 1                                # 空位起点

    def out() -> None:
        nonlocal st
        print(f"step{st:2d}:{''.join(a[1:size + 1])}")
        st += 1

    def move(m: int) -> None:
        """把相邻棋子 a[m],a[m+1] 整体移到当前空位 sp,sp+1，空位随之左移。"""
        nonlocal sp
        a[sp] = a[m]
        a[sp + 1] = a[m + 1]
        a[m] = a[m + 1] = '-'
        sp = m
        out()

    out()                                        # step 0：初始局面

    m = n
    while m > 4:
        move(m)
        move(2 * m - 1)
        m -= 1

    # n = 4 时的收尾序列
    for x in (4, 8, 2, 7, 1):
        move(x)


if __name__ == "__main__":
    solve()
