#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(2, 50)
    l = random.randint(n, 200)
    r = random.randint(l, 200)
    print(n, l, r)


if __name__ == "__main__":
    main()
