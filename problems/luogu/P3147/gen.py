#!/usr/bin/env python3
import os
import random


def main() -> None:
    seed_text = os.environ.get("DUPAI_SEED")
    if seed_text is None:
        random.seed()
    else:
        random.seed(int(seed_text))

    n = random.randint(2, 10)
    print(n)
    for _ in range(n):
        print(random.randint(1, 6))


if __name__ == "__main__":
    main()
