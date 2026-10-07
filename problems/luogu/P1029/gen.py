#!/usr/bin/env python3
import random


def main():
    random.seed()
    x0 = random.randint(2, 200)
    if random.randint(0, 3) == 0:
        y0 = random.randint(2, 5000)
    else:
        mul = random.randint(1, 200)
        y0 = x0 * mul
        if y0 > 100000:
            y0 = x0
    print(x0, y0)


if __name__ == "__main__":
    main()
