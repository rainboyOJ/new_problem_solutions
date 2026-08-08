#!/usr/bin/env python3
import random


def main():
    random.seed()

    n = random.randint(1, 8)
    d = random.randint(1, 8)
    print(n, d)
    for _ in range(n):
        print(random.randint(1, 30))


if __name__ == "__main__":
    main()
