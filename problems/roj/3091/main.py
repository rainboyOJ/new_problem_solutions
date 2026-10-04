#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 16:27
# update_at: 2026-10-01 16:33

import sys
from collections.abc import Iterator

IMPOSSIBLE = "Oh,it's impossible~!!"  # 无解时的固定输出（题面原文，含两个感叹号）


def build_equations(n: int, start: list[int], goal: list[int], data: Iterator[int]) -> list[int]:
    """把本组数据变成 n 个方程：第 j 行的低 n 位记录「哪些开关会改变第 j 位」。

    第 j 位的最终状态只由「会带动 j 的那些开关」以及 j 自己决定，所以每个方程
    对应一个输出位置 j，而不是一个开关。
    """
    rows = [0] * n
    i, j = next(data), next(data)  # 一对 I J；读到 0 0 表示本组结束
    while j:
        rows[j - 1] ^= 1 << (i - 1)  # 变量 i 出现在第 j 行：按 i 会带动 j
        i, j = next(data), next(data)
    for j in range(n):
        rows[j] |= 1 << j  # 主对角元：按 j 自己必定改变第 j 位
    # 第 j 位要求翻转恰好 (start[j] ^ goal[j]) 次，把它作为常数项放到第 n 位。
    return [row ^ (start[j] ^ goal[j]) << n for j, row in enumerate(rows)]


def free_variables(rows: list[int], n: int) -> int:
    """把每一行看成「变量系数写在低 n 位、右端常数写在第 n 位」的整数，返回自由元个数。

    返回 -1 表示出现 0 = 1 的矛盾行（无解）。消元时用「取最低位的行」当主元行，
    这样第 j 列的主元恰好是第 j 位。
    """
    rows = [row for row in rows if row]  # 全零行不含任何信息，直接丢掉
    rank = 0
    for col in range(n):
        pivot = -1
        for k in range(rank, len(rows)):
            if rows[k] >> col & 1:
                pivot = k
                break
        if pivot < 0:
            continue  # 这一列没有主元，该变量自由
        rows[rank], rows[pivot] = rows[pivot], rows[rank]
        pivot_row = rows[rank]
        for k in range(len(rows)):
            if k != rank and rows[k] >> col & 1:
                rows[k] ^= pivot_row  # 整行异或，右端常数跟着一起变
        rank += 1
    if any(row == 1 << n for row in rows):  # 只剩常数位的 0 = 1
        return -1
    return n - rank


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    out: list[str] = []
    cases = next(data)  # 题面的 K

    for _ in range(cases):
        n = next(data)
        start = [next(data) for _ in range(n)]
        goal = [next(data) for _ in range(n)]
        free = free_variables(build_equations(n, start, goal, data), n)
        out.append(IMPOSSIBLE if free < 0 else str(1 << free))

    print('\n'.join(out))


if __name__ == "__main__":
    solve()
