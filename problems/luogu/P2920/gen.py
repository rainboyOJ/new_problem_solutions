#!/usr/bin/env python3
import random


def main():
    random.seed()

    n = random.randint(1, 7)
    print(n)
    for _ in range(n):
        t = random.randint(1, 8)
        s = random.randint(1, 35)
        print(t, s)


if __name__ == "__main__":
    main()
