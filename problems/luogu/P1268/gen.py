#!/usr/bin/env python3
import random
from collections import defaultdict, deque


def build_random_tree(n: int):
    next_id = n + 1
    comps = list(range(1, n + 1))
    graph = defaultdict(list)

    # 反复把两棵子树接到一个新点上，生成一棵边权非负的树。
    while len(comps) > 1:
        i = random.randrange(len(comps))
        u = comps.pop(i)
        j = random.randrange(len(comps))
        v = comps.pop(j)

        x = next_id
        next_id += 1

        wu = random.randint(0, 20)
        wv = random.randint(0, 20)

        graph[x].append((u, wu))
        graph[u].append((x, wu))
        graph[x].append((v, wv))
        graph[v].append((x, wv))

        comps.append(x)

    return graph


def get_distance_matrix(graph, n: int):
    dist = [[0] * (n + 1) for _ in range(n + 1)]
    for s in range(1, n + 1):
        q = deque([s])
        seen = {s: 0}
        while q:
            u = q.popleft()
            for v, w in graph[u]:
                if v not in seen:
                    seen[v] = seen[u] + w
                    q.append(v)
        for t in range(1, n + 1):
            dist[s][t] = seen[t]
    return dist


def main():
    random.seed()
    n = random.randint(2, 8)
    graph = build_random_tree(n)
    dist = get_distance_matrix(graph, n)

    print(n)
    for i in range(1, n):
        row = []
        for j in range(i + 1, n + 1):
            row.append(str(dist[i][j]))
        print(" ".join(row))


if __name__ == "__main__":
    main()
