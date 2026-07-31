#!/usr/bin/env python3
import os
import random


def main():
    seed = os.environ.get("DUPAI_SEED")
    random.seed(None if seed is None else int(seed))

    n = random.randint(3, 8)
    obstacle = (n, n)
    m = random.randint(1, min(3, n * n - 1))
    positions = [(x, y) for x in range(1, n + 1) for y in range(1, n + 1) if (x, y) != obstacle]
    stores = random.sample(positions, m)
    k = random.randint(1, 8)
    customers = [(random.choice(positions), random.randint(1, 5)) for _ in range(k)]

    print(n, m, k, 1)
    for x, y in stores:
        print(x, y)
    for (x, y), amount in customers:
        print(x, y, amount)
    print(*obstacle)


if __name__ == "__main__":
    main()
