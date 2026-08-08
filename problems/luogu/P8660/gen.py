#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 12)
    print(n)

    remain = 10000
    lengths = []
    for i in range(1, n + 1):
        if i == n:
            lengths.append(remain)
        else:
            x = random.randint(1, max(1, remain - (n - i)))
            lengths.append(x)
            remain -= x

    for length in lengths:
        left = random.randint(0, 10000)
        right = left + length
        print(left, right)


if __name__ == "__main__":
    main()
