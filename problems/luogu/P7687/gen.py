#!/usr/bin/env python3
import random


def connected_graph(n: int, m: int):
    edges = []
    used = set()

    for i in range(2, n + 1):
        p = random.randint(1, i - 1)
        u, v = min(i, p), max(i, p)
        edges.append((u, v))
        used.add((u, v))

    candidates = []
    for i in range(1, n + 1):
        for j in range(i + 1, n + 1):
            if (i, j) not in used:
                candidates.append((i, j))

    random.shuffle(candidates)
    need = m - (n - 1)
    edges.extend(candidates[:need])
    random.shuffle(edges)
    return edges


def main():
    random.seed()

    n = random.randint(2, 8)
    max_m = n * (n - 1) // 2
    m = random.randint(n - 1, min(max_m, n + 4))

    cnt_a = random.randint(1, n)
    cnt_b = random.randint(1, n)

    nodes = list(range(1, n + 1))
    random.shuffle(nodes)
    a_nodes = nodes[:cnt_a]
    random.shuffle(nodes)
    b_nodes = nodes[:cnt_b]

    edges = connected_graph(n, m)

    print(n, m, cnt_a, cnt_b)
    print(" ".join(map(str, a_nodes)))
    print(" ".join(map(str, b_nodes)))
    for u, v in edges:
        print(u, v)


if __name__ == "__main__":
    main()
