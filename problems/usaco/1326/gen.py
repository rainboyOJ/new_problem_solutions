#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 25)
    a = [random.randint(0, 40) for _ in range(n)]
    q = random.randint(1, 25)

    print(n)
    print(*a)
    print(q)
    for _ in range(q):
        idx = random.randint(1, n)
        val = random.randint(0, 40)
        print(idx, val)


if __name__ == "__main__":
    main()
