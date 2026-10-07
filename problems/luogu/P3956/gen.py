#!/usr/bin/env python3
import random


def main():
    random.seed()
    m = random.randint(1, 6)
    cells = []
    for i in range(1, m + 1):
        for j in range(1, m + 1):
            if random.randint(0, 99) < 45:
                cells.append((i, j, random.randint(0, 1)))

    print(m, len(cells))
    for x, y, c in cells:
        print(x, y, c)


if __name__ == "__main__":
    main()
