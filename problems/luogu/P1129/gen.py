#!/usr/bin/env python3
import random


def main():
    random.seed()
    t = random.randint(1, 5)
    print(t)
    for _ in range(t):
        n = random.randint(1, 7)
        print(n)
        for _ in range(n):
            row = [str(random.randint(0, 1)) for _ in range(n)]
            print(" ".join(row))


if __name__ == "__main__":
    main()
