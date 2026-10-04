#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 00:03
# update_at: 2026-09-30 00:03

import sys


def current_wins(a: int, b: int) -> bool:
    """(a, b) 局面下当前执子者是否必胜。

    商 a//b >= 2 时必胜（可以调整取 k 倍把必败局面留给对手）；
    a % b == 0 时直接取空一堆获胜；
    否则商为 1，只有 (a, b) -> (b, a-b) 唯一取法，胜负随轮次翻转。
    """
    a, b = max(a, b), min(a, b)                      # 保证 a >= b，较多堆是 a
    mine = True                                      # True = 起始先手执子
    while a // b < 2 and a % b != 0:                 # 商为 1 且不整除：唯一取法
        a, b = b, a - b                              # 较多堆变 b，较多堆变 a-b（更小）
        mine = not mine                              # 唯一取法后换人执子
    return mine                                      # 退出时比值 >=2 或整除：执子者获胜


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    out: list[str] = []
    while True:
        a, b = next(data), next(data)                # 每组一行两个正整数
        if a == 0 and b == 0:                        # 0 0 结束
            break
        out.append("win" if current_wins(a, b) else "lose")

    print("\n".join(out))


if __name__ == "__main__":
    solve()
