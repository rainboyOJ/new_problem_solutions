#!/usr/bin/env python3
import random


def main():
    n = random.randint(1, 50)
    print(n)
    x = 0
    for _ in range(n):
        x += random.randint(1, 8)
        p = random.randint(0, 20)
        c = random.randint(0, 30)
        print(x, p, c)


if __name__ == "__main__":
    main()
