#!/usr/bin/env python3
import os
import random


def main():
    seed = os.environ.get("DUPAI_SEED")
    random.seed(None if seed is None else int(seed))

    n = random.randint(1, 12)
    print(n)
    for _ in range(n):
        x1 = random.randint(0, 12)
        x2 = random.randint(x1 + 1, 15)
        y1 = random.randint(0, 12)
        y2 = random.randint(y1 + 1, 15)
        print(x1, y1, x2, y2)


if __name__ == "__main__":
    main()
