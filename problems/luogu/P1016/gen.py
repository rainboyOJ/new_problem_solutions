#!/usr/bin/env python3
import random


def main():
    random.seed()

    s = random.randint(10, 40)
    c = random.randint(2, 8)
    l = random.randint(1, 5)
    p0 = random.randint(1, 10)
    n = random.randint(0, 5)

    pos = sorted(random.sample(range(1, s), n))
    print(f"{s:.1f} {c:.1f} {l:.1f} {p0:.1f} {n}")
    for d in pos:
        p = random.randint(1, 10)
        print(f"{float(d):.1f} {float(p):.1f}")


if __name__ == "__main__":
    main()
