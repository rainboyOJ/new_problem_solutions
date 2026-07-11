#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 8)
    print(n)
    values = []
    for _ in range(n):
        values.append(str(random.randint(1, 30)))
    print(" ".join(values))


if __name__ == "__main__":
    main()
