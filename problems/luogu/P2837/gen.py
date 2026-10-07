#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 30)
    print(n)
    for _ in range(n):
        print(random.randint(1, 2))


if __name__ == "__main__":
    main()
