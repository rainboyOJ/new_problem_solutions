#!/usr/bin/env python3
import random


def main():
    suits = "DCHS"
    ranks = "A23456789TJQK"
    cards = [s + r for s in suits for r in ranks]
    n = random.randint(1, 52)
    print(n)
    for _ in range(n):
        print(random.choice(cards))


if __name__ == "__main__":
    main()
