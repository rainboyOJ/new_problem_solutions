#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 12)
    s = random.randint(1, n)
    t = random.randint(1, n)
    print(n, s, t)
    print(*[random.randint(0, n) for _ in range(n)])


if __name__ == "__main__":
    main()
