#!/usr/bin/env python3
import random


def main():
    random.seed()

    n = random.randint(2, 10)
    m = random.randint(1, min(3, n))

    g = [[] for _ in range(n + 1)]
    indeg = [0] * (n + 1)

    for u in range(1, n + 1):
        candidates = list(range(max(u + 1, m + 1), n + 1))
        random.shuffle(candidates)
        d = random.randint(0, min(3, len(candidates)))
        g[u] = sorted(candidates[:d])
        for v in g[u]:
            indeg[v] += 1

    # 保证前 m 个点是接收口，没有入边。
    for i in range(1, m + 1):
        for u in range(1, i):
            if i in g[u]:
                g[u].remove(i)
        indeg[i] = 0

    print(n, m)
    for i in range(1, n + 1):
        print(len(g[i]), *g[i])


if __name__ == "__main__":
    main()
