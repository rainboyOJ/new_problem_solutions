#!/usr/bin/env python3

import random


def main():
    n = random.randint(1, 7)
    m = random.randint(1, 6)
    k = random.randint(0, n * m)
    p = random.randint(0, n)
    print(n, m, k, p)


if __name__ == "__main__":
    main()
