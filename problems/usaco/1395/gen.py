#!/usr/bin/env python3
import random
import sys


def main():
    random.seed()
    max_s = 500
    max_t = 10
    if len(sys.argv) >= 2:
        max_s = int(sys.argv[1])
    if len(sys.argv) >= 3:
        max_t = int(sys.argv[2])

    t = random.randint(1, max_t)
    print(t)
    for _ in range(t):
        if random.randint(0, 4) == 0:
            x = random.randint(1, max_s // 10 + 1) * 10
            x = min(x, max_s)
        else:
            x = random.randint(1, max_s)
        print(x)


if __name__ == "__main__":
    main()
