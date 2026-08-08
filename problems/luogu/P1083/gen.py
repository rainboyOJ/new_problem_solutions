#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 40)
    m = random.randint(1, 40)
    print(n, m)
    rooms = [random.randint(0, 20) for _ in range(n)]
    print(" ".join(map(str, rooms)))
    for _ in range(m):
        l = random.randint(1, n)
        r = random.randint(l, n)
        d = random.randint(0, 20)
        print(d, l, r)


if __name__ == "__main__":
    main()
