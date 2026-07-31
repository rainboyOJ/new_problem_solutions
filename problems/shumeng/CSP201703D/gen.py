#!/usr/bin/env python3
import os
import random


def main():
    seed = os.environ.get("DUPAI_SEED")
    random.seed(None if seed is None else int(seed))

    n = random.randint(2, 9)
    edges = {(i, i + 1) for i in range(1, n)}
    candidates = [(u, v) for u in range(1, n + 1) for v in range(u + 1, n + 1)]
    random.shuffle(candidates)
    for edge in candidates[: random.randint(0, len(candidates) - n + 1)]:
        edges.add(edge)

    print(n, len(edges))
    for u, v in sorted(edges):
        print(u, v, random.randint(1, 30))


if __name__ == "__main__":
    main()
