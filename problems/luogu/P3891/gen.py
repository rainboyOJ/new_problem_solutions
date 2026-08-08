#!/usr/bin/env python3
import random


def main():
    n = random.randint(1, 4)
    target = random.randint(2, 18)
    m = random.randint(1, target)
    print(n, m, target)
    for _ in range(n):
        a = random.randint(1, target)
        b = random.randint(1, 8)
        print(a, b)


if __name__ == "__main__":
    main()
