#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 8)
    mod = random.randint(2, 1000)
    print(n, mod)


if __name__ == "__main__":
    main()
