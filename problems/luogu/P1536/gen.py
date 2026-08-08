#!/usr/bin/env python3
import random


def gen_case():
    n = random.randint(1, 10)
    edges = set()
    m = random.randint(0, 15)
    for _ in range(m):
        x = random.randint(1, n)
        y = random.randint(1, n)
        if x == y:
            continue
        if x > y:
            x, y = y, x
        edges.add((x, y))
    return n, list(edges)


def main():
    random.seed()
    t = random.randint(1, 4)
    for _ in range(t):
        n, edges = gen_case()
        print(n, len(edges))
        for x, y in edges:
            print(x, y)
    print(0)


if __name__ == "__main__":
    main()
