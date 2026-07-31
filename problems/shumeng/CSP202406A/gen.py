#!/usr/bin/env python3
import os
import random


def main():
    seed = os.environ.get("DUPAI_SEED")
    random.seed(None if seed is None else int(seed))
    total = random.randint(1, 100)
    factors = [x for x in range(1, total + 1) if total % x == 0]
    n = random.choice(factors)
    m = total // n
    p = random.choice(factors)
    q = total // p
    print(n, m, p, q)
    for i in range(n):
        print(*[random.randint(-1000, 1000) for _ in range(m)])


if __name__ == "__main__":
    main()
