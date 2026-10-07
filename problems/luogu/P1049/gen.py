#!/usr/bin/env python3
import random


def main():
    random.seed()

    capacity = random.randint(1, 40)
    n = random.randint(1, 15)
    print(capacity)
    print(n)
    for _ in range(n):
        print(random.randint(1, 25))


if __name__ == "__main__":
    main()
