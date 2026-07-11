#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(2, 20)
    avg = random.randint(1, 20)

    diff = [0] * n
    for i in range(n - 1):
        diff[i] = random.randint(-8, 8)
    diff[-1] = -sum(diff[:-1])

    h = [avg + x for x in diff]
    while min(h) <= 0:
        avg += 10
        h = [avg + x for x in diff]

    print(n)
    print(*h)
    for v in range(2, n + 1):
        u = random.randint(1, v - 1)
        print(u, v)


if __name__ == "__main__":
    main()
