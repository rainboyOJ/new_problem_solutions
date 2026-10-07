#!/usr/bin/env python3
import random
import sys


def main() -> None:
    if len(sys.argv) > 1:
        random.seed(int(sys.argv[1]))

    t = random.randint(1, 5)
    print(t)
    for _ in range(t):
        n = random.randint(1, 30)
        print(n)
        arr = [str(random.randint(-10, 10)) for _ in range(n)]
        print(" ".join(arr))


if __name__ == "__main__":
    main()
