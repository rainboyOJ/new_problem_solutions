#!/usr/bin/env python3
import random


def main():
    random.seed()

    A = random.randint(1, 100)
    I = random.randint(1, 100)
    print(A, I)


if __name__ == "__main__":
    main()
