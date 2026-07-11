#!/usr/bin/env python3
import random


def main():
    random.seed()
    t = random.randint(1, 8)
    print(t)
    for _ in range(t):
        n = random.randint(1, 8)
        a = [random.randint(0, 8) for _ in range(n)]
        print(n)
        print(*a)


if __name__ == "__main__":
    main()
