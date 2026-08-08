#!/usr/bin/env python3
import random
import sys


def main():
    if len(sys.argv) > 1:
        random.seed(int(sys.argv[1]))
    else:
        random.seed()

    n = random.randint(1, 30)
    q = random.randint(1, 60)
    arr = [random.randint(0, 20) for _ in range(n)]

    print(n, q)
    print(*arr)
    for _ in range(q):
        op = random.choice(["P", "M", "S"])
        l = random.randint(1, n)
        r = random.randint(l, n)
        if op == "P":
            c = random.randint(-10, 10)
            print(op, l, r, c)
        else:
            print(op, l, r)


if __name__ == "__main__":
    main()
