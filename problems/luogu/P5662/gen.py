#!/usr/bin/env python3
import random


def main() -> None:
    random.seed()

    T = random.randint(1, 5)
    N = random.randint(1, 5)
    M = random.randint(0, 40)
    print(T, N, M)

    prices = [[random.randint(1, 20) for _ in range(N)]]
    for _ in range(1, T):
        prev = prices[-1]
        row = [max(1, prev[item] + random.randint(-5, 8)) for item in range(N)]
        prices.append(row)

    for row in prices:
        print(*row)


if __name__ == "__main__":
    main()
