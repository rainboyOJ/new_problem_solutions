#!/usr/bin/env python3
import os
import random


def main() -> None:
    seed_text = os.environ.get("DUPAI_SEED")
    if seed_text is None:
        random.seed()
    else:
        random.seed(int(seed_text))

    n = random.randint(1, 6)
    capacity = random.randint(0, 40)
    print(n, capacity)
    for _ in range(n):
        value = random.randint(1, 12)
        weight = random.randint(1, 10)
        count = random.randint(1, 6)
        print(value, weight, count)


if __name__ == "__main__":
    main()
