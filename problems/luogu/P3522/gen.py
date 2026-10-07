#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 60)
    print(n)
    for _ in range(n):
        x = random.randint(-20, 20)
        y = random.randint(x, 20)
        print(x, y)


if __name__ == "__main__":
    main()
