#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 8)
    m = random.randint(1, n)
    s = "".join(random.choice("01") for _ in range(n))
    c = [str(random.randint(0, n)) for _ in range(n)]

    print(n, m)
    print(s)
    print(" ".join(c))


if __name__ == "__main__":
    main()
