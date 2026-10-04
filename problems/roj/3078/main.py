#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 14:49
# update_at: 2026-10-01 14:49

import sys

WIDTH = 5   # 棋盘列数
HEIGHT = 7  # 棋盘行数


def three_run_grid(board: list[list[int]]) -> list[list[bool]] | None:
    """把本轮该消除的方块标记在 5x7 网格上：行列共享的方块只记一次；无三连返回 None。"""
    dead = [[False] * HEIGHT for _ in range(WIDTH)]
    found = False
    for x in range(WIDTH):
        col = board[x]
        for y in range(len(col) - 2):  # 每列内部竖向三连
            if col[y] == col[y + 1] == col[y + 2]:
                found = True
                dead[x][y] = dead[x][y + 1] = dead[x][y + 2] = True
    for y in range(HEIGHT):
        for x in range(WIDTH - 2):
            # 不足 7 格的列把缺位读作 0，颜色从 1 开始，0 天然不会三连同色
            run = [board[i][y] if y < len(board[i]) else 0 for i in range(x, x + 3)]
            if run[0] and run[0] == run[1] == run[2]:
                found = True
                dead[x][y] = dead[x + 1][y] = dead[x + 2][y] = True
    return dead if found else None


def settle(board: list[list[int]]) -> list[list[int]]:
    """消除 → 掉落 循环到棋盘稳定。"""
    while dead := three_run_grid(board):
        for x in range(WIDTH):
            col = board[x]
            for y, d in enumerate(dead[x]):
                if d:
                    col[y] = 0                  # 先整体标记消除，不能边判边删
        board[:] = [[c for c in col if c] for col in board]  # 再整体掉落
    return board


def moved(board: list[list[int]], x: int, y: int, g: int) -> list[list[int]] | None:
    """把 (x, y) 的方块沿 g 方向拖动一格并结算，返回新棋盘；无意义移动返回 None。"""
    nx = x + g
    if not 0 <= nx < WIDTH:
        return None
    nb = [col[:] for col in board]
    if y < len(nb[nx]):                          # 目标位置有方块：交换
        if nb[nx][y] == nb[x][y]:
            return None                          # 同色交换后棋盘不变，白白浪费一步
        nb[nx][y], nb[x][y] = nb[x][y], nb[nx][y]
    else:                                        # 目标位置为空：抽落后掉落到 min(y, 列高)
        nb[nx].insert(min(y, len(nb[nx])), nb[x].pop(y))
    return settle(nb)


def dfs(board: list[list[int]], left: int, failed: set[tuple]) -> list[tuple[int, int, int]] | None:
    """还剩 left 步时能否清空；按 x→y→(右,左) 的枚举顺序，第一个解就是字典序最小的。"""
    state = (tuple(map(tuple, board)), left)     # 可哈希局面：只用来记住"到此必败"
    if state in failed:
        return None
    if left == 0:
        return [] if all(not col for col in board) else None
    counts = [0] * 11                            # 颜色 1~10 的方块计数
    for col in board:
        for c in col:
            counts[c] += 1
    if any(0 < v < 3 for v in counts):           # 某颜色只剩 1~2 个，永远凑不出三连
        failed.add(state)
        return None
    for x in range(WIDTH):
        for y in range(len(board[x])):
            for g in (1, -1):
                nx = x + g
                if not 0 <= nx < WIDTH:
                    continue
                # 左移交换 = 左邻方块右移，那个局面字典序更小且已先枚举过，直接跳过
                if g == -1 and y < len(board[nx]):
                    continue
                nb = moved(board, x, y, g)
                if nb is None:
                    continue
                tail = dfs(nb, left - 1, failed)
                if tail is not None:
                    return [(x, y, g)] + tail
    failed.add(state)
    return None


def solve() -> None:
    """读入棋盘，DFS 恰好 n 步，按字典序输出方案或 -1。"""
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    board: list[list[int]] = []
    for _ in range(WIDTH):                       # 每竖列自下而上给出，以 0 结尾
        col: list[int] = []
        v = next(data)
        while v != 0:
            col.append(v)
            v = next(data)
        board.append(col)

    moves = dfs(board, n, set())
    if moves is None:
        print(-1)
    else:
        print("\n".join(f"{x} {y} {g}" for x, y, g in moves))


if __name__ == "__main__":
    solve()
