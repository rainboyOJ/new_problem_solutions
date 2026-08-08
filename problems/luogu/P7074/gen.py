#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 4)
    m = random.randint(1, 4)
    print(n, m)
    for _ in range(n):
        row = [str(random.randint(-5, 5)) for _ in range(m)]
        print(" ".join(row))


if __name__ == "__main__":
    main()
