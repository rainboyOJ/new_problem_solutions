#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 50)
    k = random.randint(1, 300)
    print(n, k)


if __name__ == "__main__":
    main()
