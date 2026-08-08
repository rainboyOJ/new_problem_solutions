#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 12)
    print(n)
    for _ in range(n):
        print(random.randint(-10, 10))


if __name__ == "__main__":
    main()
