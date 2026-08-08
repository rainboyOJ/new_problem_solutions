#!/usr/bin/env python3
import random


def gen_case():
    n = random.randint(1, 6)
    m = random.randint(1, 6)
    g = []
    for _ in range(n):
        row = []
        for _ in range(m):
            row.append("#" if random.randint(0, 99) < 35 else ".")
        g.append(row)

    sx = random.randint(0, n - 1)
    sy = random.randint(0, m - 1)
    g[sx][sy] = "S"

    print(n, m)
    for i in range(n):
        print("".join(g[i]))


def main():
    random.seed()
    t = random.randint(1, 4)
    for _ in range(t):
        gen_case()


if __name__ == "__main__":
    main()
