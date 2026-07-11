#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(2, 10)
    values = []
    for _ in range(n):
        values.append(str(random.randint(1, 100)))

    print(n)
    print(" ".join(values))


if __name__ == "__main__":
    main()
