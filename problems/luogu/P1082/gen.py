#!/usr/bin/env python3

import math
import random


def main():
    while True:
        a = random.randint(2, 200)
        b = random.randint(2, 200)
        if math.gcd(a, b) == 1:
            print(a, b)
            return


if __name__ == "__main__":
    main()
