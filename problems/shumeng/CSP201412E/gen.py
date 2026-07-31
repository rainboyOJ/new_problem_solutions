#!/usr/bin/env python3
import os
import random


def main():
    seed = os.environ.get("DUPAI_SEED")
    random.seed(None if seed is None else int(seed))
    n = random.randint(2, 4)
    extra = random.randint(0, n * (n - 1) // 2 - (n - 1))
    roads = [(i, i + 1, random.randint(1, 5)) for i in range(1, n)]
    used = {(min(u, v), max(u, v)) for u, v, _ in roads}
    while extra > 0:
        u, v = random.sample(range(1, n + 1), 2)
        key = (min(u, v), max(u, v))
        if key in used: continue
        used.add(key)
        roads.append((u, v, random.randint(1, 5)))
        extra -= 1

    production = [[random.randint(0, 3) for _ in range(7)] for _ in range(n)]
    total = sum(sum(row) for row in production)
    if total == 0:
        production[0][0] = 1
        total = 1
    demand_flat = [0] * (n * 7)
    for _ in range(total):
        demand_flat[random.randrange(n * 7)] += 1
    demand = [demand_flat[i * 7:(i + 1) * 7] for i in range(n)]

    print(n, len(roads))
    for city in range(n):
        print(*(production[city] + demand[city] + [100, random.randint(1, 5)]))
    for road in roads:
        print(*road)


if __name__ == "__main__":
    main()
