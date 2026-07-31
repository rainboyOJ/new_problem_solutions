#!/usr/bin/env python3
import os
import random


def main():
    seed = os.environ.get("DUPAI_SEED")
    random.seed(None if seed is None else int(seed))

    n = random.randint(2, 8)
    first_price = [random.randint(1, 30) for _ in range(n)]
    second_price = [0] * n
    second_price[0] = (first_price[0] + first_price[1]) // 2
    for i in range(1, n - 1):
        second_price[i] = (first_price[i - 1] + first_price[i] + first_price[i + 1]) // 3
    second_price[-1] = (first_price[-2] + first_price[-1]) // 2

    print(n)
    print(*second_price)


if __name__ == "__main__":
    main()
