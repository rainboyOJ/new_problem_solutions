#!/usr/bin/env python3
import random
import sys


def main():
    if len(sys.argv) > 1:
        random.seed(int(sys.argv[1]))
    else:
        random.seed()

    n = random.randint(1, 30)
    w_choices = [0, 1, 3, 5, 7, 9]
    w = random.choice(w_choices)

    print(n, w)
    for _ in range(n):
        x = random.randint(1, 20)
        b = random.randint(1, 20)
        print(x, b)


if __name__ == "__main__":
    main()
