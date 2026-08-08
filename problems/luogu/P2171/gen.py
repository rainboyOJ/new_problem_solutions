#!/usr/bin/env python3
import os
import random


def main() -> None:
    seed_text = os.environ.get("DUPAI_SEED")
    if seed_text is None:
        random.seed()
    else:
        random.seed(int(seed_text))

    n = random.randint(1, 60)
    values = random.sample(range(1, 10000), n)
    print(n)
    print(*values)


if __name__ == "__main__":
    main()
