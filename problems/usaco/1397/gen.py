#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 40)
    q = random.randint(1, 40)
    c = [random.randint(1, 80) for _ in range(n)]
    t = [random.randint(1, 80) for _ in range(n)]

    print(n, q)
    print(*c)
    print(*t)
    for _ in range(q):
        v = random.randint(1, n)
        s = random.randint(1, 80)
        print(v, s)


if __name__ == "__main__":
    main()
