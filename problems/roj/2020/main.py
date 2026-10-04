#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 03:20
# update_at: 2026-10-01 03:20

import sys

SHOW = 3  # 题面只要求前 3 个解，而按列号升序展开时它们正好是字典序最小的 3 个


def solve() -> None:
    n = int(sys.stdin.buffer.read().split()[0])
    full = (1 << n) - 1          # 低 n 位全 1：第 c 位为 1 表示列 c 还没被占
    head: list[list[int]] = []   # 前 SHOW 个解，每个解是各行的列号
    pos = [0] * n                # pos[row] 是第 row 行的列号；放棋子即写入，回溯即被覆盖
    total = 0

    def dfs(row: int, col: int, diag1: int, diag2: int) -> None:
        """在第 row 行及其之后摆完剩下的棋子：三个掩码是已被占用的列 / 两条斜线。"""
        nonlocal total
        if row == n:                     # n 行都放好了，得到一个完整解
            total += 1
            if len(head) < SHOW:
                head.append(pos.copy())  # 不复制的话，回溯会把这份棋盘改掉
            return
        free = full & ~(col | diag1 | diag2)   # 本行所有合法列
        while free:
            bit = free & -free           # 取列号最小的合法列，同一层天然按字典序展开
            free ^= bit
            pos[row] = bit.bit_length()  # bit = 1 << (列号-1)，bit_length() 还原成 1 起算的列号
            # r+c 与 r-c 分别由 diag1、diag2 记录，走到下一行时两条斜线朝相反方向平移一位
            dfs(row + 1, col | bit, (diag1 | bit) << 1, (diag2 | bit) >> 1)

    dfs(0, 0, 0, 0)
    print('\n'.join(' '.join(map(str, solution)) for solution in head))
    print(total)


if __name__ == "__main__":
    solve()
