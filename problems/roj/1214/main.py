#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 23:51
# update_at: 2026-10-04 13:17

import sys

N = 8          # 棋盘为 N × N
ALL = (1 << N) - 1  # 低位 N 个 1，表示当前行可放的列掩码


def collect(solutions: list[str], row: int, cols: int, diag1: int, diag2: int, path: list[int]) -> None:
    """按行 DFS：row 为当前处理行，cols/diag1/diag2 分别记录已被占用的列、主对角线、副对角线。"""
    if row == N:
        # 列号转换为 1-indexed 后拼成整数串
        solutions.append(''.join(str(c + 1) for c in path))
        return
    # 当前行仍可放的列：未被列或两条对角线攻击
    free = ALL & ~(cols | diag1 | diag2)
    while free:
        low = free & -free                 # 取最低位 1 作为当前列
        col = low.bit_length() - 1         # 列号 0..N-1
        path.append(col)
        # 下一行：列占用不变；对角线分别左移/右移一位表示攻击范围向下延伸
        collect(solutions, row + 1, cols | low, (diag1 | low) << 1, (diag2 | low) >> 1, path)
        path.pop()
        free ^= low                        # 清除这一位，尝试下一列


def solve() -> None:
    solutions: list[str] = []
    collect(solutions, 0, 0, 0, 0, [])
    solutions.sort()                       # 按整数字典序排列

    data = iter(map(int, sys.stdin.buffer.read().split()))
    q = next(data)                         # 询问组数
    out: list[str] = []
    for _ in range(q):
        b = next(data) - 1                 # 询问的序号（1-indexed）
        out.append(solutions[b])
    sys.stdout.write('\n'.join(out))


if __name__ == "__main__":
    solve()
