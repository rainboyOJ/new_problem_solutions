#!/usr/bin/env python3
import random


def main():
    random.seed()

    k = random.randint(0, 10)
    total = 1 << k

    n = random.randint(0, min(total, 10))
    c = random.randint(1, 8)
    m = 0 if k == 0 else random.randint(0, 15)

    animals = random.sample(range(total), n)

    print(n, m, c, k)
    if n > 0:
        print(" ".join(map(str, animals)))
    else:
        print()

    for _ in range(m):
        p = random.randint(0, k - 1)
        q = random.randint(1, c)
        print(p, q)


if __name__ == "__main__":
    main()
