#!/usr/bin/env python3
import random


def main():
    n = random.randint(1, 40)
    print(n)
    for _ in range(n):
        x = random.randint(1, 50)
        y = random.randint(1, 50)
        print(x, y)


if __name__ == "__main__":
    main()
