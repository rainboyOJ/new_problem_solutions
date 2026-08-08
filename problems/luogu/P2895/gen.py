#!/usr/bin/env python3
import random


def main():
    random.seed()
    m = random.randint(1, 12)
    print(m)
    for _ in range(m):
        x = random.randint(0, 12)
        y = random.randint(0, 12)
        t = random.randint(0, 20)
        print(x, y, t)


if __name__ == "__main__":
    main()
