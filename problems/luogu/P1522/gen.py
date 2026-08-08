#!/usr/bin/env python3

import random


def random_partition(n, parts):
    sizes = [1] * parts
    left = n - parts
    while left > 0:
        idx = random.randrange(parts)
        sizes[idx] += 1
        left -= 1
    return sizes


def build_component(nodes, g):
    for i in range(1, len(nodes)):
        u = nodes[i]
        v = nodes[random.randrange(i)]
        g[u][v] = 1
        g[v][u] = 1

    for i in range(len(nodes)):
        for j in range(i + 1, len(nodes)):
            if g[nodes[i]][nodes[j]] == 0 and random.random() < 0.35:
                u = nodes[i]
                v = nodes[j]
                g[u][v] = 1
                g[v][u] = 1


def main():
    n = random.randint(2, 8)
    part_cnt = random.randint(2, min(4, n))
    sizes = random_partition(n, part_cnt)

    used = set()
    coord = [None]
    for _ in range(n):
        while True:
            x = random.randint(0, 20)
            y = random.randint(0, 20)
            if (x, y) not in used:
                used.add((x, y))
                coord.append((x, y))
                break

    g = [[0] * (n + 1) for _ in range(n + 1)]

    order = list(range(1, n + 1))
    random.shuffle(order)

    pos = 0
    for size in sizes:
        nodes = order[pos:pos + size]
        pos += size
        build_component(nodes, g)

    print(n)
    for i in range(1, n + 1):
        print(coord[i][0], coord[i][1])
    for i in range(1, n + 1):
        print("".join(str(g[i][j]) for j in range(1, n + 1)))


if __name__ == "__main__":
    main()
