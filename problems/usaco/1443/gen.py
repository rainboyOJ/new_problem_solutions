#!/usr/bin/env python3
import random
import sys


def main():
    random.seed()
    max_n = 10000
    max_t = 20
    if len(sys.argv) >= 2:
        max_n = int(sys.argv[1])
    if len(sys.argv) >= 3:
        max_t = int(sys.argv[2])

    t = random.randint(1, max_t)
    used = set()
    values = []
    while len(values) < t:
        if random.randint(0, 3) == 0:
            k = random.choice([44, 45, 49, 50, 444, 445, 499, 500, 4444, 4445, 4999, 5000])
            n = min(max_n, k)
            if n < 1:
                n = 1
        else:
            n = random.randint(1, max_n)
        if n not in used:
            used.add(n)
            values.append(n)

    print(t)
    for n in values:
        print(n)


if __name__ == "__main__":
    main()
