#!/usr/bin/env python3
import random


def main():
    random.seed()

    n = random.randint(1, 16)
    m = random.randint(1, 60)
    items = []
    for _ in range(n):
        w = random.randint(1, m)
        v = random.randint(1, 20)
        items.append((w, v))

    print(n, m)
    for w, v in items:
        print(w, v)


if __name__ == "__main__":
    main()
