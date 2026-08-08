#!/usr/bin/env python3
import random


def main():
    random.seed()
    a = random.randint(1, 30)
    b = random.randint(1, 30)
    c = random.randint(1, 30)
    print(a, b, c)


if __name__ == "__main__":
    main()
