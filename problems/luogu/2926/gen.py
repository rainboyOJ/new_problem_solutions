#!/usr/bin/env python3
import os
import random


def main():
    random.seed(int(os.environ.get("DUPAI_SEED", "0")))

    n = random.randint(1, 60)
    print(n)
    for _ in range(n):
        print(random.randint(1, 80))


if __name__ == "__main__":
    main()
