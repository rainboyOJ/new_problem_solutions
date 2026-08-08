#!/usr/bin/env python3

import random


def main():
    n = random.randint(2, 8)
    print(n)

    for i in range(1, n + 1):
        s = random.randint(1, 12)
        k = random.randint(1, 20)
        r = random.randint(0, 3)
        childs = [random.randint(1, n) for _ in range(r)]
        print(s, k, r, *childs)


if __name__ == "__main__":
    main()
