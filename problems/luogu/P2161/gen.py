#!/usr/bin/env python3
import random
import sys


def main():
    n = random.randint(1, 15)
    print(n)
    for _ in range(n):
        if random.random() < 0.2:
            print("B")
        else:
            l = random.randint(1, 10)
            r = random.randint(l, 10)
            print("A", l, r)


if __name__ == "__main__":
    main()
