#!/usr/bin/env python3
"""生成 CSP202412E 的小规模随机数据，用于主程序与暴力程序对拍。"""

import os
import random


def main():
    seed = os.environ.get("DUPAI_SEED")
    random.seed(None if seed is None else int(seed))
    n = random.randint(1, 10)
    a = [0] + [random.randint(1, 20) for _ in range(n)]
    b = [0] + [random.randint(1, 20) for _ in range(n)]
    q = random.randint(1, 4)

    print(n)
    print(*a[1:])
    print(*b[1:])
    print(q)
    for _ in range(q):
        changed = random.randint(0, n)
        print(changed)
        positions = random.sample(range(1, n + 1), changed)
        for position in positions:
            print(position, random.randint(1, 20), random.randint(1, 20))


if __name__ == "__main__":
    main()
