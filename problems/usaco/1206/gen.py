#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 8)
    print(n)
    for _ in range(n):
        p = list(range(1, n + 1))
        random.shuffle(p)
        print(*p)


if __name__ == "__main__":
    main()
