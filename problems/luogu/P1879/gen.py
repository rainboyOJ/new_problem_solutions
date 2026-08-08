#!/usr/bin/env python3
import random
import sys


def main():
    if len(sys.argv) > 1:
        random.seed(int(sys.argv[1]))
    else:
        random.seed()

    n = random.randint(1, 6)
    m = random.randint(1, 6)
    print(n, m)
    for _ in range(n):
        row = [str(random.randint(0, 1)) for _ in range(m)]
        print(" ".join(row))


if __name__ == "__main__":
    main()
