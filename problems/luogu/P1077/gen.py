#!/usr/bin/env python3
import random


def main():
    random.seed()

    n = random.randint(1, 6)
    m = random.randint(0, 10)
    a = [random.randint(0, 5) for _ in range(n)]

    print(n, m)
    print(*a)


if __name__ == "__main__":
    main()
