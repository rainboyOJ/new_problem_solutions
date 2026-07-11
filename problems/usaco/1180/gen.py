#!/usr/bin/env python3
import random


def main():
    random.seed()
    t = random.randint(1, 10)
    print(t)
    for _ in range(t):
        nums = [random.randint(1, 10) for _ in range(8)]
        print(*nums)


if __name__ == "__main__":
    main()
