#!/usr/bin/env python3
import random


def main():
    random.seed()

    n = random.randint(2, 12)
    m = random.randint(2, n)
    xs = random.sample(range(0, 200), n)
    random.shuffle(xs)

    print(n, m)
    for x in xs:
        print(x)


if __name__ == "__main__":
    main()
