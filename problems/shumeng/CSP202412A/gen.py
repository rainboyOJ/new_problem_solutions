#!/usr/bin/env python3
import os
import random


def main():
    seed = os.environ.get("DUPAI_SEED")
    random.seed(None if seed is None else int(seed))
    n = random.randint(1, 100)
    k = random.randint(1, 30)
    print(n, k)
    for _ in range(k):
        length = random.randint(1, 100)
        commands = "".join(random.choice("fblr") for _ in range(length))
        print(random.randint(1, n), random.randint(1, n), commands)


if __name__ == "__main__":
    main()
