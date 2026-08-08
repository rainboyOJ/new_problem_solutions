#!/usr/bin/env python3
import random


def main():
    random.seed()

    n = random.randint(1, 50)
    p = random.randint(1, n)
    print(n, p)
    print(" ".join(str(random.randint(0, 100)) for _ in range(n)))

    for _ in range(p):
        l = random.randint(1, n)
        r = random.randint(l, n)
        z = random.randint(0, 100)
        print(l, r, z)


if __name__ == "__main__":
    main()
