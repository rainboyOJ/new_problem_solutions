#!/usr/bin/env python3
import random


def main() -> None:
    random.seed()

    D = random.randint(2, 20)
    G = random.randint(1, 8)
    print(D, G)

    items = []
    for _ in range(G):
        t = random.randint(1, 20)
        f = random.randint(1, 8)
        h = random.randint(1, 8)
        items.append((t, f, h))

    random.shuffle(items)
    for t, f, h in items:
        print(t, f, h)


if __name__ == "__main__":
    main()
