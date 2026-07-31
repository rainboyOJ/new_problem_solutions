#!/usr/bin/env python3
import os
import random


def main():
    seed = os.environ.get("DUPAI_SEED")
    random.seed(None if seed is None else int(seed))
    m = random.randint(1, 12)
    left = random.randint(0, 80)
    right = random.randint(left, min(100, left + 20))
    print(m, left, right)
    print(*[random.randint(0, 20) for _ in range(m)])


if __name__ == "__main__":
    main()
