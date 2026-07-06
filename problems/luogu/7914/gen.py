#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 10)
    k = random.randint(1, n)
    chars = ["(", ")", "*", "?"]
    s = "".join(random.choice(chars) for _ in range(n))
    print(n, k)
    print(s)


if __name__ == "__main__":
    main()
