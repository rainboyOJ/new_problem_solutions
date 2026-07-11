#!/usr/bin/env python3
import random


def main():
    random.seed()
    t = random.randint(1, 4)
    print(t)
    for _ in range(t):
        n = random.randint(1, 50)
        m = random.randint(1, 10)
        k = random.randint(1, 4)
        print(n, m, k)
        for _ in range(m):
            values = random.sample(range(1, 21), k)
            print(*values)


if __name__ == "__main__":
    main()
