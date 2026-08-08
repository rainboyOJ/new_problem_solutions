#!/usr/bin/env python3
import random


def main():
    n = random.randint(1, 7)
    print(n)
    for _ in range(n):
        arr = list(range(1, n + 1))
        random.shuffle(arr)
        print(" ".join(map(str, arr)))
    print(random.randint(1, 2))


if __name__ == "__main__":
    main()
