#!/usr/bin/env python3
import random


def main():
    random.seed()

    n = random.randint(1, 3)
    m = random.randint(1, 3)
    c = random.randint(1, 3)

    print(n, m, c)


if __name__ == "__main__":
    main()
