#!/usr/bin/env python3
import random
import sys


def build_valid(n, a, b):
    first = [[random.choice([False, True]) for _ in range(n)] for _ in range(n)]
    second = [[False for _ in range(n)] for _ in range(n)]

    for r in range(n):
        for c in range(n):
            if not first[r][c]:
                continue
            if random.choice([False, True]):
                nr = r + b
                nc = c + a
                if 0 <= nr < n and 0 <= nc < n:
                    second[nr][nc] = True

    rows = []
    for r in range(n):
        row = []
        for c in range(n):
            if first[r][c] and second[r][c]:
                row.append("B")
            elif first[r][c] or second[r][c]:
                row.append("G")
            else:
                row.append("W")
        rows.append("".join(row))
    return rows


def build_random(n):
    rows = []
    for _ in range(n):
        rows.append("".join(random.choice(["W", "G", "B"]) for _ in range(n)))
    return rows


def main():
    random.seed()
    max_n = 3
    max_t = 4
    if len(sys.argv) >= 2:
        max_n = int(sys.argv[1])
    if len(sys.argv) >= 3:
        max_t = int(sys.argv[2])

    t = random.randint(1, max_t)
    print(t)
    for _ in range(t):
        n = random.randint(1, max_n)
        a = random.randint(0, n)
        b = random.randint(0, n)
        if random.choice([False, True]):
            rows = build_valid(n, a, b)
        else:
            rows = build_random(n)

        print(n, a, b)
        for row in rows:
            print(row)


if __name__ == "__main__":
    main()
