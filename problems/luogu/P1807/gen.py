#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(2, 12)
    edges = []
    for u in range(1, n + 1):
        for v in range(u + 1, n + 1):
            if random.random() < 0.25:
                w = random.randint(-20, 20)
                edges.append((u, v, w))

    print(n, len(edges))
    for u, v, w in edges:
        print(u, v, w)


if __name__ == "__main__":
    main()
