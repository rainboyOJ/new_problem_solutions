#!/usr/bin/env python3

import random


def main():
    n = random.randint(2, 8)
    all_pairs = []
    for i in range(1, n + 1):
        for j in range(i + 1, n + 1):
            all_pairs.append((i, j))

    random.shuffle(all_pairs)

    chosen = []

    # 先造一棵随机树，保证连通。
    order = list(range(1, n + 1))
    random.shuffle(order)
    for i in range(1, n):
        u = order[i]
        v = order[random.randrange(i)]
        a, b = min(u, v), max(u, v)
        chosen.append((a, b))

    chosen_set = set(chosen)

    extra = random.randint(0, min(len(all_pairs) - len(chosen), n + 2))
    for u, v in all_pairs:
        if len(chosen_set) >= n - 1 + extra:
            break
        if (u, v) in chosen_set:
            continue
        chosen.append((u, v))
        chosen_set.add((u, v))

    print(n, len(chosen))
    for u, v in chosen:
        w = random.randint(1, 20)
        print(u, v, w)


if __name__ == "__main__":
    main()
