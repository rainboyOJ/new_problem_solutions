#!/usr/bin/env python3
import random
import sys


def main() -> None:
    if len(sys.argv) > 1:
        random.seed(int(sys.argv[1]))

    t = random.randint(1, 8)
    p = random.randint(1, 20)
    print(t, p)
    for _ in range(t):
        x = random.randint(1, 30)
        y = random.randint(1, 30)
        print(x, y)


if __name__ == "__main__":
    main()
