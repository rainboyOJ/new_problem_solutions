#!/usr/bin/env python3
import random
import sys


def main() -> None:
    if len(sys.argv) > 1:
        random.seed(int(sys.argv[1]))

    t = random.randint(1, 8)
    for _ in range(t):
        a = random.randint(-5, 30)
        b = random.randint(-5, 30)
        c = random.randint(-5, 30)
        print(a, b, c)
    print(-1, -1, -1)


if __name__ == "__main__":
    main()
