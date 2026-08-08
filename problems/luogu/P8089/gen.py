#!/usr/bin/env python3
import random
import sys


def main():
    if len(sys.argv) > 1:
        random.seed(int(sys.argv[1]))
    else:
        random.seed()

    t = 1
    dep = random.randint(1, 10)
    mx = 1 << (dep - 1)
    x = random.randint(1, mx)
    print(t)
    print(dep)
    print(bin(x)[2:])


if __name__ == "__main__":
    main()
