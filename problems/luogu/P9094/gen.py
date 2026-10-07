#!/usr/bin/env python3
import os
import random


def main():
    seed_text = os.environ.get("DUPAI_SEED")
    if seed_text is not None:
        random.seed(int(seed_text))
    else:
        random.seed()

    n = random.randint(1, 20)
    m = random.randint(0, 30)

    print(n, m)
    for _ in range(m):
        l = random.randint(1, n)
        r = random.randint(l, n)
        k = random.randint(1, 3)
        print(l, r, k)


if __name__ == "__main__":
    main()
