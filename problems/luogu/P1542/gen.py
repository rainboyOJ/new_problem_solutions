#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 12)
    print(n)

    cur_l = 0
    for _ in range(n):
        l = cur_l + random.randint(0, 10)
        r = l + random.randint(0, 10)
        s = random.randint(1, 20)
        print(l, r, s)
        cur_l = l


if __name__ == "__main__":
    main()
