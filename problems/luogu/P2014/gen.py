#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 18)
    m = random.randint(1, n)

    print(n, m)
    for i in range(1, n + 1):
        if i == 1:
            parent = 0
        else:
            parent = random.randint(0, i - 1)
        score = random.randint(0, 30)
        print(parent, score)


if __name__ == "__main__":
    main()
