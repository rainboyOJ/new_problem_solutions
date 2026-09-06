#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 12)
    k = random.randint(1, n)
    print(n, k)
    print(*[random.randint(1, 63) for _ in range(n)])


if __name__ == "__main__":
    main()
