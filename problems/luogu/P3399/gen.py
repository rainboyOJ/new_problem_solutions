#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 8)
    m = random.randint(n, 10)
    print(n, m)
    for _ in range(n):
        print(random.randint(1, 10))
    for _ in range(m):
        print(random.randint(1, 10))


if __name__ == "__main__":
    main()
