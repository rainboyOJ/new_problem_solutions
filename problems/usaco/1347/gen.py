#!/usr/bin/env python3
import random
import sys


def main():
    random.seed()
    max_n = 20
    max_m = 20
    max_h = 50
    if len(sys.argv) >= 2:
        max_n = int(sys.argv[1])
    if len(sys.argv) >= 3:
        max_m = int(sys.argv[2])
    if len(sys.argv) >= 4:
        max_h = int(sys.argv[3])

    n = random.randint(1, max_n)
    m = random.randint(1, max_m)
    print(n, m)
    print(" ".join(str(random.randint(1, max_h)) for _ in range(n)))
    print(" ".join(str(random.randint(1, max_h)) for _ in range(m)))


if __name__ == "__main__":
    main()
