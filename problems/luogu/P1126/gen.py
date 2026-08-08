#!/usr/bin/env python3
import random


def main():
    random.seed()

    n = random.randint(2, 7)
    m = random.randint(2, 7)
    print(n, m)

    for _ in range(n):
        row = [str(random.randint(0, 1)) for _ in range(m)]
        print(" ".join(row))

    sx = random.randint(1, n - 1)
    sy = random.randint(1, m - 1)
    tx = random.randint(1, n - 1)
    ty = random.randint(1, m - 1)
    d = random.choice(["E", "S", "W", "N"])
    print(sx, sy, tx, ty, d)


if __name__ == "__main__":
    main()
