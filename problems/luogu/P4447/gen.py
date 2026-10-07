#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 14)
    arr = [random.randint(-5, 8) for _ in range(n)]
    print(n)
    print(" ".join(map(str, arr)))


if __name__ == "__main__":
    main()
