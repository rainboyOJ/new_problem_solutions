#!/usr/bin/env python3
import random


def main():
    random.seed()
    for _ in range(7):
        print(random.randint(0, 10), random.randint(0, 10))


if __name__ == "__main__":
    main()
