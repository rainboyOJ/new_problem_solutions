#!/usr/bin/env python3
import os
import random


def main():
    seed = os.environ.get("DUPAI_SEED")
    random.seed(None if seed is None else int(seed))
    n = random.randint(1, 30)
    print(n)
    print(*[random.randint(1, n) for _ in range(n)])


if __name__ == "__main__":
    main()
