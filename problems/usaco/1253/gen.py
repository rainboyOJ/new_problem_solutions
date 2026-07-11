#!/usr/bin/env python3
import random


def main():
    random.seed()
    t = random.randint(1, 6)
    print(t)
    print()
    for case in range(t):
        n = random.randint(1, 3)
        m = random.randint(1, 8)
        print(n, m)
        for _ in range(m):
            s = "".join(random.choice("01") for _ in range(n))
            out = random.choice("01")
            print(s, out)
        if case + 1 < t:
            print()


if __name__ == "__main__":
    main()
