#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 12)
    m = random.randint(1, 20)
    print(n, m)
    for i in range(n):
        d = random.randint(0, 1)
        print(d, f"p{i}")
    for _ in range(m):
        op = random.randint(0, 1)
        step = random.randint(1, 20)
        print(op, step)


if __name__ == "__main__":
    main()
