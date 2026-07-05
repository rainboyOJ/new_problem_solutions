#!/usr/bin/env python3
import random


def main():
    n = random.randint(1, 10)
    m = random.randint(1, 10)
    total = n * m
    values = list(range(1, total + 1))
    random.shuffle(values)
    print(n, m)
    print(" ".join(map(str, values)))


if __name__ == "__main__":
    main()
