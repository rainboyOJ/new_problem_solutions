#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(2, 300)
    q = random.randint(1, 800)
    seed = random.randint(1, (1 << 32) - 1)

    order = list(range(1, n + 1))
    random.shuffle(order)
    root = order[0]
    parent = [0] * (n + 1)
    parent[root] = 0

    appeared = [root]
    for node in order[1:]:
        parent[node] = random.choice(appeared)
        appeared.append(node)

    print(n, q, seed)
    print(" ".join(str(parent[i]) for i in range(1, n + 1)))


if __name__ == "__main__":
    main()
