#!/usr/bin/env python3
import random


def main():
    random.seed()
    m = random.randint(3, 12)
    n = random.randint(1, m)
    print(n, m)


if __name__ == "__main__":
    main()
