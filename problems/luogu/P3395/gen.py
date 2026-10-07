#!/usr/bin/env python3
import random


def main():
    random.seed()
    t = random.randint(1, 4)
    print(t)
    print()

    for case_id in range(t):
        n = random.randint(1, 6)
        print(n)
        for _ in range(2 * n - 2):
            x = random.randint(1, n)
            y = random.randint(1, n)
            print(x, y)
        if case_id != t - 1:
            print()


if __name__ == "__main__":
    main()
