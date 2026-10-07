#!/usr/bin/env python3
import os
import random


def main():
    seed_text = os.environ.get("DUPAI_SEED")
    if seed_text is not None:
        random.seed(int(seed_text))
    else:
        random.seed()

    n = random.randint(1, 8)
    a = [random.randint(-10, 10) for _ in range(n)]

    print(n)
    print(*a)


if __name__ == "__main__":
    main()
