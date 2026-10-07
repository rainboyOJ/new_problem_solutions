#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(2, 20)
    q = random.randint(1, 20)
    k = random.randint(1, 3)
    print(n, q, k)
    print(*[random.randint(1, 30) for _ in range(n)])
    for v in range(2, n + 1):
        u = random.randint(1, v - 1)
        print(u, v)
    for _ in range(q):
        s = random.randint(1, n)
        t = random.randint(1, n)
        while t == s:
            t = random.randint(1, n)
        print(s, t)


if __name__ == "__main__":
    main()
