#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 30)
    a = [random.randint(-20, 20) for _ in range(n)]
    print(n)
    print(*a)


if __name__ == "__main__":
    main()
