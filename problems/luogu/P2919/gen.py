#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 8)
    m = random.randint(1, 8)
    print(n, m)
    for _ in range(n):
        print(*[random.randint(0, 9) for _ in range(m)])


if __name__ == "__main__":
    main()
