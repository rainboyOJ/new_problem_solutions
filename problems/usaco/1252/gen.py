#!/usr/bin/env python3
import random


def main():
    random.seed()
    t = random.randint(1, 8)
    print(t)
    for _ in range(t):
        n = random.randint(1, 8)
        k = random.randint(0, n - 1)
        s = "".join(random.choice("GH") for _ in range(n))
        print(n, k)
        print(s)


if __name__ == "__main__":
    main()
