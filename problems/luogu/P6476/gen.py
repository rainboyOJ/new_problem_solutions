#!/usr/bin/env python3
import random


def main():
    random.seed()
    t = random.randint(1, 5)
    print(t)
    for _ in range(t):
        p1 = random.randint(1, 8)
        p2 = random.randint(1, 8)
        k = random.randint(1, 8)
        print(p1, p2, k)


if __name__ == "__main__":
    main()
