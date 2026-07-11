#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 8)
    k = random.randint(1, min(n, 5))
    print(n, k)
    print(" ".join(str(random.randint(1, 8)) for _ in range(n)))


if __name__ == "__main__":
    main()
