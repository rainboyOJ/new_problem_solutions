#!/usr/bin/env python3
import random


def main():
    random.seed()

    c = random.randint(1, 60)
    h = random.randint(1, 16)
    arr = [random.randint(1, c) for _ in range(h)]

    print(c, h)
    for x in arr:
        print(x)


if __name__ == "__main__":
    main()
