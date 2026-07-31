#!/usr/bin/env python3
import os
import random


def main():
    seed = os.environ.get("DUPAI_SEED")
    random.seed(None if seed is None else int(seed))
    n = random.randint(2, 7)
    edges = []
    used = set()
    for i in range(2, n + 1):
        u = random.randint(1, i - 1)
        edges.append((u, i, random.randint(1, 30)))
        used.add((min(u, i), max(u, i)))
    extra = random.randint(0, min(6, n * (n - 1) // 2 - len(edges)))
    while extra > 0:
        u, v = random.sample(range(1, n + 1), 2)
        key = (min(u, v), max(u, v))
        if key in used:
            continue
        used.add(key)
        edges.append((u, v, random.randint(1, 30)))
        extra -= 1
    print(n, len(edges))
    for edge in edges:
        print(*edge)


if __name__ == "__main__":
    main()
