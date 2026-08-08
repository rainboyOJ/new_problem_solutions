#!/usr/bin/env python3
import random


def main():
    random.seed()
    t = random.randint(1, 5)
    print(t)
    for _ in range(t):
        n = random.randint(1, 6)
        k = random.randint(1, 9)
        print(n, k)


if __name__ == "__main__":
    main()
