#!/usr/bin/env python3
import random


def main():
    random.seed()

    n = random.randint(2, 7)
    edges = []
    used = set()

    for i in range(2, n + 1):
        p = random.randint(1, i - 1)
        w = random.randint(1, 20)
        edges.append((p, i, w))
        used.add((min(p, i), max(p, i)))

    extra = []
    for i in range(1, n + 1):
        for j in range(i + 1, n + 1):
            if (i, j) not in used:
                extra.append((i, j))

    random.shuffle(extra)
    extra_cnt = random.randint(0, min(5, len(extra)))
    for i in range(extra_cnt):
        u, v = extra[i]
        w = random.randint(1, 20)
        edges.append((u, v, w))

    random.shuffle(edges)
    print(n, len(edges))
    for u, v, w in edges:
        print(u, v, w)


if __name__ == "__main__":
    main()
