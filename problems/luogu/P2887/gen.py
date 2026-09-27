#!/usr/bin/env python3
import random


def main():
    random.seed()
    c = random.randint(1, 30)
    l = random.randint(1, 12)
    print(c, l)
    for _ in range(c):
        a = random.randint(1, 20)
        b = random.randint(a, 25)
        print(a, b)
    for _ in range(l):
        spf = random.randint(1, 25)
        cover = random.randint(1, 4)
        print(spf, cover)


if __name__ == "__main__":
    main()
