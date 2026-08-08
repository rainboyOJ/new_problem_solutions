#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(3, 7)
    m = random.randint(5, 8)
    k = random.randint(0, n - 1)

    print(n, m, k)
    for _ in range(n):
        print(random.randint(1, m - 1), random.randint(1, m - 1))

    positions = random.sample(range(1, n), k)
    for position in positions:
        low = random.randint(0, m - 2)
        high = random.randint(low + 2, m)
        print(position, low, high)


if __name__ == "__main__":
    main()
