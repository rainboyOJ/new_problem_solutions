#!/usr/bin/env python3
import random


def main():
    random.seed()

    n = random.randint(1, 20)
    print(n)
    arr = [random.randint(1, 20) for _ in range(n)]
    print(*arr)


if __name__ == "__main__":
    main()
