#!/usr/bin/env python3
import random


def main():
    random.seed()
    t = random.randint(1, 5)
    print(t)
    for _ in range(t):
        n = random.randint(1, 12)
        arr = [random.randint(1, 12) for _ in range(n)]
        print(n)
        print(" ".join(map(str, arr)))


if __name__ == "__main__":
    main()
