#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 30)
    d = random.randint(1, 20)
    print(n, d)

    pos = random.sample(range(1, 200), n)
    for x in pos:
        h = random.randint(1, 50)
        print(x, h)


if __name__ == "__main__":
    main()
