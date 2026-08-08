#!/usr/bin/env python3
import random

SUITS = ["C", "H", "S", "D"]
POINTS = ["A", "2", "3", "4", "5", "6", "7", "8", "9", "T", "J", "Q", "K"]
KINDS = [
    "K", "M", "P", "W", "B", "A", "S", "C", "G", "D", "U", "T", "N", "F", "E",
    "I", "K", "L", "+", "-", "LN", "QG", "GD", "HB", "CX", "WL", "QL", "ZB",
    "GS", "FT", "YS", "LG", "RW", "BZ", "TJ", "SZ",
]


def random_card():
    return random.choice(SUITS) + random.choice(POINTS), random.choice(KINDS)


def main():
    random.seed()

    n = random.randint(1, 6)
    k = random.randint(1, 20)
    m = random.randint(1, 8)
    p = random.randint(1, n)

    print(n, k, m, p)
    for _ in range(k):
        a, b = random_card()
        print(a, b)


if __name__ == "__main__":
    main()
