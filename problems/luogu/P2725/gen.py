#!/usr/bin/env python3
import random


def main():
    random.seed()

    k = random.randint(1, 5)
    n = random.randint(1, 5)
    a = sorted({random.randint(1, 10) for _ in range(n)})
    n = len(a)

    print(k, n)
    print(*a)


if __name__ == "__main__":
    main()
