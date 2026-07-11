#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 25)
    values = []
    for _ in range(n):
        values.append(str(random.randint(1, 30)))

    print(n)
    print(" ".join(values))


if __name__ == "__main__":
    main()
