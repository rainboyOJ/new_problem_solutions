#!/usr/bin/env python3
import random


def gen_case():
    n = random.randint(2, 7)
    costs = [random.randint(1, 20) for _ in range(n)]

    tree_edges = []
    for i in range(2, n + 1):
        parent = random.randint(1, i - 1)
        w = random.randint(0, 20)
        tree_edges.append((parent, i, w))

    extra_candidates = []
    exist = {(min(u, v), max(u, v)) for u, v, _ in tree_edges}
    for u in range(1, n + 1):
        for v in range(u + 1, n + 1):
            if (u, v) not in exist:
                extra_candidates.append((u, v))

    random.shuffle(extra_candidates)
    extra_cnt = random.randint(0, min(len(extra_candidates), 4))

    edges = list(tree_edges)
    for u, v in extra_candidates[:extra_cnt]:
        edges.append((u, v, random.randint(0, 20)))

    random.shuffle(edges)
    return n, costs, edges


def main():
    random.seed()
    n, costs, edges = gen_case()
    print(n, len(edges))
    for x in costs:
        print(x)
    for u, v, w in edges:
        print(u, v, w)


if __name__ == "__main__":
    main()
