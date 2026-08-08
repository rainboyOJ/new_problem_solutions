#!/usr/bin/env python3
import random


def main():
    random.seed()

    n = random.randint(1, 8)
    wood = [random.randint(1, 30) for _ in range(n)]
    total = sum(wood)
    k = random.randint(1, total + 5)

    print(n, k)
    for x in wood:
        print(x)


if __name__ == "__main__":
    main()
