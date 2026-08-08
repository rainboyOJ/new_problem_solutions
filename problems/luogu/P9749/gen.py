#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(2, 8)
    d = random.randint(1, 6)
    print(n, d)
    print(" ".join(str(random.randint(1, 10)) for _ in range(n - 1)))
    print(" ".join(str(random.randint(1, 10)) for _ in range(n)))


if __name__ == "__main__":
    main()
