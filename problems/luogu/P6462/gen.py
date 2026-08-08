#!/usr/bin/env python3
import random


def main():
    random.seed()
    t = random.randint(1, 8)
    print(t)
    for _ in range(t):
        h = random.randint(1, 80)
        x = random.randint(0, 20)
        y = random.randint(0, 20)
        print(h, x, y)


if __name__ == "__main__":
    main()
