#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 12)
    q = random.randint(1, 20)
    colors = "ABCD"
    s = "".join(random.choice(colors) for _ in range(n))
    print(n, q)
    print(s)
    for _ in range(q):
        a = random.randint(1, n)
        b = random.randint(a, n)
        print(a, b)


if __name__ == "__main__":
    main()
