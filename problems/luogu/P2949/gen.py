#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 18)
    print(n)
    for _ in range(n):
        print(random.randint(1, 20), random.randint(1, 100))


if __name__ == "__main__":
    main()
