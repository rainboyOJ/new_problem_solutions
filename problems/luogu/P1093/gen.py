#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(5, 20)
    print(n)
    for _ in range(n):
        print(random.randint(0, 100), random.randint(0, 100), random.randint(0, 100))


if __name__ == "__main__":
    main()
