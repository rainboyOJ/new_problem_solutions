#!/usr/bin/env python3
import random


def main():
    random.seed()

    ship_limit = random.randint(2, 20)
    q = random.randint(1, 60)
    print(q)

    for _ in range(q):
        op = "M" if random.randint(1, 100) <= 55 else "C"
        x = random.randint(1, ship_limit)
        y = random.randint(1, ship_limit)
        print(op, x, y)


if __name__ == "__main__":
    main()
