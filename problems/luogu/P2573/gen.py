#!/usr/bin/env python3
import random


def main():
    random.seed()

    n = random.randint(1, 9)
    all_edges = []
    for i in range(1, n + 1):
        for j in range(i + 1, n + 1):
            all_edges.append((i, j))
    random.shuffle(all_edges)
    m = random.randint(0, min(len(all_edges), 15))

    heights = [random.randint(1, 8) for _ in range(n)]
    print(n, m)
    print(*heights)

    for u, v in all_edges[:m]:
        print(u, v, random.randint(1, 20))


if __name__ == "__main__":
    main()
