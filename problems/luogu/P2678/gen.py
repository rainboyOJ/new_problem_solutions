#!/usr/bin/env python3
import random


def main():
    random.seed()

    n = random.randint(0, 8)
    l = random.randint(max(2, n + 1), 30)
    m = random.randint(0, n)
    stones = random.sample(range(1, l), n)
    random.shuffle(stones)

    print(l, n, m)
    for x in stones:
        print(x)


if __name__ == "__main__":
    main()
