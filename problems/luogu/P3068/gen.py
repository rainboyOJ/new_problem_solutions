#!/usr/bin/env python3
import os
import random


def main():
    seed_text = os.environ.get("DUPAI_SEED")
    if seed_text is not None:
        random.seed(int(seed_text))
    else:
        random.seed()

    n = random.randint(1, 12)
    max_groups = min(12, (1 << n) - 1)
    m = random.randint(0, max_groups)

    print(n, m)
    used_groups = set()
    for _ in range(m):
        while True:
            size = random.randint(1, n)
            cows = tuple(sorted(random.sample(range(1, n + 1), size)))
            if cows not in used_groups:
                used_groups.add(cows)
                break
        print(size, *cows)


if __name__ == "__main__":
    main()
