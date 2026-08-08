#!/usr/bin/env python3
import sys


def parse_relations(path):
    lines = []
    with open(path, "r", encoding="utf-8") as f:
        for raw in f:
            line = raw.rstrip("\n")
            if line:
                lines.append(line)

    if len(lines) != 15:
        return None

    h_rel = [[None] * 8 for _ in range(9)]
    v_rel = [[None] * 9 for _ in range(8)]

    for idx, line in enumerate(lines):
        arr = [ch for ch in line if ch in "<>^v"]
        if len(arr) == 6:
            row = (idx // 5) * 3 + ((idx % 5) // 2)
            cols = [0, 1, 3, 4, 6, 7]
            for col, ch in zip(cols, arr):
                h_rel[row][col] = ch
        elif len(arr) == 9:
            row = (idx // 5) * 3 + ((idx % 5 - 1) // 2)
            for col, ch in enumerate(arr):
                v_rel[row][col] = ch
        else:
            return None

    return h_rel, v_rel


def parse_board(path):
    nums = []
    with open(path, "r", encoding="utf-8") as f:
        for token in f.read().split():
            nums.append(int(token))
    if len(nums) != 81:
        return None

    board = [[0] * 9 for _ in range(9)]
    pos = 0
    for i in range(9):
        for j in range(9):
            board[i][j] = nums[pos]
            pos += 1
    return board


def validate(board, h_rel, v_rel):
    target = set(range(1, 10))

    for i in range(9):
        row = set(board[i])
        if row != target:
            return False, f"row {i + 1} invalid"

    for j in range(9):
        col = set(board[i][j] for i in range(9))
        if col != target:
            return False, f"column {j + 1} invalid"

    for br in range(0, 9, 3):
        for bc in range(0, 9, 3):
            block = set()
            for i in range(br, br + 3):
                for j in range(bc, bc + 3):
                    block.add(board[i][j])
            if block != target:
                return False, f"box ({br // 3 + 1},{bc // 3 + 1}) invalid"

    for i in range(9):
        for j in range(8):
            ch = h_rel[i][j]
            if ch is None:
                continue
            if ch == "<" and not (board[i][j] < board[i][j + 1]):
                return False, f"horizontal relation failed at ({i + 1},{j + 1})"
            if ch == ">" and not (board[i][j] > board[i][j + 1]):
                return False, f"horizontal relation failed at ({i + 1},{j + 1})"

    for i in range(8):
        for j in range(9):
            ch = v_rel[i][j]
            if ch is None:
                continue
            if ch == "^" and not (board[i][j] < board[i + 1][j]):
                return False, f"vertical relation failed at ({i + 1},{j + 1})"
            if ch == "v" and not (board[i][j] > board[i + 1][j]):
                return False, f"vertical relation failed at ({i + 1},{j + 1})"

    return True, "ok"


def main():
    if len(sys.argv) != 4:
        return 2

    parsed = parse_relations(sys.argv[1])
    if parsed is None:
        print("invalid input", file=sys.stderr)
        return 1
    h_rel, v_rel = parsed

    user_board = parse_board(sys.argv[2])
    brute_board = parse_board(sys.argv[3])
    if user_board is None or brute_board is None:
        print("invalid output format", file=sys.stderr)
        return 1

    ok, msg = validate(user_board, h_rel, v_rel)
    if not ok:
        print("user invalid: " + msg, file=sys.stderr)
        return 1

    ok, msg = validate(brute_board, h_rel, v_rel)
    if not ok:
        print("brute invalid: " + msg, file=sys.stderr)
        return 1

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
