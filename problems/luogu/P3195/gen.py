#!/usr/bin/env python3
import random


def main():
    n = random.randint(1, 60)
    L = random.randint(1, 30)
    print(n, L)
    for _ in range(n):
        print(random.randint(1, 20))


if __name__ == "__main__":
    main()
