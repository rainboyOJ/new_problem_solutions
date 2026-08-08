#!/usr/bin/env python3
import random
import sys


def main():
    if len(sys.argv) > 1:
        random.seed(int(sys.argv[1]))
    else:
        random.seed()

    n = random.randint(1, 10)
    print(n)
    for _ in range(n):
        print(f"{random.uniform(-10,10):.3f} {random.uniform(-10,10):.3f}")


if __name__ == "__main__":
    main()
