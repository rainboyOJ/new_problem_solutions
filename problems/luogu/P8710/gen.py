#!/usr/bin/env python3
import random


def main():
    random.seed()

    n = random.randint(1, 8)
    m = random.randint(1, 30)
    print(n, m)

    for _ in range(m):
        op = 1 if random.randint(1, 100) <= 45 else 2
        x = random.randint(1, n)
        y = random.randint(1, n)

        if op == 1:
            print(1, x, y)
        else:
            t = random.randint(1, 20)
            print(2, x, t)


if __name__ == "__main__":
    main()
