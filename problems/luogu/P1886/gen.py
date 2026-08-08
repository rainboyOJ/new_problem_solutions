#!/usr/bin/env python3
import random


def main():
    n = random.randint(1, 80)
    k = random.randint(1, n)
    arr = [str(random.randint(-20, 20)) for _ in range(n)]
    print(n, k)
    print(" ".join(arr))


if __name__ == "__main__":
    main()
