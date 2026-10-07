#!/usr/bin/env python3
import random


def main():
    random.seed()

    n = random.randrange(2, 20, 2)
    print(n)
    for _ in range(n):
        print(random.randint(0, 20))


if __name__ == "__main__":
    main()
