#!/usr/bin/env python3
import random


def main():
    n = random.randint(1, 12)
    print(n)
    arr = []
    total_a = 0
    for _ in range(n):
        a = random.randint(1, 20)
        b = random.randint(1, 20)
        arr.append((a, b))
        total_a += a
    for a, b in arr:
        print(a, b)
    H = random.randint(1, total_a + 20)
    print(H)


if __name__ == "__main__":
    main()
