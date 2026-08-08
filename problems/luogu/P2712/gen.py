#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 12)
    positions = random.sample(range(0, 31), n)
    print(n)
    for i in range(n):
        m = random.randint(0, n)
        watch = sorted(random.sample(range(0, 31), m))
        print(positions[i], m, *watch)


if __name__ == "__main__":
    main()
