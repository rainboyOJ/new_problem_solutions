#!/usr/bin/env python3
import random


def main():
    random.seed()

    p = random.randint(3, 20)
    nodes = list(range(1, p + 1))
    pb, pa1, pa2 = random.sample(nodes, 3)

    max_edges = p * (p - 1) // 2
    c_target = random.randint(p - 1, min(max_edges, 40))

    edges = {}

    # 先造一棵树，保证连通。
    for i in range(2, p + 1):
        fa = random.randint(1, i - 1)
        key = (min(i, fa), max(i, fa))
        edges[key] = random.randint(1, 20)

    while len(edges) < c_target:
        u = random.randint(1, p)
        v = random.randint(1, p)
        if u == v:
            continue
        key = (min(u, v), max(u, v))
        if key in edges:
            continue
        edges[key] = random.randint(1, 20)

    print(len(edges), p, pb, pa1, pa2)
    for (u, v), w in edges.items():
        print(u, v, w)


if __name__ == "__main__":
    main()
