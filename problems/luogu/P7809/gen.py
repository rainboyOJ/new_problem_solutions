#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 40)
    m = random.randint(1, 60)
    print(n, m)
    arr = [random.randint(0, 1) for _ in range(n)]
    print(*arr)
    for _ in range(m):
        op = random.randint(1, 2)
        l = random.randint(1, n)
        r = random.randint(l, n)
        print(op, l, r)


if __name__ == "__main__":
    main()
