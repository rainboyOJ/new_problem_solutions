#!/usr/bin/env python3
import random
import sys


def main():
    if len(sys.argv) > 1:
        random.seed(int(sys.argv[1]))
    else:
        random.seed()

    years = sorted(random.sample(range(1, 25), random.randint(1, 10)))
    print(len(years))
    for y in years:
        print(y, random.randint(1, 20))

    q = random.randint(1, 20)
    print(q)
    for _ in range(q):
        y = random.randint(1, 23)
        x = random.randint(y + 1, 24)
        print(y, x)


if __name__ == "__main__":
    main()
