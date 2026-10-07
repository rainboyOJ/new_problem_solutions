#!/usr/bin/env python3
import random


def main():
    random.seed()

    n = random.randint(2, 8)
    all_edges = []
    for i in range(1, n + 1):
        for j in range(i + 1, n + 1):
            all_edges.append((i, j))

    random.shuffle(all_edges)

    tree = []
    used = set()
    for i in range(2, n + 1):
        p = random.randint(1, i - 1)
        u, v = min(i, p), max(i, p)
        tree.append((u, v))
        used.add((u, v))

    extra = [e for e in all_edges if e not in used]
    random.shuffle(extra)
    add_cnt = random.randint(0, min(len(extra), n + 2))
    edges = tree + extra[:add_cnt]
    random.shuffle(edges)

    print(n, len(edges))
    for u, v in edges:
        print(u, v)


if __name__ == "__main__":
    main()
