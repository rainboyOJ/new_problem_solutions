#!/usr/bin/env python3
import random
import sys


def main():
    if len(sys.argv) > 1:
        random.seed(int(sys.argv[1]))
    else:
        random.seed()

    n = random.randint(1, 40)
    home_x = random.randint(0, 50)
    arr = []
    for _ in range(n):
        x = random.randint(0, 50)
        r = random.randint(1, 20)
        v = random.randint(1, 100)
        arr.append((x, r, v))

    print(n, home_x)
    for x, r, v in arr:
        print(x, r, v)


if __name__ == "__main__":
    main()
