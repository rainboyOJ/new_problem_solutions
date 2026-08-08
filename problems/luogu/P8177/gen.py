#!/usr/bin/env python3
import random


def main():
    random.seed()
    t = random.randint(1, 10)
    print(t)
    for _ in range(t):
        n = random.randint(2, 8)
        a = random.randint(-20, 20)
        d = random.randint(1, 12)
        print(n, a, d)


if __name__ == "__main__":
    main()
