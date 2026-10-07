#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 14)
    h = random.randint(1, 20)
    print(n)
    print(h)
    for _ in range(h):
        l = random.randint(1, n)
        r = random.randint(l, n)
        need = random.randint(1, r - l + 1)
        print(l, r, need)


if __name__ == "__main__":
    main()
