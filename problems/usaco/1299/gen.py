#!/usr/bin/env python3
import random


def main():
    random.seed()
    t = random.randint(1, 30)
    n = random.randint(1, min(8, t))
    days = sorted(random.sample(range(1, t + 1), n))

    print(n, t)
    for d in days:
        b = random.randint(1, 20)
        print(d, b)


if __name__ == "__main__":
    main()
