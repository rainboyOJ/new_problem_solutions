#!/usr/bin/env python3
import random


def main():
    random.seed()

    n = random.randint(2, 100)
    k = random.randint(2, 100)
    print(n, k)


if __name__ == "__main__":
    main()
