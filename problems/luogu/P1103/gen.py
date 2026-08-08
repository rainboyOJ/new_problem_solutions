#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 10)
    k = random.randint(0, n - 1)
    print(n, k)

    heights = random.sample(range(1, 100), n)
    for h in heights:
        w = random.randint(1, 20)
        print(h, w)


if __name__ == "__main__":
    main()
