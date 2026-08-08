#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 12)
    arr = random.sample(range(1, 80), n)
    print(n)
    for x in arr:
        print(x)


if __name__ == "__main__":
    main()
