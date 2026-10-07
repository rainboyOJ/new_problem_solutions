#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 8)
    m = random.randint(1, 8)
    print(n, m)
    for _ in range(max(0, n - 1)):
        print(random.randint(1, 20))
    for _ in range(max(0, m - 1)):
        print(random.randint(1, 20))


if __name__ == "__main__":
    main()
