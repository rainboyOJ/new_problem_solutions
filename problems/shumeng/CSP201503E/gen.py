#!/usr/bin/env python3
import os
import random


def main():
    seed = os.environ.get("DUPAI_SEED")
    random.seed(None if seed is None else int(seed))
    n = random.randint(1, 20)
    m = random.randint(1, 40)
    print(n, m)
    print(*[random.randint(1, 30) for _ in range(n)])
    for child in range(2, n + 1):
        print(random.randint(1, child - 1), child, random.randint(1, 20))
    for _ in range(m):
        print(random.randint(1, n), random.randint(1, n))


if __name__ == "__main__":
    main()
