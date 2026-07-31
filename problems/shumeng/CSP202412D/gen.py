#!/usr/bin/env python3
import os
import random


def main():
    seed = os.environ.get("DUPAI_SEED")
    random.seed(None if seed is None else int(seed))
    n = random.randint(1, 35)
    a = [0]
    for i in range(1, n + 1):
        a.append(random.randint(0, i - 1))
    a[n] = 0
    k = [0] + [random.randint(1, 2 * n) for _ in range(n)]
    print(n)
    print(*a[1:])
    print(*k[1:])


if __name__ == "__main__":
    main()
