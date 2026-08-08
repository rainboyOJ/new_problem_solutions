#!/usr/bin/env python3
import random


def main():
    random.seed()
    a = random.randint(1, 20)
    b = random.randint(1, 20)
    c = random.randint(1, 20)
    d = random.randint(1, 20)
    p = random.randint(1, 100)
    m = random.randint(1, 100)
    g = random.randint(1, 100)
    print(a, b, c, d)
    print(p, m, g)


if __name__ == "__main__":
    main()
