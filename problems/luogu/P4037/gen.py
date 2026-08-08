#!/usr/bin/env python3
import random


def main():
    n = random.randint(1, 10)
    m = random.randint(0, 30)

    children = [[] for _ in range(n + 1)]
    parent = [0] * (n + 1)

    for i in range(2, n + 1):
        if random.randint(0, 1) == 0:
            p = random.randint(1, i - 1)
            need = random.randint(1, 2)
            children[p].append((i, need))
            parent[i] = p

    print(n, m)
    for i in range(1, n + 1):
        power = random.randint(1, 15)
        if children[i]:
            print(power, "A", len(children[i]), end="")
            for v, need in children[i]:
                print("", v, need, end="")
            print()
        else:
            cost = random.randint(1, 10)
            limit = random.randint(0, 5)
            print(power, "B", cost, limit)


if __name__ == "__main__":
    main()
