#!/usr/bin/env python3
import random
import os


def main():
    seed = os.environ.get("DUPAI_SEED")
    random.seed(None if seed is None else int(seed))
    n = random.randint(1, 6)
    m = random.randint(0, 10)
    print(n, m)
    for _ in range(n):
        left = random.randint(1, 3)
        right = left + random.randint(2, 3)
        print(left, right, random.randint(-5, 5), random.randint(-10, 10), random.randint(-10, 10))
    for _ in range(m):
        print(random.randint(1, 2), random.randint(1, n), random.randint(1, n))


if __name__ == "__main__":
    main()
