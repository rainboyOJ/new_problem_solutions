#!/usr/bin/env python3
import random


def main():
    random.seed()

    n = random.randint(2, 12)
    order = list(range(1, n + 1))
    random.shuffle(order)
    rank = {order[i]: i for i in range(n)}

    pairs = []
    for i in range(1, n + 1):
        for j in range(1, n + 1):
            if i == j:
                continue
            if rank[i] < rank[j]:
                pairs.append((i, j))

    random.shuffle(pairs)
    m = random.randint(1, len(pairs))
    chosen = pairs[:m]

    print(n, len(chosen))
    for u, v in chosen:
        print(u, v)


if __name__ == "__main__":
    main()
