#!/usr/bin/env python3
import random


def main():
    random.seed()
    t = 1
    n = random.randint(2, 12)
    print(t)
    print(n)
    print(*[random.randint(1, 8) for _ in range(n)])


if __name__ == "__main__":
    main()
