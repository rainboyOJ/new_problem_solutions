#!/usr/bin/env python3
import random


def main():
    random.seed()

    n = random.randint(0, 10)
    coef = [random.randint(-5, 5) for _ in range(n + 1)]
    while coef[0] == 0:
        coef[0] = random.randint(-5, 5)

    print(n)
    print(" ".join(map(str, coef)))


if __name__ == "__main__":
    main()
