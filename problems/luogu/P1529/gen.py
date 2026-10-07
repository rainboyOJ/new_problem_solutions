#!/usr/bin/env python3
import random


def pool():
    return [chr(ord("a") + i) for i in range(26)] + [chr(ord("A") + i) for i in range(26)]


def main():
    random.seed()

    nodes = pool()
    nodes.remove("Z")

    upper = [chr(ord("A") + i) for i in range(25)]  # A..Y
    random.shuffle(upper)
    chosen_upper = upper[: random.randint(1, 6)]

    all_nodes = ["Z"] + chosen_upper
    extra = random.sample([x for x in nodes if x not in chosen_upper], random.randint(0, 8))
    all_nodes += extra

    edges = {}

    # 先保证每只牛都能到 Z。
    for ch in chosen_upper:
        w = random.randint(1, 20)
        key = tuple(sorted((ch, "Z")))
        edges[key] = min(edges.get(key, 10**9), w)

    target_p = random.randint(len(edges), min(25, len(all_nodes) * (len(all_nodes) - 1) // 2))

    while len(edges) < target_p:
        a, b = random.sample(all_nodes, 2)
        key = tuple(sorted((a, b)))
        if key in edges:
            continue
        edges[key] = random.randint(1, 20)

    print(len(edges))
    for (a, b), w in edges.items():
        print(a, b, w)


if __name__ == "__main__":
    main()
