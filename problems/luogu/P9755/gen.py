#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 8)
    print(n)
    for _ in range(n):
        a = random.randint(1, 80)
        b = random.randint(1, 8)
        c = random.randint(-3, 3)
        print(a, b, c)
    for v in range(2, n + 1):
        u = random.randint(1, v - 1)
        print(u, v)


if __name__ == "__main__":
    main()
