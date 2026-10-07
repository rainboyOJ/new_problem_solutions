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
    all_edges = []
    for u in range(1, n + 1):
        for v in range(1, n + 1):
            if u != v:
                all_edges.append((u, v))
    m = random.randint(0, len(all_edges))
    edges = random.sample(all_edges, m)

    print(n, m)
    for u, v in edges:
        print(u, v)


if __name__ == "__main__":
    main()
