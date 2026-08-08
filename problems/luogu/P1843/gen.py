#!/usr/bin/env python3
import random


def main():
    random.seed()

    n = random.randint(1, 50)
    a = random.randint(1, 10)
    b = random.randint(1, 10)
    print(n, a, b)
    for _ in range(n):
        print(random.randint(1, 200))


if __name__ == "__main__":
    main()
