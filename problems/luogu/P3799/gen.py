#!/usr/bin/env python3
import os
import random


def main():
    random.seed(int(os.environ.get("DUPAI_SEED", "0")))
    n = random.randint(1, 12)
    max_length = random.randint(1, 10)
    sticks = [random.randint(1, max_length) for _ in range(n)]

    print(n)
    print(*sticks, sep="\n")


if __name__ == "__main__":
    main()
