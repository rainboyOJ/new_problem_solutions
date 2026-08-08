#!/usr/bin/env python3
import os
import random


def main():
    seed_text = os.environ.get("DUPAI_SEED")
    if seed_text is not None:
        random.seed(int(seed_text))
    else:
        random.seed()

    n = random.randint(1, 12)
    m = random.randint(0, 20)

    print(n, m)
    for _ in range(m):
        x1 = random.randint(1, n)
        x2 = random.randint(x1, n)
        y1 = random.randint(1, n)
        y2 = random.randint(y1, n)
        print(x1, y1, x2, y2)


if __name__ == "__main__":
    main()
