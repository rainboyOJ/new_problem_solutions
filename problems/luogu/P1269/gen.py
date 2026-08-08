#!/usr/bin/env python3
import random
from collections import defaultdict


def main():
    random.seed()

    n = random.randint(2, 12)
    s = random.randint(1, 10)

    g = defaultdict(list)
    for v in range(2, n + 1):
        p = random.randint(1, v - 1)
        w = random.randint(1, 10)
        g[p].append((v, w))
        g[v].append((p, w))

    print(n)
    for u in range(1, n + 1):
        print(len(g[u]), end="")
        for v, w in g[u]:
            print(" {} {}".format(v, w), end="")
        print()
    print(s)


if __name__ == "__main__":
    main()
