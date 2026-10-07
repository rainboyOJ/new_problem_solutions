#!/usr/bin/env python3
import random


def main():
    n = random.randint(1, 60)
    s = random.randint(1, 15)
    print(n)
    print(s)
    for _ in range(n):
        ti = random.randint(1, 15)
        ci = random.randint(0, 15)
        print(ti, ci)


if __name__ == "__main__":
    main()
