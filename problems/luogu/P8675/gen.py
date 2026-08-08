#!/usr/bin/env python3
import os
import random


def main() -> None:
    seed_text = os.environ.get("DUPAI_SEED")
    if seed_text is None:
        random.seed()
    else:
        random.seed(int(seed_text))

    n = random.randint(1, 5)
    m = random.randint(1, 6)
    print(n, m)
    for _ in range(n):
        row = []
        for _ in range(m):
            row.append(random.choice(".X"))
        print("".join(row))


if __name__ == "__main__":
    main()
