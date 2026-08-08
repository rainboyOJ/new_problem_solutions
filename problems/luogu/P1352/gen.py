#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 18)
    print(n)
    for _ in range(n):
        print(random.randint(-20, 30))
    for i in range(2, n + 1):
        parent = random.randint(1, i - 1)
        print(i, parent)


if __name__ == "__main__":
    main()
