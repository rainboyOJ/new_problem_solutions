#!/usr/bin/env python3
import random


def main():
    random.seed()
    L = random.randint(1, 20)
    B = random.randint(1, 100)
    A = random.randint(1, B * L)
    print(A, B, L)


if __name__ == "__main__":
    main()
