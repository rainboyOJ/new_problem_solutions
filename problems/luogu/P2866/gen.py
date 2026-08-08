#!/usr/bin/env python3
import random


def main():
    n = random.randint(1, 80)
    print(n)
    for _ in range(n):
        print(random.randint(1, 100))


if __name__ == "__main__":
    main()
