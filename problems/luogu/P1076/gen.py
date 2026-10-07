#!/usr/bin/env python3
import random


def main():
    random.seed()

    n = random.randint(1, 8)
    m = random.randint(1, 8)
    print(n, m)

    for _ in range(n):
        stair = [0] * m
        count = random.randint(1, m)
        pos = random.sample(range(m), count)
        for x in pos:
            stair[x] = 1
        for j in range(m):
            value = random.randint(1, 20)
            print(stair[j], value)

    print(random.randint(0, m - 1))


if __name__ == "__main__":
    main()
