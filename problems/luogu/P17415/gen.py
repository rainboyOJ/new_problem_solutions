#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 12)
    x = random.randint(1, 30)
    q = random.randint(1, 15)
    print(n, x, q)
    for _ in range(n):
        if random.random() < 0.35:
            a = random.randint(1, 8)
            b = random.randint(1, 20)
            c = random.randint(1, 20)
            print(1, a, b, c)
        else:
            a = random.randint(1, 8)
            b = random.randint(1, 20)
            print(0, a, b)
    for _ in range(q):
        print(random.randint(1, 50))


if __name__ == "__main__":
    main()
