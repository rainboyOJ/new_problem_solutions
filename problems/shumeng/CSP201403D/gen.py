#!/usr/bin/env python3
"""CSP201403D 的小数据连通网络生成器，供状态 BFS 与枚举对拍。"""

import os
import random


def main():
    seed = os.environ.get("DUPAI_SEED")
    random.seed(None if seed is None else int(seed))

    router_count = random.randint(2, 7)
    candidate_count = random.randint(1, 10)
    radius = 3
    limit = 2 * (router_count - 1)
    points = [(0, 0), (limit, 0)]
    for index in range(1, router_count - 1):
        points.append((2 * index, 0))

    used = set(points)
    while len(points) < router_count + candidate_count:
        point = (random.randint(-2, limit + 2), random.randint(-2, 2))
        if point not in used:
            used.add(point)
            points.append(point)

    print(router_count, candidate_count, random.randint(1, candidate_count), radius)
    for point in points:
        print(*point)


if __name__ == "__main__":
    main()
