#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 17:23
# update_at: 2026-10-02 17:23

import sys


def solve() -> None:
    """贪心扫描：reach 是当前弹力下能到达的最右格子，cast_at 是撑起它的施法格。"""
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    p = [next(data) for _ in range(n)]  # 弹力系数，p[i-1] 是格子 i 的值

    reach = 1           # 不再施法能到达的最右格子（初始站在格子 1）
    cast_at = 1         # 把 reach 撑到当前值的格子，即断档时应施法的格子
    casts: list[int] = []

    for i in range(1, n + 2):  # 格子 n+1 是终点，也要参与断档检查
        if i > reach:  # 第一次走出可达范围：给 cast_at 施法恰好补上这一格
            casts.append(cast_at)
            p[cast_at - 1] += 1
            reach = cast_at = i
        if i <= n and i + p[i - 1] > reach:  # 格子 i 能把右边界推得更远
            reach = i + p[i - 1]
            cast_at = i

    print(len(casts))
    if casts:
        print(*casts)


if __name__ == "__main__":
    solve()
