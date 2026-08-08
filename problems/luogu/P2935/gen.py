#!/usr/bin/env python3
import random


def main():
    random.seed()

    p = random.randint(2, 8)
    f = random.randint(1, p)
    max_edges = p * (p - 1) // 2
    c = random.randint(p - 1, min(max_edges, 14))

    fav = random.sample(range(1, p + 1), f)

    edges = {}

    # 先造一棵树，保证图连通。
    for i in range(2, p + 1):
        fa = random.randint(1, i - 1)
        w = random.randint(1, 20)
        key = (min(i, fa), max(i, fa))
        edges[key] = w

    # 再随机补边。
    while len(edges) < c:
        u = random.randint(1, p)
        v = random.randint(1, p)
        if u == v:
            continue
        key = (min(u, v), max(u, v))
        if key in edges:
            continue
        edges[key] = random.randint(1, 20)

    print(p, f, len(edges))
    for x in fav:
        print(x)
    for (u, v), w in edges.items():
        print(u, v, w)


if __name__ == "__main__":
    main()
