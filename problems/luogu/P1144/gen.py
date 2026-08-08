#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 30)
    m = random.randint(1, 120)

    print(n, m)
    for _ in range(m):
        u = random.randint(1, n)
        v = random.randint(1, n)
        while n > 1 and v == u:
            v = random.randint(1, n)
        print(u, v)


if __name__ == "__main__":
    main()
