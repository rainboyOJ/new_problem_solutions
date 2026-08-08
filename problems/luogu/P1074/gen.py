#!/usr/bin/env python3
import random

SOLVED = [
    [5, 3, 4, 6, 7, 8, 9, 1, 2],
    [6, 7, 2, 1, 9, 5, 3, 4, 8],
    [1, 9, 8, 3, 4, 2, 5, 6, 7],
    [8, 5, 9, 7, 6, 1, 4, 2, 3],
    [4, 2, 6, 8, 5, 3, 7, 9, 1],
    [7, 1, 3, 9, 2, 4, 8, 5, 6],
    [9, 6, 1, 5, 3, 7, 2, 8, 4],
    [2, 8, 7, 4, 1, 9, 6, 3, 5],
    [3, 4, 5, 2, 8, 6, 1, 7, 9],
]


def swap_rows(board, a, b):
    board[a], board[b] = board[b], board[a]


def swap_cols(board, a, b):
    for row in board:
        row[a], row[b] = row[b], row[a]


def permute_digits(board):
    mp = list(range(10))
    perm = list(range(1, 10))
    random.shuffle(perm)
    for i in range(1, 10):
        mp[i] = perm[i - 1]
    for i in range(9):
        for j in range(9):
            board[i][j] = mp[board[i][j]]


def make_board():
    board = [row[:] for row in SOLVED]

    for block in range(3):
        rows = [block * 3, block * 3 + 1, block * 3 + 2]
        random.shuffle(rows)
        tmp = [board[r][:] for r in rows]
        for i, r in enumerate(range(block * 3, block * 3 + 3)):
            board[r] = tmp[i]

    for block in range(3):
        cols = [block * 3, block * 3 + 1, block * 3 + 2]
        random.shuffle(cols)
        cur = [[board[i][c] for c in cols] for i in range(9)]
        for i in range(9):
            for j, c in enumerate(range(block * 3, block * 3 + 3)):
                board[i][c] = cur[i][j]

    permute_digits(board)
    return board


def main():
    random.seed()
    board = make_board()

    # 题目保证至少 24 个已知数；为了让 brute 也能跑，对拍时多保留一些。
    keep = random.randint(28, 40)
    cells = [(i, j) for i in range(9) for j in range(9)]
    random.shuffle(cells)

    keep_set = set(cells[:keep])
    for i in range(9):
        for j in range(9):
            if (i, j) not in keep_set:
                board[i][j] = 0

    for i in range(9):
        print(*board[i])


if __name__ == "__main__":
    main()
