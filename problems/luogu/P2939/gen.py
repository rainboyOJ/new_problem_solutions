#!/usr/bin/env python3

import random


def main():
    n = random.randint(2, 8)
    k = random.randint(1, min(4, n))

    all_pairs = []
    for i in range(1, n + 1):
        for j in range(i + 1, n + 1):
            all_pairs.append((i, j))

    random.shuffle(all_pairs)

    chosen = []
    used = set()

    order = list(range(1, n + 1))
    random.shuffle(order)
    for i in range(1, n):
        u = order[i]
        v = order[random.randrange(i)]
        a, b = min(u, v), max(u, v)
        used.add((a, b))
        chosen.append((a, b, random.randint(1, 20)))

    extra = random.randint(0, min(len(all_pairs) - (n - 1), n + 4))
    for u, v in all_pairs:
        if extra == 0:
            break
        if (u, v) in used:
            continue
        used.add((u, v))
        chosen.append((u, v, random.randint(1, 20)))
        extra -= 1

    print(n, len(chosen), k)
    for u, v, w in chosen:
        print(u, v, w)


if __name__ == "__main__":
    main()
