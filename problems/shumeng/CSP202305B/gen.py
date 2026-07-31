#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 8)
    d = random.randint(1, 5)
    print(n, d)
    for _ in range(3 * n):
        print(" ".join(str(random.randint(-5, 5)) for _ in range(d)))
    print(" ".join(str(random.randint(-5, 5)) for _ in range(n)))


if __name__ == "__main__":
    main()
