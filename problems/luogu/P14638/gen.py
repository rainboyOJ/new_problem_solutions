#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 35)
    q = random.randint(1, 30)

    print(n)
    print(" ".join(str(random.randint(-20, 20)) for _ in range(n)))
    print(q)
    for _ in range(q):
        l = random.randint(1, n)
        r = random.randint(l, n)
        print(l, r)


if __name__ == "__main__":
    main()
