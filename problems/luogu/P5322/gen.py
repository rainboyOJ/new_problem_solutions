#!/usr/bin/env python3
import random


def main() -> None:
    random.seed()

    s = random.randint(1, 5)
    n = random.randint(1, 5)
    m = random.randint(1, 20)
    print(s, n, m)
    for _ in range(s):
        row = []
        remain = m
        for j in range(n):
            if j == n - 1:
                x = random.randint(0, remain)
            else:
                x = random.randint(0, remain)
            row.append(x)
            remain -= x
        print(*row)


if __name__ == "__main__":
    main()
