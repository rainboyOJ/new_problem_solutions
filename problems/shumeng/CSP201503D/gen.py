#!/usr/bin/env python3
import os
import random


def main():
    seed = os.environ.get("DUPAI_SEED")
    random.seed(None if seed is None else int(seed))
    n = random.randint(1, 20)
    m = random.randint(1, 20)
    print(n, m)
    if n > 1:
        print(*[random.randint(1, child - 1) for child in range(2, n + 1)])
    else:
        print()
    print(*[random.randint(1, n) for _ in range(m)])


if __name__ == "__main__":
    main()
