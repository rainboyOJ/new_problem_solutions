#!/usr/bin/env python3
import random


def main():
    random.seed()

    n = random.randint(2, 7)
    need_level1 = random.randint(0, n - 1)

    all_edges = []
    for i in range(1, n + 1):
        for j in range(i + 1, n + 1):
            all_edges.append((i, j))

    random.shuffle(all_edges)
    edge_cnt = random.randint(n - 1, min(len(all_edges), 10))
    chosen = all_edges[:edge_cnt]

    print(n, need_level1, edge_cnt + 1)
    for u, v in chosen:
        c2 = random.randint(1, 20)
        c1 = random.randint(c2, 25)
        print(u, v, c1, c2)


if __name__ == "__main__":
    main()
