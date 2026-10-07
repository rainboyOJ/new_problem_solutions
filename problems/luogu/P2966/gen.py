#!/usr/bin/env python3

import random


def main():
    n = random.randint(2, 8)
    all_pairs = []
    for i in range(1, n + 1):
        for j in range(i + 1, n + 1):
            all_pairs.append((i, j))

    random.shuffle(all_pairs)

    edges = []
    chosen = set()

    order = list(range(1, n + 1))
    random.shuffle(order)
    for i in range(1, n):
        u = order[i]
        v = order[random.randrange(i)]
        a, b = min(u, v), max(u, v)
        chosen.add((a, b))
        edges.append((a, b, random.randint(1, 20)))

    extra = random.randint(0, min(len(all_pairs) - (n - 1), n + 3))
    for u, v in all_pairs:
        if extra == 0:
            break
        if (u, v) in chosen:
            continue
        chosen.add((u, v))
        edges.append((u, v, random.randint(1, 20)))
        extra -= 1

    # 允许同一对点有重边，偶尔补一条重边测试取 min。
    if random.random() < 0.4:
        u, v, _ = random.choice(edges)
        edges.append((u, v, random.randint(1, 20)))

    q = random.randint(1, 8)

    print(n, len(edges), q)
    for _ in range(n):
        print(random.randint(1, 15))
    for u, v, w in edges:
        print(u, v, w)
    for _ in range(q):
        s = random.randint(1, n)
        t = random.randint(1, n)
        while t == s:
            t = random.randint(1, n)
        print(s, t)


if __name__ == "__main__":
    main()
