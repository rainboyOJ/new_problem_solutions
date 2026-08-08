#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(2, 12)
    all_edges = [(u, v) for u in range(1, n + 1) for v in range(1, n + 1) if u != v]
    m = random.randint(n, min(len(all_edges), n * 3))
    edges = random.sample(all_edges, m)
    exist = set(edges)
    active = set(edges)

    q = random.randint(1, 50)
    ops = []
    for _ in range(q):
        choices = [2, 4]
        if active:
            choices.append(1)
        if len(active) < len(exist):
            choices.append(3)
        typ = random.choice(choices)

        if typ == 1:
            u, v = random.choice(list(active))
            active.remove((u, v))
            ops.append((1, u, v))
        elif typ == 2:
            v = random.randint(1, n)
            for e in list(active):
                if e[1] == v:
                    active.remove(e)
            ops.append((2, v))
        elif typ == 3:
            inactive = list(exist - active)
            u, v = random.choice(inactive)
            active.add((u, v))
            ops.append((3, u, v))
        else:
            v = random.randint(1, n)
            for e in exist:
                if e[1] == v:
                    active.add(e)
            ops.append((4, v))

    print(n, m)
    for u, v in edges:
        print(u, v)
    print(q)
    for op in ops:
        print(*op)


if __name__ == "__main__":
    main()
