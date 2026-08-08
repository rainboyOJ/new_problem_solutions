#!/usr/bin/env python3
import random


def main():
    random.seed()

    n = random.randint(2, 8)
    weeks = random.randint(1, 12)
    print(n, weeks)

    for _ in range(weeks):
        u = random.randint(1, n)
        v = random.randint(1, n)
        while u == v:
            v = random.randint(1, n)
        w = random.randint(1, 20)
        print(u, v, w)


if __name__ == "__main__":
    main()
