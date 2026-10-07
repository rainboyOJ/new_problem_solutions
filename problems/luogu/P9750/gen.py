#!/usr/bin/env python3
import random


def main():
    random.seed()
    t = random.randint(1, 20)
    m = random.randint(1, 20)
    print(t, m)
    for _ in range(t):
        a = 0
        while a == 0:
            a = random.randint(-m, m)
        b = random.randint(-m, m)
        c = random.randint(-m, m)
        print(a, b, c)


if __name__ == "__main__":
    main()
