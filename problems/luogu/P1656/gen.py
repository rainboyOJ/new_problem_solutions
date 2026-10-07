#!/usr/bin/env python3
import random


def main():
    random.seed()

    n = random.randint(2, 8)
    tree_edges = []
    used = set()
    for i in range(2, n + 1):
        p = random.randint(1, i - 1)
        tree_edges.append((p, i))
        used.add((min(p, i), max(p, i)))

    extra = []
    for i in range(1, n + 1):
        for j in range(i + 1, n + 1):
            if (i, j) not in used:
                extra.append((i, j))
    random.shuffle(extra)
    extra_cnt = random.randint(0, min(len(extra), 5))

    edges = tree_edges + extra[:extra_cnt]
    random.shuffle(edges)
    print(n, len(edges))
    for u, v in edges:
        print(u, v)


if __name__ == "__main__":
    main()
