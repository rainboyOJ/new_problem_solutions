#!/usr/bin/env python3
import os
import random


def main():
    seed = os.environ.get("DUPAI_SEED")
    random.seed(None if seed is None else int(seed))

    n = random.randint(1, 35)
    m = random.randint(1, 100)
    parent = [0] * (n + 1)
    children = [[] for _ in range(n + 1)]
    alive = [True] * (n + 1)

    for node in range(2, n + 1):
        parent[node] = random.randint(1, node - 1)
        children[parent[node]].append(node)

    print(n, m)
    print(*parent[2:])
    print(*[random.randint(0, 100) for _ in range(n)])

    # 生成操作时同步维护当前树，保证操作对象始终没有被删除。
    operations = []
    for _ in range(m):
        available = [node for node in range(1, n + 1) if alive[node]]
        node = random.choice(available)
        if random.randint(0, 1) == 0:
            operations.append((2, node))
            continue

        operations.append((1, node))
        old_children = children[node]
        children[node] = []
        for removed in old_children:
            alive[removed] = False
            children[node].extend(children[removed])
            children[removed] = []

    for operation in operations:
        print(operation[0], operation[1])


if __name__ == "__main__":
    main()
