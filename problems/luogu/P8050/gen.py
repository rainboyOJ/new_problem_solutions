#!/usr/bin/env python3
import random


def build_shape():
    if random.randint(0, 1) == 0:
        n1, m1 = 0, 0
        n2 = random.randint(1, 5)
        m2 = random.randint(1, 5)
    else:
        n1 = random.randint(1, 4)
        m1 = random.randint(1, 4)
        n2 = random.randint(1, 5)
        m2 = random.randint(m1 + 1, 6)
    return n1, m1, n2, m2


def row_len(row, top_rows, m1, m2):
    if row <= top_rows:
        return m1
    return m2


def neighbors(r, c, top_rows, total_rows, m1, m2):
    dirs = [(0, 1), (1, 0), (0, -1), (-1, 0)]
    res = []
    for dr, dc in dirs:
        nr, nc = r + dr, c + dc
        if nr < 1 or nr > total_rows:
            continue
        if nc < 1 or nc > row_len(nr, top_rows, m1, m2):
            continue
        res.append((nr, nc))
    return res


def main():
    random.seed()

    n1, m1, n2, m2 = build_shape()
    top_rows = n1 if n1 > 0 and m1 > 0 else 0
    total_rows = top_rows + n2
    k = random.randint(-5, 5)

    board = []
    for i in range(1, total_rows + 1):
        board.append([k] * row_len(i, top_rows, m1, m2))

    edges = []
    for i in range(1, total_rows + 1):
        limit = row_len(i, top_rows, m1, m2)
        for j in range(1, limit + 1):
            if j + 1 <= limit:
                edges.append((i, j, i, j + 1))
            if i + 1 <= total_rows and j <= row_len(i + 1, top_rows, m1, m2):
                edges.append((i, j, i + 1, j))

    q = random.randint(0, 30)
    if edges:
        for _ in range(q):
            x1, y1, x2, y2 = random.choice(edges)
            delta = random.choice([-1, 1])
            board[x1 - 1][y1 - 1] += delta
            board[x2 - 1][y2 - 1] += delta

    all_cells = []
    for i in range(1, total_rows + 1):
        for j in range(1, row_len(i, top_rows, m1, m2) + 1):
            all_cells.append((i, j))
    mx, my = random.choice(all_cells)
    board[mx - 1][my - 1] = 999999

    print(n1, m1, n2, m2, k)
    for row in board:
        print(*row)


if __name__ == "__main__":
    main()
