#!/usr/bin/env python3
import random


def main():
    random.seed()

    a = random.randint(100, 999)
    b = random.randint(100, 999)
    print(a, b)


if __name__ == "__main__":
    main()
