#!/usr/bin/env python3
import os
import random
from fractions import Fraction


def main():
    random.seed(int(os.environ.get("DUPAI_SEED", "0")))

    while True:
        root_units = sorted(random.sample(range(-2000, 2001), 3))
        if root_units[1] - root_units[0] >= 20 and root_units[2] - root_units[1] >= 20:
            break

    # 二十分之一刻度会生成 0.05、0.35 等不能被二进制浮点精确表示的小数。
    roots = [Fraction(value, 20) for value in root_units]
    leading = random.choice([-5, -3, -2, -1, 1, 2, 3, 5])

    a = Fraction(leading)
    b = -a * sum(roots)
    c = a * (roots[0] * roots[1] + roots[0] * roots[2] + roots[1] * roots[2])
    d = -a * roots[0] * roots[1] * roots[2]

    print(*(f"{float(value):.10f}" for value in (a, b, c, d)))


if __name__ == "__main__":
    main()
