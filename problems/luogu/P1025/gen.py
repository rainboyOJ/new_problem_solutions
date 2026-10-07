#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(7, 30)
    k = random.randint(2, min(6, n))
    print(n, k)


if __name__ == "__main__":
    main()
