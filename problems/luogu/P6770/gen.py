#!/usr/bin/env python3
import random


def main():
    random.seed()

    f = random.randint(2, 20)
    c = random.randint(1, min(10, f))
    max_edges = f * (f - 1) // 2
    p_target = random.randint(f - 1, min(max_edges, 40))

    edges = {}

    # 先造一棵树，保证连通。
    for i in range(2, f + 1):
        fa = random.randint(1, i - 1)
        w = random.randint(1, 20)
        key = (min(i, fa), max(i, fa))
        edges[key] = w

    while len(edges) < p_target:
        u = random.randint(1, f)
        v = random.randint(1, f)
        if u == v:
            continue
        key = (min(u, v), max(u, v))
        if key in edges:
            continue
        edges[key] = random.randint(1, 20)

    cow_pos = [random.randint(1, f) for _ in range(c)]
    m_limit = random.randint(1, 50)

    print(f, len(edges), c, m_limit)
    for (u, v), w in edges.items():
        print(u, v, w)
    for x in cow_pos:
        print(x)


if __name__ == "__main__":
    main()
