#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(2, 7)
    x = random.randint(0, 6)
    print(n, x)
    print(" ".join(str(random.randint(0, 4)) for _ in range(n)))


if __name__ == "__main__":
    main()
