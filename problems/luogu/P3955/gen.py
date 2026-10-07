#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 30)
    q = random.randint(1, 30)
    print(n, q)
    for _ in range(n):
        print(random.randint(1, 10**7))
    for _ in range(q):
        length = random.randint(1, 8)
        limit = min(10**length - 1, 10**7)
        need = random.randint(1, limit)
        print(length, need)


if __name__ == "__main__":
    main()
