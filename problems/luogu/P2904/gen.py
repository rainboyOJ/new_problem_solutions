#!/usr/bin/env python3
import random


def main():
    random.seed()

    n = random.randint(1, 10)
    m = random.randint(1, 20)
    print(n, m)
    for _ in range(n):
        print(random.randint(1, 20))


if __name__ == "__main__":
    main()
