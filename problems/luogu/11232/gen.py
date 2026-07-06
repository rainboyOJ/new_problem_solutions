#!/usr/bin/env python3
import random


def main():
    random.seed()
    t = 1
    n = random.randint(1, 8)
    length = random.randint(5, 30)
    m = random.randint(1, min(8, length + 1))
    limit_v = random.randint(1, 8)

    print(t)
    print(n, m, length, limit_v)
    for _ in range(n):
        d = random.randint(0, length - 1)
        v = random.randint(1, 8)
        a = random.randint(-5, 5)
        print(d, v, a)

    positions = sorted(random.sample(range(0, length + 1), m))
    print(*positions)


if __name__ == "__main__":
    main()
