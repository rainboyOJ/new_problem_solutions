#!/usr/bin/env python3
import random


def main():
    n = random.randint(1, 80)
    k = random.randint(1, n)
    b = random.randint(0, n)
    pos = list(range(1, n + 1))
    random.shuffle(pos)
    pos = pos[:b]
    print(n, k, b)
    for x in pos:
        print(x)


if __name__ == "__main__":
    main()
