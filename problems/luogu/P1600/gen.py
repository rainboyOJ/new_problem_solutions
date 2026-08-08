#!/usr/bin/env python3
import random


def main():
    random.seed()

    n = random.randint(2, 18)
    m = random.randint(1, 20)
    print(n, m)

    for i in range(2, n + 1):
        p = random.randint(1, i - 1)
        print(i, p)

    w = [str(random.randint(0, n)) for _ in range(n)]
    print(" ".join(w))

    for _ in range(m):
        s = random.randint(1, n)
        t = random.randint(1, n)
        print(s, t)


if __name__ == "__main__":
    main()
