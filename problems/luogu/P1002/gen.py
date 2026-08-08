#!/usr/bin/env python3
import random

CONTROL_DELTA = [(0, 0), (1, 2), (1, -2), (-1, 2), (-1, -2),
                 (2, 1), (2, -1), (-2, 1), (-2, -1)]


def is_blocked_start(hx, hy):
    for dx, dy in CONTROL_DELTA:
        if hx + dx == 0 and hy + dy == 0:
            return True
    return False


def main():
    # 限制 n,m <= 10，保证 brute DFS 能在时限内完成
    n = random.randint(1, 10)
    m = random.randint(1, 10)
    hx = random.randint(0, 20)
    hy = random.randint(0, 20)
    while is_blocked_start(hx, hy):
        hx = random.randint(0, 20)
        hy = random.randint(0, 20)
    print(f"{n} {m} {hx} {hy}")


if __name__ == "__main__":
    main()
