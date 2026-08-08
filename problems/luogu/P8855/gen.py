#!/usr/bin/env python3
import random


def main():
    random.seed()

    n = random.randint(2, 18)
    print(n)

    for i in range(2, n + 1):
        p = random.randint(1, i - 1)
        print(i, p)

    m = random.randint(1, 20)
    print(m)
    for _ in range(m):
        print(random.randint(1, n))


if __name__ == "__main__":
    main()
