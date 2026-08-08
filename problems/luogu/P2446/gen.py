#!/usr/bin/env python3

import random


def main():
    n = random.randint(2, 8)

    order = list(range(1, n + 1))
    random.shuffle(order)
    pos = {order[i]: i for i in range(n)}

    edges = []
    # 先造一条从 1 到 n 的链，保证有解
    chain = [1]
    middle = [x for x in range(2, n)]
    random.shuffle(middle)
    chain.extend(middle)
    chain.append(n)

    used = set()
    for i in range(len(chain) - 1):
        u = chain[i]
        v = chain[i + 1]
        used.add((u, v))
        edges.append((u, v, random.randint(1, 15)))

    # 再补一些随机单向边
    extra = random.randint(0, n + 4)
    all_pairs = [(i, j) for i in range(1, n + 1) for j in range(1, n + 1)]
    random.shuffle(all_pairs)
    for u, v in all_pairs:
        if extra == 0:
            break
        if (u, v) in used:
            continue
        used.add((u, v))
        edges.append((u, v, random.randint(1, 15)))
        extra -= 1

    req = [[] for _ in range(n + 1)]
    for city in range(2, n + 1):
        candidates = [x for x in range(1, n + 1) if x != city and pos[x] < pos[city]]
        random.shuffle(candidates)
        take = random.randint(0, min(2, len(candidates)))
        req[city] = candidates[:take]

    print(n, len(edges))
    for u, v, w in edges:
        print(u, v, w)
    for city in range(1, n + 1):
        print(len(req[city]), *req[city])


if __name__ == "__main__":
    main()
