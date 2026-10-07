#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 12)
    print(n)
    for i in range(1, n + 1):
        row = [str(random.randint(0, 20)) for _ in range(i)]
        print(" ".join(row))


if __name__ == "__main__":
    main()
