#!/usr/bin/env python3
import random


def main():
    random.seed()
    m = random.randint(1, 6)
    n = random.randint(m, 12)
    print(n, m)


if __name__ == "__main__":
    main()
