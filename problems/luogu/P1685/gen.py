#!/usr/bin/env python3
import random


def main():
    random.seed()

    n = random.randint(2, 9)
    s = 1
    t = n
    t0 = random.randint(1, 10)

    edges = []

    def add_edge(u, v, w):
        edges.append((u, v, w))

    # 先放一条基础链，保证一定能从 s 走到 t。
    for u in range(1, n):
        add_edge(u, u + 1, random.randint(1, 10))

    for u in range(1, n):
        for v in range(u + 1, n + 1):
            times = random.randint(0, 2)
            for _ in range(times):
                if random.randint(0, 99) < 35:
                    add_edge(u, v, random.randint(1, 10))

    print(n, len(edges), s, t, t0)
    for u, v, w in edges:
        print(u, v, w)


if __name__ == "__main__":
    main()
