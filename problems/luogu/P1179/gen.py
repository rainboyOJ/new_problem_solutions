#!/usr/bin/env python3
import random


def main():
    random.seed()
    l = random.randint(1, 100000)
    r = random.randint(l, 100000)
    print(l, r)


if __name__ == "__main__":
    main()
