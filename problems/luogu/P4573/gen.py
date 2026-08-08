#!/usr/bin/env python3
import random


BASE = [
    [1, 2, 3, 4, 5, 6, 7, 8, 9],
    [4, 5, 6, 7, 8, 9, 1, 2, 3],
    [7, 8, 9, 1, 2, 3, 4, 5, 6],
    [2, 3, 4, 5, 6, 7, 8, 9, 1],
    [5, 6, 7, 8, 9, 1, 2, 3, 4],
    [8, 9, 1, 2, 3, 4, 5, 6, 7],
    [3, 4, 5, 6, 7, 8, 9, 1, 2],
    [6, 7, 8, 9, 1, 2, 3, 4, 5],
    [9, 1, 2, 3, 4, 5, 6, 7, 8],
]


def shuffle_board(board):
    board = [row[:] for row in board]

    nums = list(range(1, 10))
    shuffled = nums[:]
    random.shuffle(shuffled)
    mp = {a: b for a, b in zip(nums, shuffled)}
    for i in range(9):
        for j in range(9):
            board[i][j] = mp[board[i][j]]

    row_groups = [0, 1, 2]
    random.shuffle(row_groups)
    new_rows = []
    for g in row_groups:
        rows = [g * 3, g * 3 + 1, g * 3 + 2]
        random.shuffle(rows)
        new_rows.extend(rows)
    board = [board[i][:] for i in new_rows]

    col_groups = [0, 1, 2]
    random.shuffle(col_groups)
    new_cols = []
    for g in col_groups:
        cols = [g * 3, g * 3 + 1, g * 3 + 2]
        random.shuffle(cols)
        new_cols.extend(cols)
    board = [[row[j] for j in new_cols] for row in board]

    return board


def main():
    random.seed()
    board = shuffle_board(BASE)

    for band in range(3):
        for inner in range(3):
            r = band * 3 + inner
            row_parts = []
            for c in [0, 1, 3, 4, 6, 7]:
                row_parts.append(">" if board[r][c] > board[r][c + 1] else "<")
            print(" ".join(row_parts))
            if inner != 2:
                vr = band * 3 + inner
                col_parts = []
                for c in range(9):
                    col_parts.append("v" if board[vr][c] > board[vr + 1][c] else "^")
                print(" ".join(col_parts))


if __name__ == "__main__":
    main()
