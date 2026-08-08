#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 6)
    l = random.randint(0, 6)
    r = random.randint(l, 6)
    arr = [random.randint(0, 8) for _ in range(n)]
    print(n)
    print(*arr)
    print(l, r)


if __name__ == "__main__":
    main()
