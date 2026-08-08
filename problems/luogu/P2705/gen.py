#!/usr/bin/env python3
import random


def main():
    random.seed()
    R = random.randint(1, 20)
    B = random.randint(1, 20)
    C = random.randint(-20, 20)
    D = random.randint(-20, 20)
    E = random.randint(-20, 20)
    print(R, B, C, D, E)


if __name__ == "__main__":
    main()
