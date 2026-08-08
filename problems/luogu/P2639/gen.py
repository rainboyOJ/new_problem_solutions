#!/usr/bin/env python3
import random


def main():
    random.seed()

    n = random.randint(1, 16)
    h = random.randint(5, 60)
    weights = [random.randint(1, h) for _ in range(n)]

    print(h, n)
    for w in weights:
        print(w)


if __name__ == "__main__":
    main()
