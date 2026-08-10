#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 10)
    m = random.randint(1, 10)
    print(n, m)
    print(*random.sample(range(1, 100), n))
    for _ in range(m):
        l = random.randint(1, n)
        r = random.randint(l, n)
        print(l, r)


if __name__ == "__main__":
    main()
