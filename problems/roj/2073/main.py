#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-05 21:47
# update_at: 2026-07-05 21:47

import sys

WHITE, EMPTY, BLACK = 1, 0, 2


def search(n: int) -> list[int]:
    """回溯搜索最少步数下字典序最小的跳棋移动序列。"""
    board = [WHITE] * n + [EMPTY] + [BLACK] * n
    target = [BLACK] * n + [EMPTY] + [WHITE] * n
    max_steps = (n + 1) ** 2 - 1
    total_len = 2 * n + 1
    path: list[int] = []

    def dfs(blank: int) -> bool:
        if len(path) == max_steps:
            return board == target

        # 候选移入空格的棋子位置：优先枚举较小下标以保证字典序最小
        moves: list[int] = []
        if blank >= 2 and board[blank - 2] == WHITE and board[blank - 1] == BLACK:
            moves.append(blank - 2)
        if blank >= 1 and board[blank - 1] == WHITE:
            moves.append(blank - 1)
        if blank + 1 < total_len and board[blank + 1] == BLACK:
            moves.append(blank + 1)
        if blank + 2 < total_len and board[blank + 2] == BLACK and board[blank + 1] == WHITE:
            moves.append(blank + 2)

        moves.sort()
        for pos in moves:
            board[blank], board[pos] = board[pos], board[blank]
            path.append(pos + 1)
            if dfs(pos):
                return True
            path.pop()
            board[blank], board[pos] = board[pos], board[blank]
        return False

    dfs(n)
    return path


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    ans = search(n)
    for i in range(0, len(ans), 20):
        print(*(ans[i : i + 20]))


if __name__ == "__main__":
    solve()
