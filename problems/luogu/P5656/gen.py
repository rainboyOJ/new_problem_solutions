#!/usr/bin/env python3

import random


def main():
    T = random.randint(1, 5)
    print(T)
    for _ in range(T):
        a = random.randint(1, 20)
        b = random.randint(1, 20)
        c = random.randint(1, 200)
        print(a, b, c)


if __name__ == "__main__":
    main()
