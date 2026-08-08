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
    for i in range(1, n + 1):
        for j in range(i + 1, n + 1):
            all_edges.append((i, j))
    m = random.randint(0, len(all_edges))
    edges = random.sample(all_edges, m)
    q = random.randint(1, 8)

    print(n, m, q)
    for u, v in edges:
        print(u, v)
    for _ in range(q):
        a = random.randint(1, n)
        L = random.randint(1, 8)
        print(a, L)


if __name__ == "__main__":
    main()
