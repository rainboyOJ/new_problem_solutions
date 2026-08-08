#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 80)
    k = random.randint(1, 8)
    print(n, k)
    upper = (1 << k) - 1
    arr = [str(random.randint(0, upper)) for _ in range(n)]
    print(" ".join(arr))


if __name__ == "__main__":
    main()
