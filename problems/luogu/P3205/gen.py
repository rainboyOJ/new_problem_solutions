#!/usr/bin/env python3
import os
import random


def main() -> None:
    seed_text = os.environ.get("DUPAI_SEED")
    if seed_text is None:
        random.seed()
    else:
        random.seed(int(seed_text))

    n = random.randint(1, 8)
    arr = random.sample(range(1000, 1020), n)

    print(n)
    print(*arr)


if __name__ == "__main__":
    main()
