#!/usr/bin/env python3
import random


def main():
    random.seed()

    n = random.randint(1, 64)
    if n == 64:
        k = random.randint(0, (1 << 64) - 1)
    else:
        k = random.randint(0, (1 << n) - 1)

    print(n, k)


if __name__ == "__main__":
    main()
