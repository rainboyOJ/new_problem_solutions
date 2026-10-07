#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 6)
    k = random.randint(1, 6)
    print(n, k)
    print(*[random.randint(1, 10) for _ in range(n)])
    print(*[random.randint(1, 10) for _ in range(k)])


if __name__ == "__main__":
    main()
