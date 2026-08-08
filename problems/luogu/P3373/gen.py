#!/usr/bin/env python3
import random
import sys


def main():
    if len(sys.argv) > 1:
        random.seed(int(sys.argv[1]))
    else:
        random.seed()

    n = random.randint(1, 20)
    q = random.randint(1, 50)
    mod = random.randint(2, 100)
    arr = [random.randint(0, 50) for _ in range(n)]

    print(n, q, mod)
    print(*arr)
    for _ in range(q):
        op = random.randint(1, 3)
        l = random.randint(1, n)
        r = random.randint(l, n)
        if op == 3:
            print(op, l, r)
        else:
            x = random.randint(0, 20)
            print(op, l, r, x)


if __name__ == "__main__":
    main()
