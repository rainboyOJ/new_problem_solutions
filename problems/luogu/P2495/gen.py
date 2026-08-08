#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(2, 80)
    print(n)
    for i in range(2, n + 1):
        parent = random.randint(1, i - 1)
        w = random.randint(1, 50)
        print(parent, i, w)

    q = random.randint(1, 40)
    print(q)
    all_nodes = list(range(2, n + 1))
    for _ in range(q):
        k = random.randint(1, min(n - 1, 12))
        nodes = random.sample(all_nodes, k)
        print(k, *nodes)


if __name__ == "__main__":
    main()
