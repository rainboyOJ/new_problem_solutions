#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 5)
    m = random.randint(1, 4)
    arr = [random.randint(1, 5) for _ in range(m)]
    print(n, m)
    print(*arr)


if __name__ == "__main__":
    main()
