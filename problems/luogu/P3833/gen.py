#!/usr/bin/env python3
import random


def main():
    random.seed()

    n = random.randint(2, 18)
    print(n)

    for i in range(1, n):
        p = random.randint(0, i - 1)
        print(p, i)

    q = random.randint(1, 20)
    print(q)

    for _ in range(q):
        if random.randint(0, 1) == 0:
            u = random.randint(0, n - 1)
            v = random.randint(0, n - 1)
            d = random.randint(1, 10)
            print("A", u, v, d)
        else:
            u = random.randint(0, n - 1)
            print("Q", u)


if __name__ == "__main__":
    main()
