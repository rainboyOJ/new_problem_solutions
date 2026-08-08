#!/usr/bin/env python3
import random


def main():
    random.seed()

    n = random.randint(1, 8)
    limit_c = random.randint(1, 30)
    print(n, limit_c)

    used = set()
    for _ in range(n):
        while True:
            x = random.randint(0, 8)
            y = random.randint(0, 8)
            if (x, y) not in used:
                used.add((x, y))
                print(x, y)
                break


if __name__ == "__main__":
    main()
