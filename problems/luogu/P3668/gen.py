#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 60)
    print(n)
    for _ in range(n):
        print(random.randint(0, n))


if __name__ == "__main__":
    main()
