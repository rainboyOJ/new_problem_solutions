#!/usr/bin/env python3
import os
import random


def main() -> None:
    seed_text = os.environ.get("DUPAI_SEED")
    if seed_text is None:
        random.seed()
    else:
        random.seed(int(seed_text))

    n = random.randint(1, 10)
    all_edges = []
    for i in range(1, n + 1):
        for j in range(i + 1, n + 1):
            all_edges.append((i, j))

    m = random.randint(0, len(all_edges))
    edges = random.sample(all_edges, m)

    print(n, m)
    for u, v in edges:
        print(u, v, random.randint(1, 20))


if __name__ == "__main__":
    main()
