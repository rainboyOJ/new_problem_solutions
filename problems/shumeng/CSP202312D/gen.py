#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 700)
    m = random.randint(1, 100)
    print(n, m)

    def write_operation(kind=None):
        if kind is None:
            kind = random.randint(1, 3)
        if kind == 3:
            print(3)
        else:
            values = [random.randint(0, 30) for _ in range(4)]
            print(kind, *values)

    for _ in range(n): write_operation()
    for _ in range(m):
        if random.randint(0, 2) == 0:
            print(1, random.randint(1, n), end=" ")
            write_operation()
        else:
            left = random.randint(1, n)
            right = random.randint(left, n)
            print(2, left, right)


if __name__ == "__main__":
    main()
