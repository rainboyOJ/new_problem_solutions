#!/usr/bin/env python3
import random
import os


def main():
    seed = os.environ.get("DUPAI_SEED")
    random.seed(None if seed is None else int(seed))
    n = random.randint(0, 18)
    length = random.randint(1, 30)
    print(n)
    print("".join(random.choice("1246") for _ in range(length)))


if __name__ == "__main__":
    main()
