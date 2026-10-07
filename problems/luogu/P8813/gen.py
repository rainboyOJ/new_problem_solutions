#!/usr/bin/env python3
import random


def main():
    random.seed()
    a = random.randint(1, 1000)
    b = random.randint(1, 30)
    print(a, b)


if __name__ == "__main__":
    main()
