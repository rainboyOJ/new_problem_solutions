#!/usr/bin/env python3
import os
import random


def connected_graph(n: int, extra_edges: int):
    edges = set()
    for i in range(2, n + 1):
        p = random.randint(1, i - 1)
        edges.add((min(i, p), max(i, p)))
    candidates = [
        (i, j)
        for i in range(1, n + 1)
        for j in range(i + 1, n + 1)
        if (i, j) not in edges
    ]
    random.shuffle(candidates)
    for i in range(min(extra_edges, len(candidates))):
        edges.add(candidates[i])
    return sorted(edges)


def main() -> None:
    seed_text = os.environ.get("DUPAI_SEED")
    if seed_text is None:
        random.seed()
    else:
        random.seed(int(seed_text))

    n = random.randint(3, 8)
    extra = random.randint(0, max(0, n))
    edges = connected_graph(n, extra)
    x, y = random.sample(range(1, n + 1), 2)

    print(n, len(edges))
    for u, v in edges:
        print(u, v)
    print(x, y)


if __name__ == "__main__":
    main()
