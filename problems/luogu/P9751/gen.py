#!/usr/bin/env python3
import os
import random


def main() -> None:
    seed_text = os.environ.get("DUPAI_SEED")
    if seed_text is None:
        random.seed()
    else:
        random.seed(int(seed_text))

    n = random.randint(2, 7)
    k = random.randint(1, 5)
    all_edges = [(u, v) for u in range(1, n + 1) for v in range(1, n + 1) if u != v]
    m = random.randint(1, len(all_edges))
    edges = random.sample(all_edges, m)

    print(n, m, k)
    for u, v in edges:
        print(u, v, random.randint(0, 10))


if __name__ == "__main__":
    main()
