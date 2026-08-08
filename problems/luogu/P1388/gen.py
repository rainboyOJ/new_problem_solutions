#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(2, 8)
    k = random.randint(0, n - 1)
    print(n, k)
    arr = [str(random.randint(0, 9)) for _ in range(n)]
    print(" ".join(arr))


if __name__ == "__main__":
    main()
