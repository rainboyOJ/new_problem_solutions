#!/usr/bin/env python3
import random
import os


def main():
    seed = os.environ.get("DUPAI_SEED")
    random.seed(None if seed is None else int(seed))

    n = random.randint(1, 7)
    all_edges = []
    for u in range(1, n + 1):
        for v in range(u, n + 1):
            all_edges.append((u, v))
    m = random.randint(0, min(len(all_edges), 10))
    edges = random.sample(all_edges, m)

    delay_time = random.randint(1, 4)
    groups = random.randint(1, 10)
    operations = []
    current_time = random.randint(0, 2)
    next_block = 1
    for _ in range(groups):
        current_time += random.randint(0, 4)
        for _ in range(random.randint(0, 3)):
            node = random.randint(1, n)
            operations.append((node, current_time, next_block))
            next_block += 1
        for _ in range(random.randint(1, 3)):
            operations.append((random.randint(1, n), current_time))

    print(n, m)
    for u, v in edges:
        print(u, v)
    print(delay_time, len(operations))
    for operation in operations:
        print(*operation)


if __name__ == "__main__":
    main()
