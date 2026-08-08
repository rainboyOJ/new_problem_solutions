#!/usr/bin/env python3
import os
import random


def main():
    random.seed(int(os.environ.get("DUPAI_SEED", "0")))

    n = random.randint(1, 6)
    mode = random.randint(0, 2)

    print(n)
    for _ in range(n):
        if mode == 0:
            row = [random.randint(-10, -1) for _ in range(n)]
        elif mode == 1:
            row = [random.randint(0, 10) for _ in range(n)]
        else:
            row = [random.randint(-10, 10) for _ in range(n)]
        print(*row)


if __name__ == "__main__":
    main()
