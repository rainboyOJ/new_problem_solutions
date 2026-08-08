#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 10)
    m = random.randint(1, 6)
    print(n, m)
    for _ in range(m):
        row = [str(random.randint(1, 20)) for _ in range(n)]
        print(" ".join(row))


if __name__ == "__main__":
    main()
