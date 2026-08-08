#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 8)
    m = random.randint(1, 8)
    heights = [random.randint(1, 20) for _ in range(n)]
    candies = [random.randint(1, 20) for _ in range(m)]

    print(n, m)
    print(*heights)
    print(*candies)


if __name__ == "__main__":
    main()
