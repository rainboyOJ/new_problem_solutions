#!/usr/bin/env python3
import random


def main():
    random.seed()
    t = random.randint(1, 5)
    print(t)
    for _ in range(t):
        n = random.randint(1, 8)
        print(n)
        for _ in range(n):
            print(random.randint(1, 20), random.randint(1, 20))


if __name__ == "__main__":
    main()
