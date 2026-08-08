#!/usr/bin/env python3
import random
import sys


def main():
    if len(sys.argv) > 1:
        random.seed(int(sys.argv[1]))
    else:
        random.seed()

    n = random.randint(1, 12)
    print(n)
    for i in range(2, n + 1):
        p = random.randint(1, i - 1)
        print(i, p)

    arr = [str(random.randint(-10, 10)) for _ in range(n)]
    print(" ".join(arr))

    q = random.randint(1, 30)
    print(q)
    for _ in range(q):
        op = random.choice(["CHANGE", "QMAX", "QSUM"])
        u = random.randint(1, n)
        v = random.randint(1, n)
        if op == "CHANGE":
            print(op, u, random.randint(-10, 10))
        else:
            print(op, u, v)


if __name__ == "__main__":
    main()
