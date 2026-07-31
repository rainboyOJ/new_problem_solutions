#!/usr/bin/env python3
import os
import random


def main():
    seed = os.environ.get("DUPAI_SEED")
    random.seed(None if seed is None else int(seed))

    alphabet = "aAbBcC"
    pattern = "".join(random.choice(alphabet) for _ in range(random.randint(1, 5)))
    sensitive = random.randint(0, 1)
    n = random.randint(1, 12)
    print(pattern)
    print(sensitive)
    print(n)
    for _ in range(n):
        print("".join(random.choice(alphabet) for _ in range(random.randint(1, 12))))


if __name__ == "__main__":
    main()
