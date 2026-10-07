#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 30)
    m = random.randint(1, n)
    print(n, m)
    print(" ".join(str(random.randint(1, 50)) for _ in range(n)))


if __name__ == "__main__":
    main()
