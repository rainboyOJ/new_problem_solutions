#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 80)
    a = [random.randint(1, 20) for _ in range(n)]
    b = [random.randint(1, 20) for _ in range(n)]
    print(n)
    print(*a)
    print(*b)


if __name__ == "__main__":
    main()
