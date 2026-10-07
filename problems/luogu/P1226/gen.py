#!/usr/bin/env python3
import random


def main():
    random.seed()
    a = random.randint(0, 1000)
    b = random.randint(0, 80)
    if a + b == 0:
        a = 1
    p = random.randint(2, 1000)
    print(a, b, p)


if __name__ == "__main__":
    main()
