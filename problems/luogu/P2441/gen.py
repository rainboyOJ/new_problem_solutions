#!/usr/bin/env python3
import os
import random


def main() -> None:
    seed_text = os.environ.get("DUPAI_SEED")
    if seed_text is None:
        random.seed()
    else:
        random.seed(int(seed_text))

    n = random.randint(2, 12)
    q = random.randint(1, 15)
    values = [random.randint(1, 60) for _ in range(n)]
    edges = []

    for i in range(2, n + 1):
        parent = random.randint(1, i - 1)
        edges.append((parent, i))

    print(n, q)
    print(*values)
    for u, v in edges:
        print(u, v)

    update_left = random.randint(0, min(3, q))
    for _ in range(q):
        if update_left > 0 and random.randint(0, 3) == 0:
            x = random.randint(1, n)
            y = random.randint(1, 60)
            print(2, x, y)
            update_left -= 1
        else:
            x = random.randint(1, n)
            print(1, x)


if __name__ == "__main__":
    main()
