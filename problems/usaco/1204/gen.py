#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 30)
    a = list(range(1, n + 1))
    b = list(range(1, n + 1))
    random.shuffle(a)
    random.shuffle(b)

    print(n)
    print(*a)
    print(*b)


if __name__ == "__main__":
    main()
