#!/usr/bin/env python3
import random


def main():
    random.seed()

    m = random.randint(1, 8)
    t = random.randint(1, 30)
    items = []
    for _ in range(m):
        cost = random.randint(1, t)
        value = random.randint(1, 20)
        items.append((cost, value))

    print(t, m)
    for cost, value in items:
        print(cost, value)


if __name__ == "__main__":
    main()
