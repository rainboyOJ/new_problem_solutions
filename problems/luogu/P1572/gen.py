#!/usr/bin/env python3
import random


def frac():
    a = random.randint(1, 20)
    b = random.randint(1, 20)
    return f"{a}/{b}"


def main():
    random.seed()
    n = random.randint(1, 6)
    expr = frac()
    for _ in range(n - 1):
        expr += random.choice(["+", "-"])
        expr += frac()
    print(expr)


if __name__ == "__main__":
    main()
