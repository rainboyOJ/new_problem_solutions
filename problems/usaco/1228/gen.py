#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 30)
    print(n)
    for _ in range(n):
        c = random.choice("GL")
        p = random.randint(0, 100)
        print(c, p)


if __name__ == "__main__":
    main()
