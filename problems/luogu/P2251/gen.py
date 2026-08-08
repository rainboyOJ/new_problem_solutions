#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 50)
    m = random.randint(1, n)
    arr = [random.randint(1, 100) for _ in range(n)]
    print(n, m)
    print(*arr)


if __name__ == "__main__":
    main()
