#!/usr/bin/env python3
import os
import random


def main():
    seed = os.environ.get("DUPAI_SEED")
    random.seed(None if seed is None else int(seed))

    n = random.randint(1, 15)
    numbers = random.sample(range(0, 40), n)
    print(n)
    print(*numbers)


if __name__ == "__main__":
    main()
