#!/usr/bin/env python3
import os
import random


def main():
    seed = os.environ.get("DUPAI_SEED")
    random.seed(None if seed is None else int(seed))
    print(random.randint(1900, 2015))
    print(random.randint(1, 365))


if __name__ == "__main__":
    main()
