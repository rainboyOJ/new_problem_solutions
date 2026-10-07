#!/usr/bin/env python3
import random


def random_grid(r, c, p):
    g = []
    for _ in range(r):
        row = []
        for _ in range(c):
            row.append('x' if random.random() < p else '.')
        g.append("".join(row))
    return g


def main():
    q = random.randint(1, 3)
    print(q)
    for _ in range(q):
        n = random.randint(1, 4)
        m = random.randint(1, 4)
        a = random.randint(1, 3)
        b = random.randint(1, 3)
        print(n, m, a, b)
        paper = random_grid(n, m, 0.45)
        stamp = random_grid(a, b, 0.45)
        for row in paper:
            print(row)
        for row in stamp:
            print(row)


if __name__ == "__main__":
    main()
