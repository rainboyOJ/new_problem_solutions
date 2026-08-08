#!/usr/bin/env python3
import os
import random


def main() -> None:
    seed_text = os.environ.get("DUPAI_SEED")
    if seed_text is None:
        random.seed()
    else:
        random.seed(int(seed_text))

    p = random.randint(1, 15)
    q = random.randint(1, min(6, p))
    arr = sorted(random.sample(range(1, p + 1), q))

    print(p, q)
    print(*arr)


if __name__ == "__main__":
    main()
