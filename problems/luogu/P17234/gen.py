#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 80)
    print(n)
    print(*[random.randint(0, min(20, n + 2)) for _ in range(n)])


if __name__ == "__main__":
    main()
