#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 30)
    m = random.randint(1, n)
    print(n, m)
    for _ in range(n):
        print(random.randint(1, 100))


if __name__ == "__main__":
    main()
