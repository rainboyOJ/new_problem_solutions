#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 6)
    m1 = random.randint(1, 20)
    m2 = random.randint(1, 4)
    arr = [random.randint(1, 30) for _ in range(n)]

    print(n)
    print(m1, m2)
    print(*arr)


if __name__ == "__main__":
    main()
