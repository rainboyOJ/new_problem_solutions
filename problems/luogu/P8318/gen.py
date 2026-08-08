#!/usr/bin/env python3
import random


def apply(arr, op, x, y):
    if op == 1:
        arr[x] = arr[x] + arr[y]
    else:
        arr[x] = arr[x] * arr[y]


def main():
    random.seed()
    n = random.randint(1, 4)
    m = random.randint(1, 5)
    a = [0] + [random.randint(1, 4) for _ in range(n)]
    cur = a[:]
    ops = []

    for _ in range(m):
        op = random.randint(1, 2)
        x = random.randint(1, n)
        y = random.randint(1, n)
        ops.append((op, x, y))
        apply(cur, op, x, y)

    print(n, m)
    print(*cur[1:])
    for op, x, y in ops:
        print(op, x, y)


if __name__ == "__main__":
    main()
