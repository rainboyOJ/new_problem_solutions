#!/usr/bin/env python3
import random


def main():
    random.seed()
    t = random.randint(1, 3)
    print(t)
    for _ in range(t):
        n = random.randint(2, 12)
        print(n)
        for v in range(2, n + 1):
            u = random.randint(1, v - 1)
            print(u, v)


if __name__ == "__main__":
    main()
