#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 8)
    t = random.randint(1, 12)
    m = random.randint(1, 20)

    print(n, m, t)
    for _ in range(m):
        ts = random.randint(1, t)
        idx = random.randint(1, n)
        print(ts, idx)


if __name__ == "__main__":
    main()
