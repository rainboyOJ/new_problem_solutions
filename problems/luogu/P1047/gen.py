#!/usr/bin/env python3
import random


def main():
    random.seed()
    l = random.randint(1, 30)
    m = random.randint(1, 10)
    print(l, m)
    for _ in range(m):
        u = random.randint(0, l)
        v = random.randint(u, l)
        print(u, v)


if __name__ == "__main__":
    main()
