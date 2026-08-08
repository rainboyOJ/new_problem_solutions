#!/usr/bin/env python3

import random


def main():
    t = random.randint(1, 8)
    print(t)
    for _ in range(t):
        n = random.randint(1, 200)
        m = random.randint(2, 30)
        print(n, m)


if __name__ == "__main__":
    main()
