#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(2, 30)
    all_pairs = []
    used = set()

    # 先保证 1 可以到 n。
    path = list(range(1, n + 1))
    for i in range(1, n):
        used.add((i, i + 1))
        all_pairs.append((i, i + 1, 1))

    candidates = []
    for i in range(1, n + 1):
        for j in range(1, n + 1):
            if i == j:
                continue
            a = min(i, j)
            b = max(i, j)
            if (a, b) not in used:
                candidates.append((a, b))

    random.shuffle(candidates)
    extra = random.randint(0, min(len(candidates), 80))
    for i in range(extra):
        a, b = candidates[i]
        z = random.randint(1, 2)
        if z == 1 and random.randint(0, 1) == 1:
            a, b = b, a
        all_pairs.append((a, b, z))

    prices = [random.randint(1, 100) for _ in range(n)]
    print(n, len(all_pairs))
    print(" ".join(str(x) for x in prices))
    for x, y, z in all_pairs:
        print(x, y, z)


if __name__ == "__main__":
    main()
