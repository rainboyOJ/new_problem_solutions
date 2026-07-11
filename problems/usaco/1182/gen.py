#!/usr/bin/env python3
import random


def main():
    random.seed()
    t = random.randint(1, 10)
    print(t)
    for _ in range(t):
        a = random.randint(1, 200)
        b = random.randint(1, 200)
        print(a, b)


if __name__ == "__main__":
    main()
