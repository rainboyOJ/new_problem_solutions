#!/usr/bin/env python3
import random


def main():
    random.seed()
    t = random.randint(1, 3)
    print(t)
    for _ in range(t):
        n = random.randint(1, 4)
        m = random.randint(1, 4)
        print(n, m)
        for _ in range(n):
            row = [random.randint(0, 20) for _ in range(m)]
            print(*row)


if __name__ == "__main__":
    main()
