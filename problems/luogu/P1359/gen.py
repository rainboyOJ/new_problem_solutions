#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(2, 10)
    print(n)
    for i in range(1, n):
        row = [str(random.randint(1, 20)) for _ in range(n - i)]
        print(" ".join(row))


if __name__ == "__main__":
    main()
