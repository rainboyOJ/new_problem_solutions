#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(2, 5)
    cells = []
    for x in range(n):
        for y in range(n):
            for z in range(n):
                cells.append((x, y, z))
    random.shuffle(cells)
    q = random.randint(1, min(len(cells), 40))

    print(n, q)
    for i in range(q):
        print(*cells[i])


if __name__ == "__main__":
    main()
