#!/usr/bin/env python3
import random
import os


def main():
    seed = os.environ.get("DUPAI_SEED")
    random.seed(None if seed is None else int(seed))

    n = random.randint(1, 30)
    query_count = random.randint(1, 50)
    print(n, query_count)
    for _ in range(query_count):
        left = random.randint(1, n)
        right = random.randint(1, n)
        if left > right:
            left, right = right, left
        print(left, right)


if __name__ == "__main__":
    main()
