#!/usr/bin/env python3
import random


def main():
    random.seed()

    n = random.randint(1, 8)
    real_day = [0] * (n + 1)
    real_day[1] = random.randint(1, 5)
    for i in range(2, n + 1):
        real_day[i] = real_day[i - 1] + random.randint(0, 4)

    start = [random.randint(1, real_day[i]) for i in range(1, n + 1)]

    edges = []
    for u in range(1, n + 1):
        for v in range(u + 1, n + 1):
            if random.randint(0, 99) < 30:
                diff = real_day[v] - real_day[u]
                w = random.randint(0, diff)
                edges.append((u, v, w))

    m = max(real_day) + 5
    print(n, m, len(edges))
    print(*start)
    for u, v, w in edges:
        print(u, v, w)


if __name__ == "__main__":
    main()
