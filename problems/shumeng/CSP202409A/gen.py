#!/usr/bin/env python3
import os
import random


def main():
    seed = os.environ.get("DUPAI_SEED")
    random.seed(None if seed is None else int(seed))
    alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789*#"
    n = random.randint(1, 100)
    print(n)
    for _ in range(n):
        length = random.randint(6, 20)
        print("".join(random.choice(alphabet) for _ in range(length)))


if __name__ == "__main__":
    main()
