#!/usr/bin/env python3
import random
import sys


def main():
    if len(sys.argv) > 1:
        random.seed(int(sys.argv[1]))
    else:
        random.seed()

    n = random.randint(1, 20)
    m = random.randint(1, 40)
    print(n, m)

    for _ in range(m):
        op = random.randint(0, 2)
        if op == 0:
            l = random.randint(1, n)
            r = random.randint(l, n)
            print(0, l, r)
        elif op == 1:
            x1 = random.randint(1, n)
            y1 = random.randint(x1, n)
            x2 = random.randint(1, n)
            y2 = random.randint(x2, n)
            print(1, x1, y1, x2, y2)
        else:
            l = random.randint(1, n)
            r = random.randint(l, n)
            print(2, l, r)


if __name__ == "__main__":
    main()
