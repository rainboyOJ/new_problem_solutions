#!/usr/bin/env python3
import random


def main():
    random.seed()
    t = random.randint(1, 8)
    print(t)
    for _ in range(t):
        n = random.randint(1, 6)
        m = random.randint(1, 7)
        print(n, m)


if __name__ == "__main__":
    main()
