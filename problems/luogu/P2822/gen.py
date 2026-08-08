#!/usr/bin/env python3
import os
import random


def main():
    random.seed(int(os.environ.get("DUPAI_SEED", "0")))

    test_count = random.randint(1, 30)
    divisor = random.randint(1, 25)
    print(test_count, divisor)
    for _ in range(test_count):
        n = random.randint(0, 80)
        m = random.randint(0, 80)
        print(n, m)


if __name__ == "__main__":
    main()
