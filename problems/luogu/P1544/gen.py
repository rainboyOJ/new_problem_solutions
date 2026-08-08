#!/usr/bin/env python3
import random
import sys


def main() -> None:
    if len(sys.argv) > 1:
        random.seed(int(sys.argv[1]))

    n = random.randint(1, 8)
    k = random.randint(0, 8)
    print(n, k)
    for i in range(1, n + 1):
        row = [str(random.randint(-10, 10)) for _ in range(i)]
        print(" ".join(row))


if __name__ == "__main__":
    main()
