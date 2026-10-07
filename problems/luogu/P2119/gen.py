#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 30)
    m = random.randint(1, 8)
    print(n, m)
    for _ in range(m):
        print(random.randint(1, n))


if __name__ == "__main__":
    main()
