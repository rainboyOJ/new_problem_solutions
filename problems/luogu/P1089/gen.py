#!/usr/bin/env python3
import random


def main():
    random.seed()
    for _ in range(12):
        print(random.randint(0, 500))


if __name__ == "__main__":
    main()
