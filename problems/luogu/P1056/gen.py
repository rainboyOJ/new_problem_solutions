#!/usr/bin/env python3
import random


def main():
    random.seed()

    m = random.randint(2, 7)
    n = random.randint(2, 7)
    k = random.randint(0, m - 1)
    l = random.randint(0, n - 1)
    d = random.randint(1, 12)

    pairs = set()
    candidates = []

    for x in range(1, m + 1):
        for y in range(1, n + 1):
            if x + 1 <= m:
                candidates.append((x, y, x + 1, y))
            if y + 1 <= n:
                candidates.append((x, y, x, y + 1))

    random.shuffle(candidates)
    for item in candidates:
        if len(pairs) >= d:
            break
        pairs.add(item)

    print(m, n, k, l, len(pairs))
    for x1, y1, x2, y2 in pairs:
        print(x1, y1, x2, y2)


if __name__ == "__main__":
    main()
