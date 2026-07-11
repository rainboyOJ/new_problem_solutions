#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 30)
    k = random.randint(1, n)
    t = random.randint(1, 200)
    rest = random.sample(range(1, n), k - 1)
    a = [0] + sorted(rest)

    print(n, k, t)
    print(*a)


if __name__ == "__main__":
    main()
