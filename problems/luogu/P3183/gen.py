#!/usr/bin/env python3
import random
import sys


def main() -> None:
    if len(sys.argv) > 1:
        random.seed(int(sys.argv[1]))

    n = random.randint(2, 12)
    order = list(range(1, n + 1))
    random.shuffle(order)

    edges = []
    for i in range(n):
        for j in range(i + 1, n):
            if random.randint(0, 99) < 25:
                edges.append((order[i], order[j]))

    print(n, len(edges))
    for u, v in edges:
        print(u, v)


if __name__ == "__main__":
    main()
