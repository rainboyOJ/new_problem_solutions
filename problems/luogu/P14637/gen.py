#!/usr/bin/env python3
import random


def main():
    random.seed()
    t = 1
    print(t)

    n = random.randint(2, 6)
    parent = []
    depth = [0] * (n + 1)
    max_depth = 0
    for i in range(2, n + 1):
        p = random.randint(1, i - 1)
        parent.append(p)
        depth[i] = depth[p] + 1
        max_depth = max(max_depth, depth[i])

    m = random.randint(max(1, max_depth), n - 1)
    print(n, m)
    print(" ".join(map(str, parent)))


if __name__ == "__main__":
    main()
