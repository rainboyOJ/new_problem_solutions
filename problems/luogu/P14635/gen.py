#!/usr/bin/env python3
import random


def main():
    n = random.randint(1, 8)
    m = random.randint(1, 80)
    print(n, m)
    for _ in range(n):
        x = random.randint(1, 30)
        y = random.randint(1, 30)
        print(x, y)


if __name__ == "__main__":
    main()
