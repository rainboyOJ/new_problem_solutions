#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 07:38
# update_at: 2026-10-01 07:38

import sys

DR = (-1, 0, 1, 0)  # 北、东、南、西四个方向的行偏移
DC = (0, 1, 0, -1)  # 北、东、南、西四个方向的列偏移
UNDO = 0  # 栈帧类型：回退帧，撤销一段直行的足迹并还原计数
WALK = 1  # 栈帧类型：直行帧，从 (row, col) 沿 dir 直行到底后再左右转弯


def solve() -> None:
    data = iter(sys.stdin.read().split())
    N = int(next(data))
    B = int(next(data))

    blocked = bytearray(N * N)  # 路障占用表，下标 = 行 * N + 列
    for _ in range(B):
        pos = next(data)
        col = ord(pos[0]) - 65  # 列字母 A1 的 A → 0
        row = int(pos[1:]) - 1  # 行号 A1 的 1 → 0
        blocked[row * N + col] = 1

    trail = bytearray(N * N)  # 当前路线已经走过的格子
    trail[0] = 1  # 出发点 A1 已计入
    count = 1
    ans = 1

    # 手写栈代替深递归：直行帧 (WALK, row, col, dir)，回退帧 (UNDO, 本段足迹下标)
    stack: list[tuple] = [(WALK, 0, 0, 1), (WALK, 0, 0, 2)]  # 初始只能向东或向南

    while stack:
        frame = stack.pop()
        if frame[0] == UNDO:
            for idx in frame[1]:
                trail[idx] = 0  # 回溯：撤掉这一段直行的足迹
            count -= len(frame[1])
            continue

        _, row, col, d = frame
        run: list[int] = []
        hit_trail = False  # 撞上自己的足迹：题目规定此时整段散步结束，不再转弯
        # 选定方向后一直走，直到棋盘边缘、路障或自己的足迹
        while True:
            nr, nc = row + DR[d], col + DC[d]
            if not 0 <= nr < N or not 0 <= nc < N:
                break
            idx = nr * N + nc
            if trail[idx]:
                hit_trail = True
                break
            if blocked[idx]:
                break
            trail[idx] = 1
            run.append(idx)
            row, col = nr, nc
            count += 1
        if count > ans:
            ans = count

        stack.append((UNDO, run))  # 子树全部结束后再统一撤销本段足迹
        if hit_trail:
            continue  # 撞到自己的足迹，无路可走，直接回溯
        # 只有撞边缘 / 路障才转弯：左转与右转都试，下一步走得通才入栈
        for nd in ((d + 1) % 4, (d + 3) % 4):
            nr, nc = row + DR[nd], col + DC[nd]
            if 0 <= nr < N and 0 <= nc < N and not trail[nr * N + nc] and not blocked[nr * N + nc]:
                stack.append((WALK, row, col, nd))

    print(ans)


if __name__ == "__main__":
    solve()
