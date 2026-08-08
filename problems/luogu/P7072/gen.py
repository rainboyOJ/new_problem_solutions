#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 40)
    w = random.randint(1, 99)
    print(n, w)
    print(*[random.randint(0, 600) for _ in range(n)])


if __name__ == "__main__":
    main()
