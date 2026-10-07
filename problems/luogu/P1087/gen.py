#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(0, 7)
    m = 1 << n
    s = "".join(random.choice("01") for _ in range(m))
    print(n)
    print(s)


if __name__ == "__main__":
    main()
