#!/usr/bin/env python3
import random


DIRS = [(1, 0), (-1, 0), (0, 1), (0, -1)]


def valid(nodes, cx, cy, cr, parent):
    for idx, (x, y, r) in enumerate(nodes):
        dx = cx - x
        dy = cy - y
        dist2 = dx * dx + dy * dy
        need2 = (cr + r) * (cr + r)
        if dist2 < need2:
            return False
        if dist2 == need2 and idx != parent:
            return False
    return True


def build_case():
    while True:
        n = random.randint(2, 8)
        nodes = [(0, 0, random.randint(3, 8))]
        ok = True

        for _ in range(1, n):
            placed = False
            parent_order = list(range(len(nodes)))
            random.shuffle(parent_order)

            for parent in parent_order:
                px, py, pr = nodes[parent]
                for _ in range(200):
                    nr = random.randint(3, 8)
                    dx, dy = random.choice(DIRS)
                    dist = pr + nr
                    nx = px + dx * dist
                    ny = py + dy * dist
                    if abs(nx) > 60 or abs(ny) > 60:
                        continue
                    if valid(nodes, nx, ny, nr, parent):
                        nodes.append((nx, ny, nr))
                        placed = True
                        break
                if placed:
                    break

            if not placed:
                ok = False
                break

        if ok:
            return nodes


def main():
    random.seed()
    nodes = build_case()
    n = len(nodes)
    target = random.randint(1, n - 1)
    tx, ty, _ = nodes[target]

    order = list(range(n))
    random.shuffle(order)

    print(n, tx, ty)
    for idx in order:
        x, y, r = nodes[idx]
        print(x, y, r)


if __name__ == "__main__":
    main()
