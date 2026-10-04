#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 16:46
# update_at: 2026-10-01 16:46

import sys

N = 200  # 题面数据范围：2 ≤ N, M ≤ 200


def mex(values: set[int]) -> int:
    """values 之外的最小非负整数，即 SG 值的定义。"""
    m = 0
    while m in values:
        m += 1
    return m


def build_sg(limit: int) -> list[list[int]]:
    """sg[i][j]：i×j 的纸（i,j≥2）只保留"安全剪法"时的 SG 值。"""
    sg = [[0] * (limit + 1) for _ in range(limit + 1)]
    for i in range(2, limit + 1):
        row_i = sg[i]
        for j in range(2, limit + 1):
            # 只枚举剪开后两部分长宽都 ≥2 的剪法：剪出 1×k 的剪法必送对手
            # 一个含 1×k 的必胜局面（对手把它剪出 1×1 直接获胜），可整体忽略。
            # 剪在 a 与剪在 i-a 得到的两块互换，异或值相同，枚举一半即可。
            options = {sg[a][j] ^ sg[i - a][j] for a in range(2, i // 2 + 1)} | {
                sg[i][b] ^ sg[i][j - b] for b in range(2, j // 2 + 1)
            }
            row_i[j] = mex(options)
    return sg


def solve() -> None:
    sg = build_sg(N)
    data = iter(map(int, sys.stdin.buffer.read().split()))
    print('\n'.join('WIN' if sg[n][m] else 'LOSE' for n, m in zip(data, data)))


if __name__ == "__main__":
    solve()
