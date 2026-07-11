#!/usr/bin/env python3
import random
import sys


def main():
    random.seed()
    max_n = 10
    max_q = 30
    if len(sys.argv) >= 2:
        max_n = int(sys.argv[1])
    if len(sys.argv) >= 3:
        max_q = int(sys.argv[2])

    max_n = max(2, max_n)
    if max_n % 2 == 1:
        max_n -= 1
    k = random.randint(1, max_n // 2)
    n = k * 2
    q = random.randint(0, max_q)

    print(n, q)
    for _ in range(n):
        row = []
        for _ in range(n):
            row.append(random.choice([".", "#"]))
        print("".join(row))

    for _ in range(q):
        r = random.randint(1, n)
        c = random.randint(1, n)
        print(r, c)


if __name__ == "__main__":
    main()
