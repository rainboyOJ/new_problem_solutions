#!/usr/bin/env python3
import os
import random


def main():
    seed = os.environ.get("DUPAI_SEED")
    random.seed(None if seed is None else int(seed))

    n = random.randint(2, 5)
    m = random.randint(2, 5)
    q = random.randint(2, 50)
    a = random.randint(1, 50)
    b = random.randint(1, 50)
    x0 = random.randint(1, q - 1)
    print(n, m, a, b, q, x0)


if __name__ == "__main__":
    main()
