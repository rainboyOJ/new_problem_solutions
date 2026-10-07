#!/usr/bin/env python3
import os
import random


def main():
    random.seed(int(os.environ.get("DUPAI_SEED", "0")))
    n = random.randint(1, 12)
    charger_power = random.randint(1, 30)

    print(n, charger_power)
    for _ in range(n):
        use = random.randint(1, 30)
        stored = random.randint(1, 30)
        print(use, stored)


if __name__ == "__main__":
    main()
