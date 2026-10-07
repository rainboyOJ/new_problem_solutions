#!/usr/bin/env python3
import random


def main():
    random.seed()
    a = random.randint(0, 10000)
    b = random.randint(0, 9)
    print(a, b)


if __name__ == "__main__":
    main()
