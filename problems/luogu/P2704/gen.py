#!/usr/bin/env python3
import random
import sys


def main():
    if len(sys.argv) > 1:
        random.seed(int(sys.argv[1]))
    else:
        random.seed()

    n = random.randint(1, 5)
    m = random.randint(1, 5)
    print(n, m)
    for _ in range(n):
        s = "".join(random.choice("PH") for _ in range(m))
        print(s)


if __name__ == "__main__":
    main()
