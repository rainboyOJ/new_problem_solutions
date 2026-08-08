#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 7)
    h = random.randint(1, 40)
    print(n, h)
    for _ in range(n):
        print(random.randint(1, 15), random.randint(1, 30))


if __name__ == "__main__":
    main()
