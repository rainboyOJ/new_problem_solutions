#!/usr/bin/env python3
import os
import random
from fractions import Fraction


def main():
    random.seed(int(os.environ.get("DUPAI_SEED", "0")))

    while True:
        root_units = sorted(random.sample(range(-400, 401), 3))
        if root_units[1] - root_units[0] >= 4 and root_units[2] - root_units[1] >= 4:
            break

    roots = [Fraction(value, 4) for value in root_units]
    leading = random.choice([-5, -3, -2, -1, 1, 2, 3, 5])

    a = Fraction(leading)
    b = -a * sum(roots)
    c = a * (roots[0] * roots[1] + roots[0] * roots[2] + roots[1] * roots[2])
    d = -a * roots[0] * roots[1] * roots[2]

    print(*(f"{float(value):.10f}" for value in (a, b, c, d)))


if __name__ == "__main__":
    main()
