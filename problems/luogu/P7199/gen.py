#!/usr/bin/env python3
import random


def main():
    random.seed()
    q = random.randint(1, 10)
    print(q)
    for _ in range(q):
        l = random.randint(1, 200)
        r = random.randint(l, 200)
        print(l, r)


if __name__ == "__main__":
    main()
