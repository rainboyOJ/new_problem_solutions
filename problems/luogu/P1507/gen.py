#!/usr/bin/env python3
import random


def main():
    random.seed()
    H = random.randint(1, 20)
    T = random.randint(1, 20)
    n = random.randint(1, 12)
    print(H, T)
    print(n)
    for _ in range(n):
        hh = random.randint(1, 20)
        tt = random.randint(1, 20)
        kk = random.randint(1, 50)
        print(hh, tt, kk)


if __name__ == "__main__":
    main()
