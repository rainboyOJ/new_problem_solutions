#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(2, 10)
    k = 10
    limit = random.randint(2, min(9, n))
    chain_length = random.randint(2, limit)
    chain = [0] + random.sample(range(1, n - 1), chain_length - 2) + [n - 1]

    color = [-1] * n
    color[0] = 0
    color[n - 1] = k - 1
    available = list(range(1, k - 1))
    random.shuffle(available)
    for i in range(1, chain_length - 1): color[chain[i]] = available[i - 1]
    for i in range(n):
        if color[i] == -1: color[i] = random.randint(1, k - 2)

    edge = set()
    for i in range(chain_length - 1): edge.add((chain[i], chain[i + 1]))
    maximum_edge = n * (n - 1)
    edge_count = random.randint(len(edge), min(maximum_edge, 35))
    while len(edge) < edge_count:
        u = random.randrange(n)
        v = random.randrange(n)
        if u != v and color[u] != color[v]: edge.add((u, v))
    edge = list(edge)
    random.shuffle(edge)

    print(n, len(edge), limit, k)
    print(*color)
    print(*(u for u, v in edge))
    print(*(v for u, v in edge))
    print(*(random.randint(1, 20) for _ in edge))


if __name__ == "__main__":
    main()
