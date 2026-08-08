#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 8)
    k = random.randint(1, 7)
    d = random.randint(1, 10)
    s = random.randint(1, 10)
    print(n, k, d, s)
    for _ in range(k):
        ti = random.randint(1, s)
        zi = random.randint(1, 4)
        print(ti, zi)


if __name__ == "__main__":
    main()
