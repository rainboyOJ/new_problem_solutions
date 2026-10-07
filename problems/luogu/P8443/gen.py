#!/usr/bin/env python3
import random


def main():
    random.seed()
    t = random.randint(1, 20)
    print(t)
    for _ in range(t):
        x = random.randint(1, 20)
        l = random.randint(x, 100)
        r = random.randint(l, min(100, l + 30))
        print(l, r, x)


if __name__ == "__main__":
    main()
