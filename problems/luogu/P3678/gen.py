#!/usr/bin/env python3
import random


def random_pattern(h: int, w: int):
    return ["".join(random.choice(".+") for _ in range(w)) for _ in range(h)]


def main():
    random.seed()
    win_r = random.randint(1, 3)
    win_c = random.randint(1, 3)
    h = random.randint(1, 4)
    w = random.randint(1, 4)

    patterns = [[random_pattern(h, w) for _ in range(win_c)] for _ in range(win_r)]

    total_r = win_r * h + win_r + 1
    total_c = win_c * w + win_c + 1
    grid = [["#"] * total_c for _ in range(total_r)]

    for i in range(win_r):
        for j in range(win_c):
            sr = 1 + i * (h + 1)
            sc = 1 + j * (w + 1)
            mat = patterns[i][j]
            for x in range(h):
                for y in range(w):
                    grid[sr + x][sc + y] = mat[x][y]

    print(total_r, total_c)
    for row in grid:
        print("".join(row))


if __name__ == "__main__":
    main()
