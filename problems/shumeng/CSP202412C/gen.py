#!/usr/bin/env python3
import os
import random


def main():
    seed = os.environ.get("DUPAI_SEED")
    random.seed(None if seed is None else int(seed))
    n = 1 << random.randint(0, 3)
    group_count = 1 << random.randint(0, 3)
    q = random.randint(1, 100)
    print(n, group_count, q)
    for _ in range(q):
        print(random.randint(0, 1), random.randint(0, 200))


if __name__ == "__main__":
    main()
