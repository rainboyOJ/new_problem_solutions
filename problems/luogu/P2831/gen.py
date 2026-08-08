#!/usr/bin/env python3
import random
import sys


def main():
    if len(sys.argv) > 1:
        random.seed(int(sys.argv[1]))
    else:
        random.seed()

    t = 1
    n = random.randint(1, 8)
    print(t)
    print(n, 0)
    for _ in range(n):
        x = random.uniform(0.5, 5.0)
        y = random.uniform(0.1, 8.0)
        print(f"{x:.2f} {y:.2f}")


if __name__ == "__main__":
    main()
