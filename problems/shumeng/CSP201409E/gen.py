#!/usr/bin/env python3
import os
import random


def main():
    seed = os.environ.get("DUPAI_SEED")
    random.seed(None if seed is None else int(seed))

    n = random.randint(1, 6)
    m = random.randint(1, 4)
    print(n, m)


if __name__ == "__main__":
    main()
