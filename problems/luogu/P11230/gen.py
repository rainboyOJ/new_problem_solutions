#!/usr/bin/env python3
import random


def main():
    t = 1
    print(t)
    n = random.randint(1, 6)
    k = random.randint(2, 6)
    q = random.randint(1, 20)
    print(n, k, q)

    for _ in range(n):
        length = random.randint(1, 8)
        arr = [random.randint(1, 12) for _ in range(length)]
        print(length, *arr)

    for _ in range(q):
        r = random.randint(1, 8)
        c = random.randint(1, 12)
        print(r, c)


if __name__ == "__main__":
    main()
