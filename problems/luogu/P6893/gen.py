#!/usr/bin/env python3
import random


def main():
    n = random.randint(1, 6)
    w = random.randint(1, 20)
    print(n, w)
    for _ in range(n):
        if random.randint(0, 1) == 0:
            weight = random.randint(1, 8)
            t = random.randint(1, 12)
            d = random.randint(0, 4)
            print("D", weight, t, d)
        else:
            t = random.randint(1, 12)
            d = random.randint(0, 4)
            print("C", t, d)


if __name__ == "__main__":
    main()
