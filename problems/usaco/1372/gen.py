#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 20)
    start = random.randint(1, n)
    print(n, start)
    for _ in range(n):
        q = random.randint(0, 1)
        v = random.randint(0, n)
        print(q, v)


if __name__ == "__main__":
    main()
