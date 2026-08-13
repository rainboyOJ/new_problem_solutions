#!/usr/bin/env python3
import os
import random


def main() -> None:
    seed_text = os.environ.get("DUPAI_SEED")
    if seed_text is None:
        random.seed()
    else:
        random.seed(int(seed_text))

    n = random.randint(2, 12)
    edges = []
    for i in range(2, n + 1):
        parent = random.randint(1, i - 1)
        weight = random.randint(0, 10)
        edges.append((i, parent, weight))

    random.shuffle(edges)
    print(n)
    for u, v, w in edges:
        print(u, v, w)


if __name__ == "__main__":
    main()
