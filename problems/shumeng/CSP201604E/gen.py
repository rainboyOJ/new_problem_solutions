#!/usr/bin/env python3
import os
import random


def main():
    seed = os.environ.get("DUPAI_SEED")
    random.seed(None if seed is None else int(seed))

    n = random.randint(2, 10)
    p = random.randint(1, min(6, n - 1))
    all_edges = []
    for v in range(2, n + 1):
        for u in range(max(1, v - p), v):
            all_edges.append((u, v))

    # 先保留链，确保任意一组用户设备都可连通；再随机加入少量边，方便暴力枚举。
    chosen = {(i, i + 1) for i in range(1, n)}
    other_edges = [edge for edge in all_edges if edge not in chosen]
    random.shuffle(other_edges)
    target_m = random.randint(n - 1, min(16, len(all_edges)))
    for edge in other_edges[: target_m - (n - 1)]:
        chosen.add(edge)

    users = ["0"] * n
    for index in random.sample(range(n), random.randint(2, n)):
        users[index] = "1"

    print(1)
    print(n, len(chosen), p)
    print("".join(users))
    for u, v in sorted(chosen):
        print(u, v, random.randint(0, 30))


if __name__ == "__main__":
    main()
