#!/usr/bin/env python3

import random
from collections import deque


def reachable(n, edges, ban_idx):
    g = [[] for _ in range(n + 1)]
    for idx, (u, v, _) in enumerate(edges):
        if idx == ban_idx:
            continue
        g[u].append(v)
        g[v].append(u)

    q = deque([1])
    vis = [False] * (n + 1)
    vis[1] = True

    while q:
        u = q.popleft()
        for v in g[u]:
            if vis[v]:
                continue
            vis[v] = True
            q.append(v)

    return vis[n]


def valid_graph(n, edges):
    if not reachable(n, edges, -1):
        return False
    for i in range(len(edges)):
        if not reachable(n, edges, i):
            return False
    return True


def main():
    while True:
        n = random.randint(4, 8)
        all_pairs = []
        for i in range(1, n + 1):
            for j in range(i + 1, n + 1):
                all_pairs.append((i, j))

        random.shuffle(all_pairs)
        m = random.randint(n, min(len(all_pairs), n + 5))
        choose = all_pairs[:m]
        edges = []
        for u, v in choose:
            w = random.randint(1, 20)
            edges.append((u, v, w))

        if valid_graph(n, edges):
            print(n, m)
            for u, v, w in edges:
                print(u, v, w)
            return


if __name__ == "__main__":
    main()
