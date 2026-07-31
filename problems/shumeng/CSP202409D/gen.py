#!/usr/bin/env python3
import os
import random


def main():
    seed = os.environ.get("DUPAI_SEED")
    random.seed(None if seed is None else int(seed))
    n = random.randint(2, 10)
    m = random.randint(1, 10)
    print(n, m)
    for _ in range(n):
        print(random.randint(0, 20), random.randint(0, 20))
    for _ in range(m):
        print(random.randint(0, 20), random.randint(0, 20), random.randint(0, 8), random.randint(1, 20))


if __name__ == "__main__":
    main()
