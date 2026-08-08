#!/usr/bin/env python3

import random


def main():
    n = random.randint(2, 6)
    total = n * n
    m = random.randint(0, total)

    cells = [(i, j) for i in range(1, n + 1) for j in range(1, n + 1)]
    random.shuffle(cells)
    transfer = cells[:m]

    s = random.choice(cells)
    t = random.choice(cells)

    print(n, m)
    for x, y in transfer:
        print(x, y)
    print(s[0], s[1], t[0], t[1])


if __name__ == "__main__":
    main()
