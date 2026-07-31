#!/usr/bin/env python3
import os
import random


def main():
    seed = os.environ.get("DUPAI_SEED")
    random.seed(None if seed is None else int(seed))
    n = random.randint(1, 30)
    m = random.randint(1, 10)
    k = random.randint(1, 40)
    print(n, m, k)
    print(*[random.randint(1, m) for _ in range(n)])
    for operation in range(1, k + 1):
        source = random.randint(1, operation)
        left = random.randint(1, n)
        right = random.randint(left, n)
        print(source, left, right)


if __name__ == "__main__":
    main()
