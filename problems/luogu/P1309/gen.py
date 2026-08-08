#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 20)
    r = random.randint(1, 8)
    q = random.randint(1, 2 * n)
    print(n, r, q)
    scores = [random.randint(0, 20) for _ in range(2 * n)]
    print(*scores)
    powers = list(range(1, 2 * n + 1))
    random.shuffle(powers)
    print(*powers)


if __name__ == "__main__":
    main()
