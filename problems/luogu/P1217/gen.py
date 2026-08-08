#!/usr/bin/env python3
import random


def main():
    random.seed()
    a = random.randint(5, 20000)
    b = random.randint(a + 1, min(50000, a + 5000))
    print(a, b)


if __name__ == "__main__":
    main()
