#!/usr/bin/env python3

import random


def main():
    coins = [random.randint(1, 8) for _ in range(4)]
    q = random.randint(1, 6)
    print(*coins, q)
    for _ in range(q):
        limits = [random.randint(0, 8) for _ in range(4)]
        s = random.randint(0, 80)
        print(*limits, s)


if __name__ == "__main__":
    main()
