#!/usr/bin/env python3
import random


def main():
    random.seed()

    n = random.randint(1, 6)
    print(n)
    for _ in range(n):
        h = random.randint(1, 10)
        c = random.randint(1, 3)
        a = random.randint(h, 30)
        print(h, a, c)


if __name__ == "__main__":
    main()
