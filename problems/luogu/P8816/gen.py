#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 8)
    k = random.randint(0, 5)
    print(n, k)
    used = set()
    while len(used) < n:
        x = random.randint(1, 8)
        y = random.randint(1, 8)
        used.add((x, y))
    for x, y in used:
        print(x, y)


if __name__ == "__main__":
    main()
