#!/usr/bin/env python3

import random


def main():
    n = random.randint(2, 8)
    k = random.randint(0, min(4, n))
    s = random.randint(0, n - 1)
    t = random.randint(0, n - 1)
    while t == s:
        t = random.randint(0, n - 1)

    all_pairs = []
    for i in range(n):
        for j in range(i + 1, n):
            all_pairs.append((i, j))

    random.shuffle(all_pairs)

    chosen = []
    used = set()

    order = list(range(n))
    random.shuffle(order)
    for i in range(1, n):
        u = order[i]
        v = order[random.randrange(i)]
        a, b = min(u, v), max(u, v)
        used.add((a, b))
        chosen.append((a, b, random.randint(0, 20)))

    extra = random.randint(0, min(len(all_pairs) - (n - 1), n + 4))
    for u, v in all_pairs:
        if extra == 0:
            break
        if (u, v) in used:
            continue
        used.add((u, v))
        chosen.append((u, v, random.randint(0, 20)))
        extra -= 1

    print(n, len(chosen), k)
    print(s, t)
    for u, v, w in chosen:
        print(u, v, w)


if __name__ == "__main__":
    main()
