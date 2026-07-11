#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 12)
    l = random.randint(0, n)
    values = []
    for _ in range(n):
        values.append(str(random.randint(0, 12)))

    print(n, l)
    print(" ".join(values))


if __name__ == "__main__":
    main()
