#!/usr/bin/env python3
import random
import sys


def main() -> None:
    if len(sys.argv) > 1:
        random.seed(int(sys.argv[1]))

    t = random.randint(1, 12)
    w = random.randint(1, 5)
    print(t, w)
    for _ in range(t):
        print(random.randint(1, 2))


if __name__ == "__main__":
    main()
