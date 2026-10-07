#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 8)
    print(n)
    print(*[random.randint(1, 8) for _ in range(n)])
    print(*[random.randint(1, 8) for _ in range(n)])


if __name__ == "__main__":
    main()
